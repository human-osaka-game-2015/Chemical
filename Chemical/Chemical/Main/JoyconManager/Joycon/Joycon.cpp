#include "Joycon.h"
//#include <Windows.h>
#pragma pack(push, 1)

namespace
{
	// クラス内構造体にするとダメだったので.
	struct brcm_hdr {
		u8 cmd;
		u8 timer;
		u8 rumble_l[4];
		u8 rumble_r[4];
	};

	struct brcm_cmd_01 {
		u8 subcmd;
		union {
			struct {
				u32 offset;
				u8 size;
			} spi_read;

			struct {
				u8 arg1;
				u8 arg2;
			} subcmd_arg;
		};
	};

	s16 uint16_to_int16(u16 a) {
		s16 b;
		char* aPointer = (char*)&a, *bPointer = (char*)&b;
		memcpy(bPointer, aPointer, sizeof(a));
		return b;
	}

	template <typename T> T CLAMP(const T& value, const T& low, const T& high)
	{
		return value < low ? low : (value > high ? high : value);
	}

	// 参照URL
	// http://blog.hypersect.com/interpreting-analog-sticks/
	void AnalogStickCalc
		(
		float *pOutX,       // out: resulting stick X value
		float *pOutY,       // out: resulting stick Y value
		u16 x,              // in: initial stick X value
		u16 y,              // in: initial stick Y value
		u16 x_calc[3],      // calc -X, CenterX, +X
		u16 y_calc[3]       // calc -Y, CenterY, +Y
		)
	{
		float x_f, y_f;
		// Apply Joy-Con center deadzone. 0xAE translates approx to 15%. Pro controller has a 10% deadzone.
		float deadZoneCenter = 0.15f;
		// Add a small ammount of outer deadzone to avoid edge cases or machine variety.
		float deadZoneOuter = 0.10f;

		// convert to float based on calibration and valid ranges per +/-axis
		x = CLAMP(x, x_calc[0], x_calc[2]);
		y = CLAMP(y, y_calc[0], y_calc[2]);
		if (x >= x_calc[1])
			x_f = (float)(x - x_calc[1]) / (float)(x_calc[2] - x_calc[1]);
		else
			x_f = -((float)(x - x_calc[1]) / (float)(x_calc[0] - x_calc[1]));
		if (y >= y_calc[1])
			y_f = (float)(y - y_calc[1]) / (float)(y_calc[2] - y_calc[1]);
		else
			y_f = -((float)(y - y_calc[1]) / (float)(y_calc[0] - y_calc[1]));

		// Interpolate zone between deadzones
		float mag = sqrtf(x_f*x_f + y_f*y_f);
		if (mag > deadZoneCenter) {
			// scale such that output magnitude is in the range [0.0f, 1.0f]
			float legalRange = 1.0f - deadZoneOuter - deadZoneCenter;
			float normalizedMag = min(1.0f, (mag - deadZoneCenter) / legalRange);
			float scale = normalizedMag / mag;
			pOutX[1] = x_f * scale;
			pOutY[1] = y_f * scale;
		}
		else
		{
			// stick is in the inner dead zone
			pOutX[1] = 0.0f;
			pOutY[1] = 0.0f;
		}
	}
}

Joycon::Joycon() :
m_IsConnect(false)
{
	m_Handle[LEFT_CONTROLLER] = nullptr;
	m_Handle[RIGHT_CONTROLLER] = nullptr;
	memset(factory_stick_cal, 0, 0x12);
	memset(user_stick_cal, 0, 0x16);
	memset(sensor_model, 0, 0x6);
	memset(stick_model, 0, 0x12);
	memset(factory_sensor_cal, 0, 0x18);
	memset(user_sensor_cal, 0, 0x1A);
	memset(factory_sensor_cal_calm, 0, 0xC);
	memset(user_sensor_cal_calm, 0, 0xC);
	memset(sensor_cal, 0, sizeof(sensor_cal));
	memset(stick_cal_x_l, 0, sizeof(stick_cal_x_l));
	memset(stick_cal_y_l, 0, sizeof(stick_cal_y_l));
	memset(stick_cal_x_r, 0, sizeof(stick_cal_x_r));
	memset(stick_cal_y_r, 0, sizeof(stick_cal_y_r));

	cal_x[0] = 0.f;
	cal_y[0] = 0.f;

	m_AnalogStick = D3DXVECTOR2(0, 0);
	m_GyroSensor = D3DXVECTOR3(0, 0, 0);
	m_Accelerometer = D3DXVECTOR3(0, 0, 0);

	for (int i = 0; i < MAX_BUTTON; i++)
	{
		m_ButtonState[i] = OFF_BUTTON;
		m_OldButtonState[i] = OFF_BUTTON;
	}
}


Joycon::~Joycon()
{
}

bool Joycon::Connect(CONTROLLER_TYPE _controllerType)
{
	m_ControllerType = _controllerType;
	switch (_controllerType)
	{
	case Joycon::LEFT_CONTROLLER:
		m_Handle[LEFT_CONTROLLER] = hid_open(0x57e, 0x2006, nullptr);
		if (m_Handle[LEFT_CONTROLLER] == nullptr)
			return false;
		break;
	case Joycon::RIGHT_CONTROLLER:
		m_Handle[RIGHT_CONTROLLER] = hid_open(0x57e, 0x2007, nullptr);
		if (m_Handle[RIGHT_CONTROLLER] == nullptr)
			return false;
		break;
	default:
		return false;
		break;
	}
	SendRumble();
	get_spi_data(0x6020, 0x18, factory_sensor_cal);
	get_spi_data(0x603D, 0x12, factory_stick_cal);
	get_spi_data(0x6080, 0x6, sensor_model);
	get_spi_data(0x6086, 0x12, stick_model);
	get_spi_data(0x6098, 0x12, &stick_model[0x12]);
	get_spi_data(0x8010, 0x16, user_stick_cal);
	get_spi_data(0x8026, 0x1A, user_sensor_cal);

	switch (m_ControllerType)
	{
	case Joycon::LEFT_CONTROLLER:
		stick_cal_x_l[1] = (factory_stick_cal[4] << 8) & 0xF00 | factory_stick_cal[3];
		stick_cal_y_l[1] = (factory_stick_cal[5] << 4) | (factory_stick_cal[4] >> 4);
		stick_cal_x_l[0] = stick_cal_x_l[1] - ((factory_stick_cal[7] << 8) & 0xF00 | factory_stick_cal[6]);
		stick_cal_y_l[0] = stick_cal_y_l[1] - ((factory_stick_cal[8] << 4) | (factory_stick_cal[7] >> 4));
		stick_cal_x_l[2] = stick_cal_x_l[1] + ((factory_stick_cal[1] << 8) & 0xF00 | factory_stick_cal[0]);
		stick_cal_y_l[2] = stick_cal_y_l[1] + ((factory_stick_cal[2] << 4) | (factory_stick_cal[2] >> 4));
		break;
	case Joycon::RIGHT_CONTROLLER:
		stick_cal_x_r[1] = (factory_stick_cal[10] << 8) & 0xF00 | factory_stick_cal[9];
		stick_cal_y_r[1] = (factory_stick_cal[11] << 4) | (factory_stick_cal[10] >> 4);
		stick_cal_x_r[0] = stick_cal_x_r[1] - ((factory_stick_cal[13] << 8) & 0xF00 | factory_stick_cal[12]);
		stick_cal_y_r[0] = stick_cal_y_r[1] - ((factory_stick_cal[14] << 4) | (factory_stick_cal[13] >> 4));
		stick_cal_x_r[2] = stick_cal_x_r[1] + ((factory_stick_cal[16] << 8) & 0xF00 | factory_stick_cal[15]);
		stick_cal_y_r[2] = stick_cal_y_r[1] + ((factory_stick_cal[17] << 4) | (factory_stick_cal[16] >> 4));
		break;
	default:
		return false;
		break;
	}

	if ((user_stick_cal[0] | user_stick_cal[1] << 8) == 0xA1B2)
	{
		stick_cal_x_l[1] = (user_stick_cal[6] << 8) & 0xF00 | user_stick_cal[5];
		stick_cal_y_l[1] = (user_stick_cal[7] << 4) | (user_stick_cal[6] >> 4);
		stick_cal_x_l[0] = stick_cal_x_l[1] - ((user_stick_cal[9] << 8) & 0xF00 | user_stick_cal[8]);
		stick_cal_y_l[0] = stick_cal_y_l[1] - ((user_stick_cal[10] << 4) | (user_stick_cal[9] >> 4));
		stick_cal_x_l[2] = stick_cal_x_l[1] + ((user_stick_cal[3] << 8) & 0xF00 | user_stick_cal[2]);
		stick_cal_y_l[2] = stick_cal_y_l[1] + ((user_stick_cal[4] << 4) | (user_stick_cal[3] >> 4));
	}

	if ((user_stick_cal[0xB] | user_stick_cal[0xC] << 8) == 0xA1B2)
	{
		stick_cal_x_r[1] = (user_stick_cal[14] << 8) & 0xF00 | user_stick_cal[13];
		stick_cal_y_r[1] = (user_stick_cal[15] << 4) | (user_stick_cal[14] >> 4);
		stick_cal_x_r[0] = stick_cal_x_r[1] - ((user_stick_cal[17] << 8) & 0xF00 | user_stick_cal[16]);
		stick_cal_y_r[0] = stick_cal_y_r[1] - ((user_stick_cal[18] << 4) | (user_stick_cal[17] >> 4));
		stick_cal_x_r[2] = stick_cal_x_r[1] + ((user_stick_cal[20] << 8) & 0xF00 | user_stick_cal[19]);
		stick_cal_y_r[2] = stick_cal_y_r[1] + ((user_stick_cal[21] << 4) | (user_stick_cal[20] >> 4));
	}

	// Acc cal origin position
	sensor_cal[0][0] = uint16_to_int16(factory_sensor_cal[0] | factory_sensor_cal[1] << 8);
	sensor_cal[0][1] = uint16_to_int16(factory_sensor_cal[2] | factory_sensor_cal[3] << 8);
	sensor_cal[0][2] = uint16_to_int16(factory_sensor_cal[4] | factory_sensor_cal[5] << 8);
	
	// Gyro cal origin position
	sensor_cal[1][0] = uint16_to_int16(factory_sensor_cal[0xC] | factory_sensor_cal[0xD] << 8);
	sensor_cal[1][1] = uint16_to_int16(factory_sensor_cal[0xE] | factory_sensor_cal[0xF] << 8);
	sensor_cal[1][2] = uint16_to_int16(factory_sensor_cal[0x10] | factory_sensor_cal[0x11] << 8);
	
	if ((user_sensor_cal[0x0] | user_sensor_cal[0x1] << 8) == 0xA1B2)
	{
		// Acc cal origin position
		sensor_cal[0][0] = uint16_to_int16(user_sensor_cal[2] | user_sensor_cal[3] << 8);
		sensor_cal[0][1] = uint16_to_int16(user_sensor_cal[4] | user_sensor_cal[5] << 8);
		sensor_cal[0][2] = uint16_to_int16(user_sensor_cal[6] | user_sensor_cal[7] << 8);

		// Gyro cal origin position
		sensor_cal[1][0] = uint16_to_int16(user_sensor_cal[0xE] | user_sensor_cal[0xF] << 8);
		sensor_cal[1][1] = uint16_to_int16(user_sensor_cal[0x10] | user_sensor_cal[0x11] << 8);
		sensor_cal[1][2] = uint16_to_int16(user_sensor_cal[0x12] | user_sensor_cal[0x13] << 8);
	}
	// Enable nxpad standard input report
	memset(buf_cmd, 0, sizeof(buf_cmd));
	auto hdr = (brcm_hdr *)buf_cmd;
	auto pkt = (brcm_cmd_01 *)(hdr + 1);
	hdr->cmd = 0x01;
	hdr->timer = timming_byte & 0xF;
	timming_byte++;
	pkt->subcmd = 0x03;
	pkt->subcmd_arg.arg1 = 0x30;
	if (m_Handle[m_ControllerType] != nullptr)
	{
		res = hid_write(m_Handle[m_ControllerType], buf_cmd, sizeof(*hdr) + sizeof(*pkt));
		res = hid_read(m_Handle[m_ControllerType], buf_cmd, sizeof(*hdr) + sizeof(*pkt));
	}

	// Enable IMU
	memset(buf_cmd, 0, sizeof(buf_cmd));
	hdr = (brcm_hdr *)buf_cmd;
	pkt = (brcm_cmd_01 *)(hdr + 1);
	hdr->cmd = 0x01;
	hdr->timer = timming_byte & 0xF;
	timming_byte++;
	pkt->subcmd = 0x40;
	pkt->subcmd_arg.arg1 = 0x01;
	if (m_Handle[m_ControllerType] != nullptr)
	{
		res = hid_write(m_Handle[m_ControllerType], buf_cmd, sizeof(*hdr) + sizeof(*pkt));
		res = hid_read(m_Handle[m_ControllerType], buf_cmd, sizeof(*hdr) + sizeof(*pkt));
	}

	// Use SPI calibration and convert them to SI acc unit
	acc_cal_coeff[0] = (float)(1.0 / (float)(16384 - uint16_to_int16(sensor_cal[0][0]))) * 4.0f  * 9.8f;
	acc_cal_coeff[1] = (float)(1.0 / (float)(16384 - uint16_to_int16(sensor_cal[0][1]))) * 4.0f  * 9.8f;
	acc_cal_coeff[2] = (float)(1.0 / (float)(16384 - uint16_to_int16(sensor_cal[0][2]))) * 4.0f  * 9.8f;

	// Use SPI calibration and convert them to SI gyro unit
	gyro_cal_coeff[0] = (float)(936.0 / (float)(13371 - uint16_to_int16(sensor_cal[1][0])) * 0.01745329251994);
	gyro_cal_coeff[1] = (float)(936.0 / (float)(13371 - uint16_to_int16(sensor_cal[1][1])) * 0.01745329251994);
	gyro_cal_coeff[2] = (float)(936.0 / (float)(13371 - uint16_to_int16(sensor_cal[1][2])) * 0.01745329251994);
	m_IsConnect = true;
	m_Thread = std::thread(&Joycon::Update, this);
	return true;
}

void Joycon::Update()
{
	LARGE_INTEGER Time1;
	Time1.HighPart = 0;
	Time1.LowPart = 0;
	Time1.QuadPart = 0;
	Time1.u.HighPart = 0;
	Time1.u.LowPart = 0;

	while (m_IsConnect)
	{
		LARGE_INTEGER Frq, Time2;
		double TotalTime = 0;
		QueryPerformanceFrequency(&Frq);
		double MicroSec = 1000000 / (double)Frq.QuadPart;

		while (TotalTime<(1000000 / 120))
		{
			QueryPerformanceCounter(&Time2);
			TotalTime = (Time2.QuadPart - Time1.QuadPart)*MicroSec;
		}
		QueryPerformanceCounter(&Time1);

		memset(buf_cmd, 0, sizeof(buf_cmd));
		if (m_Handle[m_ControllerType] != nullptr)
		{
			res = hid_read_timeout(m_Handle[m_ControllerType], buf_reply, sizeof(buf_reply), 200);
		}

		if (res > 12)
		{
			if (buf_reply[0] == 0x21 || buf_reply[0] == 0x30 || buf_reply[0] == 0x31 || buf_reply[0] == 0x32 || buf_reply[0] == 0x33)
			{
				if (m_Handle[LEFT_CONTROLLER] != nullptr)
				{
					AnalogStickCalc(
						cal_x, cal_y,
						buf_reply[6] | (u16)((buf_reply[7] & 0xF) << 8),
						(buf_reply[7] >> 4) | (buf_reply[8] << 4),
						stick_cal_x_l,
						stick_cal_y_l);
				}
				else if (m_Handle[RIGHT_CONTROLLER] != nullptr)
				{
					AnalogStickCalc(
						cal_x, cal_y,
						buf_reply[9] | (u16)((buf_reply[10] & 0xF) << 8),
						(buf_reply[10] >> 4) | (buf_reply[11] << 4),
						stick_cal_x_r,
						stick_cal_y_r);
				}
				int len = 49;

				if (buf_reply[0] == 0x33 || buf_reply[0] == 0x31)
					len = 362;

				m_AnalogStick.x = cal_x[1];
				m_AnalogStick.y = cal_y[1];

				m_Accelerometer.x = (float)(uint16_to_int16(buf_reply[13] | (buf_reply[14] << 8) & 0xFF00)) * acc_cal_coeff[0];
				m_Accelerometer.y = (float)(uint16_to_int16(buf_reply[15] | (buf_reply[16] << 8) & 0xFF00)) * acc_cal_coeff[1];
				m_Accelerometer.z = (float)(uint16_to_int16(buf_reply[17] | (buf_reply[18] << 8) & 0xFF00)) * acc_cal_coeff[2];

				m_GyroSensor.x = (float)(uint16_to_int16(buf_reply[19] | (buf_reply[20] << 8) & 0xFF00)) * gyro_cal_coeff[0];
				m_GyroSensor.y = (float)(uint16_to_int16(buf_reply[21] | (buf_reply[22] << 8) & 0xFF00)) * gyro_cal_coeff[1];
				m_GyroSensor.z = (float)(uint16_to_int16(buf_reply[23] | (buf_reply[24] << 8) & 0xFF00)) * gyro_cal_coeff[2];
			}
		}
	}
}

void Joycon::CheckButton(int _button)
{
	if (!m_IsConnect) return;
	auto CheckButtonState = [&](bool _buttonCheck)
	{
		if (_buttonCheck)
		{
			if (m_OldButtonState[_button] == ON_BUTTON)
				m_ButtonState[_button] = ON_BUTTON;
			else
				m_ButtonState[_button] = PUSH_BUTTON;
			
			m_OldButtonState[_button] = ON_BUTTON;
		}
		else
		{
			if (m_OldButtonState[_button] == ON_BUTTON)
				m_ButtonState[_button] = RELEASE_BUTTON;
			else
				m_ButtonState[_button] = OFF_BUTTON;

			m_OldButtonState[_button] = OFF_BUTTON;
		}
	};

	switch (m_ControllerType)
	{
	case LEFT_CONTROLLER:
		if (_button == MINUS_PLUS_BUTTON)
			CheckButtonState((buf_reply[4] & 1) ? true : false);
		else if (_button == HOME_BUTTON)
			CheckButtonState((buf_reply[4] & 32) ? true : false);
		else
			CheckButtonState((buf_reply[5] & _button) ? true : false);
		break;
	case RIGHT_CONTROLLER:
		if (_button == MINUS_PLUS_BUTTON)
			CheckButtonState((buf_reply[4] & 2) ? true : false);
		else if (_button == HOME_BUTTON)
			CheckButtonState((buf_reply[4] & 16) ? true : false);
		else
			CheckButtonState((buf_reply[3] & _button) ? true : false);
		break;
	default:
		break;
	}

}


void Joycon::SendRumble()
{
	int res;
	u8 buf[0x100];
	u8 buf2[0x100];

	//Enable Vibration
	memset(buf, 0, sizeof(buf));
	auto hdr = (brcm_hdr *)buf;
	auto pkt = (brcm_cmd_01 *)(hdr + 1);
	hdr->cmd = 0x01;
	hdr->timer = timming_byte & 0xF;
	timming_byte++;
	pkt->subcmd = 0x48;
	pkt->subcmd_arg.arg1 = 0x01;
	if (m_Handle[m_ControllerType] != nullptr)
	{
		res = hid_write(m_Handle[m_ControllerType], buf, sizeof(*hdr) + sizeof(*pkt));
		res = hid_read(m_Handle[m_ControllerType], buf2, 0);
	}

	//New vibration like switch
	Sleep(16);
	//Send confirmation 
	memset(buf, 0, sizeof(buf));
	hdr->cmd = 0x01;
	hdr->timer = timming_byte & 0xF;
	timming_byte++;
	hdr->rumble_l[0] = 0xc2;
	hdr->rumble_l[1] = 0xc8;
	hdr->rumble_l[2] = 0x03;
	hdr->rumble_l[3] = 0x72;
	memcpy(hdr->rumble_r, hdr->rumble_l, sizeof(hdr->rumble_l));

	if (m_Handle[m_ControllerType] != nullptr)
	{
		res = hid_write(m_Handle[m_ControllerType], buf, sizeof(*hdr) + sizeof(*pkt));
		res = hid_read(m_Handle[m_ControllerType], buf2, 0);
	}

	Sleep(81);

	hdr->timer = timming_byte & 0xF;
	timming_byte++;
	hdr->rumble_l[0] = 0x00;
	hdr->rumble_l[1] = 0x01;
	hdr->rumble_l[2] = 0x40;
	hdr->rumble_l[3] = 0x40;
	memcpy(hdr->rumble_r, hdr->rumble_l, sizeof(hdr->rumble_l));
	if (m_Handle[m_ControllerType] != nullptr)
	{
		res = hid_write(m_Handle[m_ControllerType], buf, sizeof(*hdr) + sizeof(*pkt));
		res = hid_read(m_Handle[m_ControllerType], buf2, 0);
	}

	Sleep(5);

	hdr->timer = timming_byte & 0xF;
	timming_byte++;
	hdr->rumble_l[0] = 0xc3;
	hdr->rumble_l[1] = 0xc8;
	hdr->rumble_l[2] = 0x60;
	hdr->rumble_l[3] = 0x64;
	memcpy(hdr->rumble_r, hdr->rumble_l, sizeof(hdr->rumble_l));
	if (m_Handle[m_ControllerType] != nullptr)
	{
		res = hid_write(m_Handle[m_ControllerType], buf, sizeof(*hdr) + sizeof(*pkt));
		res = hid_read(m_Handle[m_ControllerType], buf2, 0);
	}

	Sleep(5);

	//Disable vibration
	memset(buf, 0, sizeof(buf));
	hdr = (brcm_hdr *)buf;
	pkt = (brcm_cmd_01 *)(hdr + 1);
	hdr->cmd = 0x01;
	hdr->timer = timming_byte & 0xF;
	timming_byte++;
	hdr->rumble_l[0] = 0x00;
	hdr->rumble_l[1] = 0x01;
	hdr->rumble_l[2] = 0x40;
	hdr->rumble_l[3] = 0x40;
	memcpy(hdr->rumble_r, hdr->rumble_l, sizeof(hdr->rumble_l));
	pkt->subcmd = 0x48;
	pkt->subcmd_arg.arg1 = 0x00;
	if (m_Handle[m_ControllerType] != nullptr)
	{
		res = hid_write(m_Handle[m_ControllerType], buf, sizeof(*hdr) + sizeof(*pkt));
		res = hid_read(m_Handle[m_ControllerType], buf2, 0);
	}

	memset(buf, 0, sizeof(buf));
	hdr = (brcm_hdr *)buf;
	pkt = (brcm_cmd_01 *)(hdr + 1);
	hdr->cmd = 0x01;
	hdr->timer = timming_byte & 0xF;
	timming_byte++;
	pkt->subcmd = 0x30;
	pkt->subcmd_arg.arg1 = 0x01;
	if (m_Handle[m_ControllerType] != nullptr)
	{
		res = hid_write(m_Handle[m_ControllerType], buf, sizeof(*hdr) + sizeof(*pkt));
		res = hid_read(m_Handle[m_ControllerType], buf2, 0);
	}

	// Set HOME Led
	if (m_Handle[RIGHT_CONTROLLER] != nullptr&&
		m_ControllerType == RIGHT_CONTROLLER)
	{
		memset(buf, 0, sizeof(buf));
		hdr = (brcm_hdr *)buf;
		pkt = (brcm_cmd_01 *)(hdr + 1);
		hdr->cmd = 0x01;
		hdr->timer = timming_byte & 0xF;
		timming_byte++;
		pkt->subcmd = 0x38;
		// Heartbeat style configuration
		buf[11] = 0xF1;
		buf[12] = 0x00;
		buf[13] = buf[14] = buf[15] = buf[16] = buf[17] = buf[18] = 0xF0;
		buf[19] = buf[22] = buf[25] = buf[28] = buf[31] = 0x00;
		buf[20] = buf[21] = buf[23] = buf[24] = buf[26] = buf[27] = buf[29] = buf[30] = buf[32] = buf[33] = 0xFF;
		res = hid_write(m_Handle[RIGHT_CONTROLLER], buf, sizeof(*hdr) + sizeof(*pkt));
		res = hid_read(m_Handle[RIGHT_CONTROLLER], buf2, 0);
	}
}


int Joycon::get_spi_data(u32 offset, const u16 read_len, u8 *test_buf)
{
	int res;
	u8 buf[0x100];
	while (1) {
		memset(buf, 0, sizeof(buf));
		auto hdr = (brcm_hdr *)buf;
		auto pkt = (brcm_cmd_01 *)(hdr + 1);
		hdr->cmd = 1;
		hdr->timer = timming_byte & 0xF;
		timming_byte++;
		pkt->subcmd = 0x10;
		pkt->spi_read.offset = offset;
		pkt->spi_read.size = (u8)read_len;
		if (m_Handle[m_ControllerType] != nullptr)
		{
			res = hid_write(m_Handle[m_ControllerType], buf, sizeof(*hdr) + sizeof(*pkt));
			res = hid_read(m_Handle[m_ControllerType], buf, sizeof(buf));
		}

		if ((*(u16*)&buf[0xD] == 0x1090) && (*(uint32_t*)&buf[0xF] == offset))
			break;
	}
	if (res >= 0x14 + read_len) {
		for (int i = 0; i < read_len; i++) {
			test_buf[i] = buf[0x14 + i];
		}
	}

	return 0;
}

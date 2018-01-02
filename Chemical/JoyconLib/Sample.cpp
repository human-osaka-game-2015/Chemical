#include "Joycon/Joycon.h"
#include <stdio.h>
#include <Windows.h>
#include <thread>

void main()
{
	Joycon joycon;
	Joycon joycon2;

	bool IsLeft = joycon.Connect(Joycon::LEFT_CONTROLLER);
	bool IsRight = joycon2.Connect(Joycon::RIGHT_CONTROLLER);

	while (1)
	{
		static LARGE_INTEGER Time1;
		LARGE_INTEGER Frq, Time2;
		double TotalTime = 0;
		QueryPerformanceFrequency(&Frq);
		double MicroSec = 1000000 / (double)Frq.QuadPart;

		while (TotalTime<(1000000 / 60))
		{
			QueryPerformanceCounter(&Time2);
			TotalTime = (Time2.QuadPart - Time1.QuadPart)*MicroSec;
		}
		QueryPerformanceCounter(&Time1);
		system("cls");
		if (IsLeft)
		{
			joycon.CheckButton(Joycon::DOWN_BUTTON);
			if (joycon.GetButtonState(Joycon::DOWN_BUTTON) == Joycon::PUSH_BUTTON)
			{
				printf("1");
			}
			printf("LeftController:\n");
			printf("AnalogStick X:%+f Y:%+f\n", joycon.GetAnalogStick().x, joycon.GetAnalogStick().y);
			printf("Gyro X:%+f Y:%+f Z:%+f\n", joycon.GetGyroSensor().x, joycon.GetGyroSensor().y, joycon.GetGyroSensor().z);
			printf("Acc X:%+f Y:%+f Z:%+f\n\n", joycon.GetAccelerometer().x, joycon.GetAccelerometer().y, joycon.GetAccelerometer().z);
		}

		if (IsRight)
		{
			printf("RightController:\n");
			printf("AnalogStick X:%+f Y:%+f\n", joycon2.GetAnalogStick().x, joycon2.GetAnalogStick().y);
			printf("Gyro X:%+f Y:%+f Z:%+f\n", joycon2.GetGyroSensor().x, joycon2.GetGyroSensor().y, joycon2.GetGyroSensor().z);
			printf("Acc X:%+f Y:%+f Z:%+f\n", joycon2.GetAccelerometer().x, joycon2.GetAccelerometer().y, joycon2.GetAccelerometer().z);
		}
	}

	getchar();
}
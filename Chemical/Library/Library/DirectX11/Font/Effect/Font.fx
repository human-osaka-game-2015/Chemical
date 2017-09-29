Texture2D g_Texture : register(t0);
SamplerState  g_Sampler : register(s0);

cbuffer global : register(b0)
{
	float4x4 g_WorldMat;
	float4 g_TexelOffset;
	float4 g_PosOffset;
	float4 g_ViewPort;
};

struct VS_IN
{
	float4 Pos   : POSITION;   // 頂点座標
	float2 Texel : TEXCOORD;   // テクセル
	float4 Color : COLOR;      // 頂点カラー
};

struct VS_OUT
{
	float4 Pos   : SV_POSITION;
	float2 Texel : TEXCOORD;
	float4 Color : COLOR;
};

VS_OUT VS(VS_IN In)
{
	VS_OUT Out;
	In.Pos.xy += g_PosOffset.xy;
	Out.Pos = mul(In.Pos, g_WorldMat);
	Out.Pos.x = (Out.Pos.x / g_ViewPort.x) * 2 - 1;
	Out.Pos.y = 1 - (Out.Pos.y / g_ViewPort.y) * 2;

	Out.Texel = In.Texel;
	Out.Color = In.Color;

	return Out;
}

float4 PS(VS_OUT In) : SV_Target
{
	return g_Texture.Sample(g_Sampler, In.Texel + g_TexelOffset.xy) * In.Color;
}

#type vertex

struct VSInput
{
	float2 position : Position;
};

struct VSOutput
{
	float4 position : SV_POSITION;
};

cbuffer SysShaderBuffer : register(b1)
{
	float4x4 sys_ViewProj;
	float4x4 sys_Model;
}

VSOutput VSMain(VSInput input)
{
	VSOutput output;
	output.position = mul(mul(sys_ViewProj, sys_Model), float4(input.position, 0, 1));

	return output;
}

#type pixel

struct PSInput
{
	float4 position : SV_POSITION;
};

cbuffer ShaderBuffers
{
	float4 sb_Col;
};

float4 PSMain(PSInput input) : SV_TARGET
{
	return sb_Col;
}
#type vertex

struct VSInput
{
	float2 position : POSITION;
	float2 uv       : TEXCOORD;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float2 uv       : TEXCOORD;
};

cbuffer SysShaderBuffers : register(b1)
{
	float4x4 sys_ViewProj;
	float4x4 sys_Model;
}

VSOutput VSMain(VSInput input)
{
	VSOutput output;
	output.position = mul(mul(sys_ViewProj, sys_Model), float4(input.position, 0, 1));
	output.uv       = input.uv;

	return output;
}

#type pixel

Texture2D Texture : TEXTURE: register(t0);
SamplerState Sampler : SAMPLER: register(s0);

struct PSInput
{
	float4 position : SV_POSITION;
	float2 uv       : TEXCOORD; // doesn't matter what semantic index this is
};

float4 PSMain(PSInput input) : SV_TARGET
{
	float3 pxCol = Texture.Sample(Sampler, input.uv);
	return float4(pxCol, 1.0f);
}
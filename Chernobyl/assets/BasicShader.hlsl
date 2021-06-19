#type vertex

struct VSInput
{
	float2 position : Position;
	float3 color    : Color;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float3 color    : Color;
};

VSOutput VSMain(VSInput input)
{
	VSOutput output;
	output.position = float4(input.position, 0, 1);
	output.color = input.color;

	return output;
}

#type pixel

struct PSInput
{
	float4 position : SV_POSITION;
	float3 color    : Color;
};

float4 PSMain(PSInput input) : SV_TARGET
{
	return float4(input.color, 1);
}
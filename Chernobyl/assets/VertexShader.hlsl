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

VSOutput main(VSInput input)
{
	VSOutput output;
	output.position = float4(input.position, 0, 1);
	output.color = input.color;

	return output;
}
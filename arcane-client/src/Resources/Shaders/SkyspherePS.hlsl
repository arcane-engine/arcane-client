// ReSharper disable All

struct PSInput
{
    float4 position : SV_POSITION;
    float3 localPosition : TEXCOORD0;
};

float4 main(PSInput input) : SV_Target
{
    // Normalize the local position to get a clean direction vector from origo.
    float3 dir = normalize(input.localPosition);

    // Anything below the horizon becomes the horizon color.
    float y = saturate(dir.y);

    // Adjust this value to control how fast it darkens upwards.
    y = pow(y, 0.8f);

    float3 horizon = float3(0.6980f, 0.9451f, 0.9961f);
    float3 zenith = float3(0.1569f, 0.4706f, 0.7059f);

    // Smooth interpolation between horizon and zenith.
    float3 finalColor = lerp(horizon, zenith, y);

    return float4(finalColor, 1.0f);
}
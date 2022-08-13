struct VSOut {
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
    float3 outNormal : NORMAL;
};

VSOut VS(float3 position : POSITION, float2 texCoord : TEXCOORD, float3 normal : NORMAL) {
    VSOut output;
    output.outPosition = float4(position, 1.0);
    output.outTexCoord = texCoord;
    output.outNormal = normal;
    return output;
}

float4 PS(float4 inPosition : SV_POSITION, float2 inTexCoord : TEXCOORD, float3 inNormal : NORMAL) : SV_TARGET {
    return float4(1.0, 0.0, 0.0, 1.0);
}
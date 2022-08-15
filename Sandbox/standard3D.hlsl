struct VSOut {
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
    float3 outNormal : NORMAL;
    float4 fragPos : FRAGPOS;
};

cbuffer MVP : register(b0) {
    matrix projection;
    matrix view;
    matrix model;
};

VSOut VS(float3 position : POSITION, float2 texCoord : TEXCOORD, float3 normal : NORMAL) {
    VSOut output;
    matrix finalMatrix = mul(mul(projection, view), model);
    output.fragPos = mul(model, float4(position, 1.0));
    output.outPosition = mul(finalMatrix, float4(position, 1.0));
    output.outTexCoord = texCoord;
    output.outNormal = normal;
    return output;
}

float4 PS(VSOut input) : SV_TARGET {
    return input.fragPos;
}
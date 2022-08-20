struct VSOut {
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
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
    output.position = mul(finalMatrix, float4(position, 1.0));
    output.texCoord = texCoord;
    output.normal = normal;
    return output;
}

#include "material.hlsl"
#include "lighting.hlsl"

float4 PS(VSOut input) : SV_TARGET {
    float3 lightColor = float3(1, 1, 1);
    float3 lightPosition = float3(0, 0, 0);
    float ambientStrength = 0.1;
    float3 ambient = ambientStrength * lightColor;
    float3 N = normalize(input.normal);
    float3 L = normalize(lightPosition - float3(input.fragPos.x, input.fragPos.y, input.fragPos.z));
    float diff = max(dot(N, L), 0.0);
    float3 lightDiffuse = diff * lightColor;
    float4 result = float4(lightDiffuse + ambient, 1);
    return float4(result * diffuse.color);
}
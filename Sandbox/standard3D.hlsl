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
    float3 N = normalize(input.outNormal);
    float3 lightPos = float3(0, 0, 0);
    float3 L = normalize(lightPos - float3(input.fragPos.x, input.fragPos.y, input.fragPos.z));
    float diff = max(dot(N, L), 0.0);
    float brigtness = 1.0f;
    float3 lightColor = float3(1, 1, 1);
    float3 diffuse = diff * (lightColor * brigtness);
    float ambientStrength = 0.25f;
    float3 ambient = ambientStrength * lightColor;
    return float4(ambient + diffuse, 1) * float4(1, 0, 0, 1);
}
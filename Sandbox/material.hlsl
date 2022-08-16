#define MATERIAL_TEXTURE_MAP 0
#define MATERIAL_COLOR 1
#define MATERIAL_FLOAT 2

struct MaterialAttribute {
    int type;
    float4 color;
    float val;
};

Texture2D diffuseTexture : register(t0) : DIFFUSE;
Texture2D specularTexture : register(t1) : SPECULAR;
SamplerState textureSampler : register(s0) : SAMPLERSTATE;

cbuffer Material : register(b1) {
    MaterialAttribute diffuse;
    MaterialAttribute specular;
    float specularExponent;
}
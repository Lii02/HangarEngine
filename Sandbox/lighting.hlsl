#define POINTLIGHT 0
#define DIRECTIONALLIGHT 1
#define SPOTLIGHT 2
#define MAX_LIGHTS 5

struct Light {
    float color;
    float intensity;
    int type;
};

cbuffer Lights : register(b2) {
    Light lights[MAX_LIGHTS];
}
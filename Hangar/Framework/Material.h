#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Math/Color.h"

class Texture2D;

enum MaterialAttributeType : int {
	TEXTURE_MAP,
	COLOR_VALUE,
	FLOAT_VALUE,
};

template <typename T>
struct MaterialAttribute {
	Texture2D* map;
	T value;
	MaterialAttributeType type;

	MaterialAttribute() = default;
	MaterialAttribute(Texture2D* map) {
		this->type = MaterialAttributeType::TEXTURE_MAP;
		this->map = map;
	}
	MaterialAttribute(T value, MaterialAttributeType type) {
		this->map = nullptr;
		this->value = value;
		this->type = type;
	}
};

#define MATERIAL_CBUFFER_SIZE sizeof(Material::ConstantBuffer)
#define MATERIAL_CBUFFER_SLOT 1

class Material {
private:
	struct alignas(16) ConstantBuffer {
		struct MaterialAttribute {
			int type;
			Color color;
			float val;
		};
		MaterialAttribute diffuse;
		MaterialAttribute specular;
		float specularExponent;
	};

	std::string name;
	MaterialAttribute<Color> diffuse;
	MaterialAttribute<Color> specular;
	float specularExponent;
	uint64_t cbuffer;
	ConstantBuffer constantBufferData;
public:
	Material(std::string name = "Material");
	~Material();
	Material(const Material&) = delete;

	MaterialAttribute<Color> GetDiffuse();
	void SetDiffuse(MaterialAttribute<Color> diffuse);
	MaterialAttribute<Color> GetSpecular();
	void SetSpecular(MaterialAttribute<Color> specular);
	float GetSpecularExponent() const;
	void SetSpecularExponent(float specularExponent);
	void Bind();
	void Update();
	std::string GetName() const;
	void SetName(std::string name);
};

#endif
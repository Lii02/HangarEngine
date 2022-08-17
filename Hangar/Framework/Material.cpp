#include "Precompiled.h"
#include "Material.h"
#include "Texture2D.h"
#include <Renderer/RendererCommands.h>

Material::Material(std::string name) {
	this->name = name;
	Initialize();
	SetDiffuse(MaterialAttribute<Color>(Color(1, 1, 1), MaterialAttributeType::COLOR_VALUE));
	SetSpecular(MaterialAttribute<Color>(Color(0, 0, 0), MaterialAttributeType::COLOR_VALUE));
	SetSpecularExponent(1.0f);
}

Material::~Material() {
	DeInitialize();
}

void Material::Initialize() {
	this->cbuffer = RendererCommands::CreateDataBuffer(MATERIAL_CBUFFER_SIZE, 1, DataBufferBinding::CONSTANT_BUFFER);
}

void Material::DeInitialize() {
	RendererCommands::RemoveDataBuffer(cbuffer);
}

MaterialAttribute<Color> Material::GetDiffuse() {
	return diffuse;
}

void Material::SetDiffuse(MaterialAttribute<Color> diffuse) {
	this->diffuse = diffuse;
	constantBufferData.diffuse = { diffuse.type, diffuse.value, diffuse.value.r };
}

MaterialAttribute<Color> Material::GetSpecular() {
	return specular;
}

void Material::SetSpecular(MaterialAttribute<Color> specular) {
	this->specular = specular;
	constantBufferData.specular = { specular.type, specular.value, specular.value.r };
}

float Material::GetSpecularExponent() const {
	return specularExponent;
}

void Material::SetSpecularExponent(float specularExponent) {
	this->specularExponent = specularExponent;
	constantBufferData.specularExponent = specularExponent;
}

void Material::Bind() {
	RendererCommands::BindConstantBuffer(cbuffer, MATERIAL_CBUFFER_SLOT);
	if (diffuse.type == MaterialAttributeType::TEXTURE_MAP)
		diffuse.map->Bind();
	if (specular.type == MaterialAttributeType::TEXTURE_MAP)
		specular.map->Bind();
}

void Material::Update() {
	RendererCommands::UpdateDataBuffer(cbuffer, (void*)&constantBufferData);
}

std::string Material::GetName() const {
	return name;
}

void Material::SetName(std::string name) {
	this->name = name;
}
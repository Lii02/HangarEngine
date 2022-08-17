#include "Precompiled.h"
#include "Mesh.h"
#include "../../Renderer/IRenderAPI.h"
#include "../../Renderer/RendererCommands.h"

Mesh::Mesh(MeshData3D* meshData, uint32_t indexCount, uint32_t firstIndex)
	: IComponent(ComponentType::MESH) {
	this->meshData = meshData;
	this->indexCount = indexCount;
	this->firstIndex = firstIndex;
}

Mesh::~Mesh() {
	RendererCommands::RemoveDataBuffer(vbo);
	RendererCommands::RemoveDataBuffer(ibo);
}

void Mesh::Init() {
	this->vbo = RendererCommands::CreateDataBuffer(sizeof(StandardVertex3D), meshData->vertices.size(), DataBufferBinding::VERTEX_BUFFER);
	this->ibo = RendererCommands::CreateDataBuffer(sizeof(int), meshData->indices.size(), DataBufferBinding::INDEX_BUFFER);
	RendererCommands::UpdateDataBuffer(vbo, meshData->vertices.data());
	RendererCommands::UpdateDataBuffer(ibo, meshData->indices.data());
}

void Mesh::Render() {
	// Render whole mesh for now
	material->Bind();
	RendererCommands::BindVertexBuffer(vbo);
	RendererCommands::BindIndexBuffer(ibo);
	RendererCommands::DrawIndexed(indexCount, firstIndex);
}

void Mesh::Update() {
}

Material* Mesh::GetMaterial() {
	return material;
}

void Mesh::SetMaterial(Material* newMaterial) {
	this->material = newMaterial;
}
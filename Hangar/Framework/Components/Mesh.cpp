#include "Precompiled.h"
#include "Mesh.h"
#include "../../Renderer/IRenderAPI.h"
#include "../../Renderer/RendererCommands.h"

Mesh::Mesh(Vertices* vertices, Indices* indices, uint32_t indexCount)
	: IComponent(ComponentType::MESH) {
	this->vertices = vertices;
	this->indices = indices;
	this->indexCount = indexCount;
}

Mesh::~Mesh() {
	RendererCommands::RemoveDataBuffer(vbo);
	RendererCommands::RemoveDataBuffer(ibo);
}

void Mesh::Init() {
	this->vbo = RendererCommands::CreateDataBuffer(sizeof(StandardVertex3D), vertices->size(), DataBufferBinding::VERTEX_BUFFER);
	this->ibo = RendererCommands::CreateDataBuffer(sizeof(int), indices->size(), DataBufferBinding::INDEX_BUFFER);
	RendererCommands::UpdateDataBuffer(vbo, vertices->data());
	RendererCommands::UpdateDataBuffer(ibo, indices->data());
	vertices = nullptr;
	indices = nullptr;
}

void Mesh::Render() {
	// Render whole mesh for now
	RendererCommands::BindVertexBuffer(vbo);
	RendererCommands::BindIndexBuffer(ibo);
	RendererCommands::DrawIndexed(indexCount);
}

void Mesh::Update() {
}
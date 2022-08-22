#include "Precompiled.h"
#include "MeshRenderer.h"
#include <Renderer/IRenderAPI.h>
#include <Renderer/RendererCommands.h>

MeshRenderer::MeshRenderer(MeshData3D* meshData, uint32_t indexCount, uint32_t firstIndex)
	: IComponent(ComponentType::MESHRENDERER) {
	this->meshData = meshData;
	this->indexCount = indexCount;
	this->firstIndex = firstIndex;
}

MeshRenderer::~MeshRenderer() {
	Unload();
}

void MeshRenderer::Initialize() {
	this->vbo = RendererCommands::CreateDataBuffer(sizeof(StandardVertex3D), meshData->vertices.size(), DataBufferBinding::VERTEX_BUFFER);
	this->ibo = RendererCommands::CreateDataBuffer(sizeof(int), meshData->indices.size(), DataBufferBinding::INDEX_BUFFER);
	RendererCommands::UpdateDataBuffer(vbo, meshData->vertices.data());
	RendererCommands::UpdateDataBuffer(ibo, meshData->indices.data());
}

void MeshRenderer::Render() {
	// Render whole mesh for now
	material->Bind();
	RendererCommands::BindVertexBuffer(vbo);
	RendererCommands::BindIndexBuffer(ibo);
	RendererCommands::DrawIndexed(indexCount, firstIndex);
}

void MeshRenderer::Update() {
}

void MeshRenderer::Unload() {
	RendererCommands::RemoveDataBuffer(vbo);
	RendererCommands::RemoveDataBuffer(ibo);
}

Material* MeshRenderer::GetMaterial() {
	return material;
}

void MeshRenderer::SetMaterial(Material* newMaterial) {
	this->material = newMaterial;
}
#include "Precompiled.h"
#include "EntityRenderer.h"
#include "../IO/FileSystem.h"
#include "../Renderer/RendererCommands.h"

EntityRenderer::EntityRenderer() {
	Initialize();
}

EntityRenderer::~EntityRenderer() {
	DeInitialize();
}

void EntityRenderer::Initialize() {
	constantBuffer = RendererCommands::CreateDataBuffer(sizeof(ConstantBuffer), 1, DataBufferBinding::CONSTANT_BUFFER);
	// Temporary shader loading
	InputElementArray inputElements;
	inputElements.push_back({ 0, 3, 0, "POSITION" });
	inputElements.push_back({ 0, 2, 0, "TEXCOORD" });
	inputElements.push_back({ 0, 3, 0, "NORMAL" });
	File* shaderFile = FileSystem::Get()->ImmSearchFile("standard3D.hlsl");
	shaderFile->Open();

	this->shader = RendererCommands::CreateRenderShader(shaderFile->ReadString(shaderFile->Length()), "VS", "PS", inputElements);
}

void EntityRenderer::DeInitialize() {
	RendererCommands::RemoveDataBuffer(constantBuffer);
	RendererCommands::RemoveRenderShader(shader);
}

void EntityRenderer::PrepareFrame(Entity* camera, Matrix projection) {
	cbuffer.projection = projection;
	cbuffer.view = camera->GetTransform().ToViewMatrix();
}

void EntityRenderer::DrawEntity(Entity* e) {
	cbuffer.model = e->GetTransform().ToMatrix();
	RendererCommands::UpdateDataBuffer(constantBuffer, (void*)&cbuffer);
	RendererCommands::BindRenderShader(shader);
	RendererCommands::BindConstantBuffer(constantBuffer);
	e->Render();
}
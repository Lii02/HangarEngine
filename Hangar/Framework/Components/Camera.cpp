#include "Precompiled.h"
#include "Camera.h"
#include "../../Renderer/RendererCommands.h"

Camera::Camera(float fov, float nearZ, float farZ, ProjectionType projectionType)
	: IComponent(ComponentType::CAMERA) {
	this->fov = fov;
	this->nearZ = nearZ;
	this->farZ = farZ;
	this->projectionType = projectionType;
}

void Camera::Init() {
}

void Camera::Render() {
	switch (projectionType) {
	case PERSPECTIVE:
		this->projection = Matrix::PerspectiveLH(fov, RendererCommands::GetAspectRatio(), nearZ, farZ);
		break;
	}
}

void Camera::Update() { }

Matrix Camera::GetProjection() {
	return projection;
}

ProjectionType Camera::GetType() const {
	return projectionType;
}

void Camera::SetType(ProjectionType projectionType) {
	this->projectionType = projectionType;
}

float Camera::GetFOV() const {
	return fov;
}

void Camera::SetFOV(float fov) {
	this->fov = fov;
}

float Camera::GetNearZ() const {
	return nearZ;
}

void Camera::SetNearZ(float nearZ) {
	this->nearZ = nearZ;
}

float Camera::GetFarZ() const {
	return farZ;
}

void Camera::SetFarZ(float farZ) {
	this->farZ = farZ;
}
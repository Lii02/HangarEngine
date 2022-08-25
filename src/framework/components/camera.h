#ifndef CAMERA_H
#define CAMERA_H
#include "../IComponent.h"
#include "../../Math/Matrix.h"

enum ProjectionType {
	NONE,
	PERSPECTIVE,
	ORTHOGRAPHIC,
};

class Camera : public IComponent {
private:
	Matrix projection;
	ProjectionType projectionType;
	float fov, nearZ, farZ;
public:
	Camera(float fov, float nearZ, float farZ, ProjectionType projectionType = PERSPECTIVE);

	virtual void Initialize() override;
	virtual void Render() override;
	virtual void Update() override;

	Matrix GetProjection();
	ProjectionType GetType() const;
	void SetType(ProjectionType projectionType);
	float GetFOV() const;
	void SetFOV(float fov);
	float GetNearZ() const;
	void SetNearZ(float nearZ);
	float GetFarZ() const;
	void SetFarZ(float farZ);
};

#endif
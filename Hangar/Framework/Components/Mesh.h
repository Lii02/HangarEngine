#ifndef MESH_H
#define MESH_H
#include "../IComponent.h"

class Mesh : public IComponent {
private:
public:
	Mesh();
	~Mesh();
	
	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
};

#endif
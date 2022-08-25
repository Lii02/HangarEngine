#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#include "../IComponent.h"

class MeshRenderer : public IComponent {
private:
public:
	MeshRenderer();
	~MeshRenderer();
	
	virtual void Initialize() override;
	virtual void Render() override;
	virtual void Update() override;
};

#endif
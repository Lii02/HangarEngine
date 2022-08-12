#include "Precompiled.h"
#include "IRenderAPI.h"

void IRenderAPI::ClearStats() {
	this->objectDrawCount = 0;
	this->vertexDrawCount = 0;
}
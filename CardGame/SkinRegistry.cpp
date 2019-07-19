#include "SkinRegistry.h"

SkinRegistry::SkinRegistry() {}

SkinRegistry::~SkinRegistry() {}


void SkinRegistry::registerRenderFactory(std::string className, AbstractRender*(*newRender)()) {
	//TODO
}

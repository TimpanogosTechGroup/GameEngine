#pragma once
#include "RenderEngine.h"

class Registry
{
public:
	Registry();
	~Registry();

	static inline RenderEngine* GetRenderEngine() { return renderEngine; };
	static void SetRenderEngine(RenderEngine* engine) { renderEngine = engine; };

private:
	static RenderEngine* renderEngine;
};
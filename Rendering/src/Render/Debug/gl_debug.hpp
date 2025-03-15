#pragma once
#include <glad/glad.h>

namespace Engine
{
	void GLClearErrors();
	bool GLCheckErrors();
}

#ifdef DEBUG
	// Works for visual studio, might not work for other IDE
	#define DEBUG_BREAK() __debugbreak();
#else
	#define DEBUG_BREAK()
#endif

// ASSERT only in DEBUG builds
#ifdef DEBUG
	#define ASSERT(x) if (!(x)) DEBUG_BREAK();
#else
	#define ASSERT(x) 
#endif

// GLCHECK(x), for internal debug purposes only
#ifdef DEBUG
	#define GLCHECK(x) Engine::GLClearErrors();	x; ASSERT(Engine::GLCheckErrors())
#else
	#define GLCHECK(x) x;
#endif

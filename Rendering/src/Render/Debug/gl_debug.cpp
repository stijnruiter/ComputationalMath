#include "gl_debug.hpp"
#include "Logger.hpp"
#include "glad/glad.h"

void Render::Debug::GLClearErrors()
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        Logger::LogError("GLERROR still in queue {:#06x}", err);
        DEBUG_BREAK();
    }
}

bool Render::Debug::GLCheckErrors()
{
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR)
    {
        // TODO: Format err code to readable error message
        Logger::LogError("GLERROR {:#06x}", err);
        return false;
    }
    return true;
}

#include "vorGLPlusInit.hpp"

bool GlPlusInit(void)
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	return true;
}
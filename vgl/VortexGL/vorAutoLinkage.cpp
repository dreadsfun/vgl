// Link against the opengl library
#pragma comment(lib, "opengl32.lib")
// Gl Extension wrangler library
#ifdef GLEW_STATIC
#	pragma comment(lib, "glew32s.lib")
#else
#	pragma comment(lib, "glew32d.lib")
#endif
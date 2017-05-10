#ifndef _GLPLUSSHARED_HPP
#define _GLPLUSSHARED_HPP

#define GLAPICALL __stdcall

// External classes' dll-interface
#pragma warning(disable : 4251)

#include "../VortexCore/vorPlatformSharedLib.hpp"

#ifdef GLPLUS_EXPORTS
#	define GLPLUS_API SHARED_EXPORT
#else
#	define GLPLUS_API SHARED_IMPORT
#endif

#endif // !_GLPLUSSHARED_HPP

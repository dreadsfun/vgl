#ifndef _GLOBJECTPOOL_HPP
#define _GLOBJECTPOOL_HPP

#include "vorGLPlusShared.hpp"

#include <unordered_map>

#include <glew\glew.h>
#include <gl/GL.h>

namespace vortex {
	namespace renderer {
		typedef void GLAPICALL __GlAllocatorSU(GLsizei, GLuint*);
		typedef GLuint GLAPICALL __GlAllocatorV(void);
		typedef GLuint GLAPICALL __GlAllocatorE(GLenum);
		typedef GLsync GLAPICALL __GlAllocatorY(GLenum, GLbitfield);

		typedef void GLAPICALL __GlDeallocatorSCU(GLsizei, const GLuint*);
		typedef void GLAPICALL __GlDeallocatorSU(GLsizei, GLuint*);
		typedef void GLAPICALL __GlDeallocatorU(GLuint);
		typedef void GLAPICALL __GlDeallocatorY(GLsync);

		class GLPLUS_API GlObjectPool {
		public:
			template<class T>
			GLuint GrabHandle(T* _Allocator);

			template<class T>
			GLuint GrabHandle(T* _Allocator, GLenum _AllocationTarget);

			template<class T>
			void DropHandle(void* _Target, GLuint _Handle, T* _Deallocator);

			void Copy(void* _Target, GLuint _Handle);

		private:
			std::unordered_map<void*, std::unordered_map<GLuint, unsigned int>> __ObjectPool;
		};
	}
}
#endif
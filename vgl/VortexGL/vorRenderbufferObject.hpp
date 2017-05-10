#ifndef __RENDERBUFFER_OBJECT_HPP__
#define __RENDERBUFFER_OBJECT_HPP__

#include "vorGLObject.hpp"

namespace vortex {
	namespace renderer {
		class RenderbufferObject : public GlObject<__GlAllocatorSU, __GlDeallocatorSCU, __GlBindFunctionEU> {
		public:
			RenderbufferObject(void)
				: GlObject(glGenRenderbuffers, glDeleteRenderbuffers, glBindRenderbuffer, glIsRenderbuffer) { }

			void InitializeStorage(GLenum _InternalFormat, GLsizei _Width, GLsizei _Height);
			void InitializeSampledStorage(GLsizei _Samples, GLenum _InternalFormat, GLsizei _Width, GLsizei _Height);
		};
	}
}
#endif
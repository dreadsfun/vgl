#ifndef __FRAMEBUFFER_OBJECT_HPP__
#define __FRAMEBUFFER_OBJECT_HPP__

#include "vorGLObject.hpp"
#include "vorTextureObject.hpp"
#include "vorRenderbufferObject.hpp"

namespace vortex {
	namespace renderer {
		class FramebufferObject : public GlObject<__GlAllocatorSU, __GlDeallocatorSCU, __GlBindFunctionEU> {
		public:
			FramebufferObject(void)
				: GlObject(glGenFramebuffers, glDeleteFramebuffers, glBindFramebuffer, glIsFramebuffer) { }

			void AttachImage(GLenum _AttachmentTarget, const TextureObject& _Texture, GLint _ImageLevel);
			void AttachRenderbuffer(GLenum _AttachmentTarget, const RenderbufferObject& _Renderbuffer);

			void SetParameter(GLenum _Parameter, GLint _Value);

			bool CheckCompleteness(void);

			void CopyTo(FramebufferObject& _Destination, GLint _SourceX0, GLint _SourceY0, GLint _SourceX1, GLint _SourceY1,
				GLint _DestiniationX0, GLint _DestinationY0, GLint _DestinationX1, GLint _DestinationY1, GLbitfield _TargetBuffers, GLenum _Filter);

			void ReadPixels(GLint _FromX, GLint _FromY, GLsizei _Width, GLsizei _Height, GLenum _Format, GLenum _DataType, GLvoid* _Data);
		};
	}
}

#endif
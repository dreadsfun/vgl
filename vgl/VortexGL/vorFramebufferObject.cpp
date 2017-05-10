#include "vorFramebufferObject.hpp"

namespace vortex {
	namespace renderer {
		void FramebufferObject::AttachImage(GLenum _AttachmentTarget, const TextureObject& _Texture, GLint _ImageLevel)
		{
			glFramebufferTexture2D(__Target, _AttachmentTarget, _Texture.Target(), _Texture, _ImageLevel);
		}

		void FramebufferObject::AttachRenderbuffer(GLenum _AttachmentTarget, const RenderbufferObject& _Renderbuffer)
		{
			glFramebufferRenderbuffer(__Target, _AttachmentTarget, GL_RENDERBUFFER, _Renderbuffer);
		}

		void FramebufferObject::SetParameter(GLenum _Parameter, GLint _Value)
		{
			glFramebufferParameteri(__Target, _Parameter, _Value);
		}

		bool FramebufferObject::CheckCompleteness(void)
		{
			return glCheckFramebufferStatus(__Target) == GL_FRAMEBUFFER_COMPLETE;
		}

		void FramebufferObject::CopyTo(FramebufferObject& _Destination, GLint _SourceX0, GLint _SourceY0, GLint _SourceX1, GLint _SourceY1,
			GLint _DestiniationX0, GLint _DestinationY0, GLint _DestinationX1, GLint _DestinationY1, GLbitfield _TargetBuffers, GLenum _Filter)
		{
			if (__Target != GL_READ_FRAMEBUFFER)
			{
				BindObject(GL_READ_FRAMEBUFFER);
			}

			_Destination.BindObject(GL_DRAW_FRAMEBUFFER);

			glBlitFramebuffer(_SourceX0, _SourceY0, _SourceX1, _SourceY1, _DestiniationX0, _DestinationY0, _DestinationX1,
				_DestinationY1, _TargetBuffers, _Filter);
		}

		void FramebufferObject::ReadPixels(GLint _FromX, GLint _FromY, GLsizei _Width, GLsizei _Height, GLenum _Format, GLenum _DataType, GLvoid* _Data)
		{
			BindObject(GL_READ_FRAMEBUFFER);
			glReadPixels(_FromX, _FromY, _Width, _Height, _Format, _DataType, _Data);
		}
	}
}
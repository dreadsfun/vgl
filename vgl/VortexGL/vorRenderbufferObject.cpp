#include "vorRenderbufferObject.hpp"

namespace vortex {
	namespace renderer {
		void RenderbufferObject::InitializeStorage(GLenum _InternalFormat, GLsizei _Width, GLsizei _Height)
		{
			glRenderbufferStorage(__Target, _InternalFormat, _Width, _Height);
		}

		void RenderbufferObject::InitializeSampledStorage(GLsizei _Samples, GLenum _InternalFormat, GLsizei _Width, GLsizei _Height)
		{
			glRenderbufferStorageMultisample(__Target, _Samples, _InternalFormat, _Width, _Height);
		}
	}
}
#include "vorSamplerObject.hpp"

namespace vortex {
	namespace renderer {
		void SamplerObject::SetParameter(GLenum _Parameter, GLfloat _Value)
		{
			glSamplerParameterf(__Handle, _Parameter, _Value);
		}

		void SamplerObject::SetParameter(GLenum _Parameter, GLint _Value)
		{
			glSamplerParameteri(__Handle, _Parameter, _Value);
		}
	}
}
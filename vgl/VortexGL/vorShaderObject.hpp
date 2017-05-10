#ifndef _SHADEROBJECT_HPP
#define _SHADEROBJECT_HPP

#include "vorGLObject.hpp"

namespace vortex {
	namespace renderer {
		enum ShaderType {
			SHADER_VERTEX = GL_VERTEX_SHADER,
			SHADER_FRAGMENT = GL_FRAGMENT_SHADER,
			SHADER_GEOMETRY = GL_GEOMETRY_SHADER,
			SHADER_TESSELATION_CONTROL = GL_TESS_CONTROL_SHADER,
			SHADER_TESSELATION_EVALUATION = GL_TESS_EVALUATION_SHADER
		};

		class GLPLUS_API ShaderObject : public GlObject<__GlAllocatorE, __GlDeallocatorU, __NoBindFunction> {
		public:
			ShaderObject(ShaderType _Type)
				: GlObject(glCreateShader, glDeleteShader, _Type, 0, glIsShader) { }

			ShaderObject(ShaderType _Type, GLuint _Handle)
				: GlObject(_Handle, glDeleteShader, 0, glIsShader) { }

			void FromBinary(GLenum _BinaryFormat, const void* _Binary, GLsizei _Length);

			void BufferSource(const std::string& _Source);
			bool Compile(void);

			void GetParameter(GLenum _Parameter, GLint* _OutValue);
			std::string GetInformationLog(void);
			std::string GetSource(void);
		};
	}
}
#endif
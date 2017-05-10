#include "vorShaderObject.hpp"

namespace vortex {
	namespace renderer {
		void ShaderObject::BufferSource(const std::string& _Source)
		{
			const char* _CSource = _Source.c_str();
			glShaderSource(__Handle, 1, &_CSource, nullptr);
		}

		bool ShaderObject::Compile(void)
		{
			glCompileShader(__Handle);
			GLint _Result = 0;
			glGetShaderiv(__Handle, GL_COMPILE_STATUS, &_Result);

			return _Result <= 0;
		}

		void ShaderObject::GetParameter(GLenum _Parameter, GLint* _OutValue)
		{
			glGetShaderiv(__Handle, _Parameter, _OutValue);
		}

		std::string ShaderObject::GetInformationLog(void)
		{
			GLint _InfoLength = 0;
			GetParameter(GL_INFO_LOG_LENGTH, &_InfoLength);
			std::string _Result(_InfoLength, 0);

			glGetShaderInfoLog(__Handle, _InfoLength, NULL, &_Result[0]);
			return _Result;
		}

		std::string ShaderObject::GetSource(void)
		{
			GLint _SourceLength = 0;
			GetParameter(GL_SHADER_SOURCE_LENGTH, &_SourceLength);
			std::string _Result(_SourceLength, 0);

			glGetProgramInfoLog(__Handle, _SourceLength, NULL, &_Result[0]);
			return _Result;
		}

		void ShaderObject::FromBinary(GLenum _BinaryFormat, const void* _Binary, GLsizei _Length)
		{
			glShaderBinary(1, &__Handle, _BinaryFormat, _Binary, _Length);
		}
	}
}
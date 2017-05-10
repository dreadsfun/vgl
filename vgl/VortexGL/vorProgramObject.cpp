#include "vorProgramObject.hpp"

namespace vortex {
	namespace renderer {
		void ProgramObject::AttachShader(const ShaderObject& _Shader)
		{
			glAttachShader(__Handle, _Shader);
		}

		bool ProgramObject::Link(void)
		{
			GLint _Result = 0;
			glLinkProgram(__Handle);
			glGetProgramiv(__Handle, GL_LINK_STATUS, &_Result);
			return _Result == GL_TRUE;
		}

		GLint ProgramObject::GetAttributeLocation(const std::string& _AttributeName)
		{
			return glGetAttribLocation(__Handle, _AttributeName.c_str());
		}

		GLint ProgramObject::GetUniformLocation(const std::string& _UniformName)
		{
			return glGetUniformLocation(__Handle, _UniformName.c_str());
		}

		GLint ProgramObject::GetSubRoutineIndex(const std::string& _RoutineName, ShaderType _TargetShader)
		{
			return glGetSubroutineIndex(__Handle, _TargetShader, _RoutineName.c_str());
		}

		void ProgramObject::SetSubRoutines(ShaderType _TargetShader, GLsizei _RoutineCount, const GLuint* _RoutineIndices)
		{
			glUniformSubroutinesuiv(_TargetShader, _RoutineCount, _RoutineIndices);
		}

		GLuint ProgramObject::GetUniformBlockIndex(const std::string& _BlockName)
		{
			return glGetUniformBlockIndex(__Handle, _BlockName.c_str());
		}

		std::vector<GLuint> ProgramObject::GetUniformIndices(const std::vector<std::string>& _NameIndices)
		{
			GLsizei _TargetSize = _NameIndices.size();
			std::vector<GLuint> _Result(_TargetSize);
			const GLchar* const _Names = &_NameIndices[0][0];
			glGetUniformIndices(__Handle, _TargetSize, &_Names, &_Result[0]);
			return _Result;
		}

		void ProgramObject::BindAttributeLocation(GLuint _TargetIndex, const std::string& _AttributeName)
		{
			glBindAttribLocation(__Handle, _TargetIndex, _AttributeName.c_str());
		}

		void ProgramObject::BindFragmentDataLocation(GLuint _ColorNumber, GLuint _Index, const std::string& _Name)
		{
			glBindFragDataLocationIndexed(__Handle, _ColorNumber, _Index, _Name.c_str());
		}

		void ProgramObject::BindFragmentDataLocation(GLuint _ColorNumber, const std::string& _Name)
		{
			glBindFragDataLocation(__Handle, _ColorNumber, _Name.c_str());
		}

		void ProgramObject::SetUniform(GLint _Location, const core::Matrix4f& _Value)
		{
			glUniformMatrix4fv(_Location, 1, false, _Value.GetDataPointer());
		}

		void ProgramObject::SetUniform(GLint _Location, const core::Vector3f& _Value)
		{
			glUniform3f(_Location, _Value.X, _Value.Y, _Value.Z);
		}

		void ProgramObject::SetUniform(GLint _Location, const core::Vector4f& _Value)
		{
			glUniform4f(_Location, _Value.X, _Value.Y, _Value.Z, _Value.W);
		}

		void ProgramObject::DetachShader(const ShaderObject& _Shader)
		{
			glDetachShader(__Handle, _Shader);
		}

		void ProgramObject::GetAttachedShaders(std::vector<ShaderObject>& _OutShaders)
		{
			GLuint _Shaders[5];
			GLsizei _Count = 0;

			glGetAttachedShaders(__Handle, 5, &_Count, _Shaders);
			_OutShaders.resize(_Count, ShaderObject(ShaderType::SHADER_VERTEX, 0));
			for (GLsizei i = 0; i < _Count; i++) {
				GLint _ShaderType = 0;
				glGetShaderiv(_Shaders[i], GL_SHADER_TYPE, &_ShaderType);
				_OutShaders[i] = ShaderObject(static_cast<ShaderType>(_ShaderType), _Shaders[i]);
			}
		}

		void ProgramObject::GetParameter(GLenum _Parameter, GLint* _OutValue)
		{
			glGetProgramiv(__Handle, _Parameter, _OutValue);
		}

		std::string ProgramObject::GetInformationLog(void)
		{
			GLint _InfoLength = 0;
			GetParameter(GL_INFO_LOG_LENGTH, &_InfoLength);
			std::string _Result(_InfoLength, 0);

			glGetProgramInfoLog(__Handle, _InfoLength, NULL, &_Result[0]);
			return _Result;
		}

		void ProgramObject::FromBinary(GLenum _BinaryFormat, const void* _Data, GLsizei _Length)
		{
			glProgramBinary(__Handle, _BinaryFormat, _Data, _Length);
		}

		void ProgramObject::SetParameter(GLenum _Parameter, GLint _Value)
		{
			glProgramParameteri(__Handle, _Parameter, _Value);
		}

		void ProgramObject::SetupFeedbackVaryings(const std::vector<std::string>& _Varyings, GLenum _BufferMode)
		{
			const char* _PVaryings = _Varyings[0].c_str();
			glTransformFeedbackVaryings(__Handle, _Varyings.size(), &_PVaryings, _BufferMode);
		}

		bool ProgramObject::ValidateProgram(void)
		{
			glValidateProgram(__Handle);
			GLint _Result = 0;
			GetParameter(GL_VALIDATE_STATUS, &_Result);
			return _Result == GL_TRUE;
		}

		void ProgramObject::GetAtomicCounterParameter(GLuint _BufferIndex, GLenum _Parameter, GLint* _OutValue)
		{
			glGetActiveAtomicCounterBufferiv(__Handle, _BufferIndex, _Parameter, _OutValue);
		}

		void ProgramObject::GetAttributeParameters(GLuint _Index, GLint* _Size, GLenum* _Type, std::string& _Name)
		{
			GLint _MaxLength = 0;
			GetParameter(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &_MaxLength);
			_Name.resize(_MaxLength);
			glGetActiveAttrib(__Handle, _Index, _MaxLength, NULL, _Size, _Type, &_Name[0]);
		}

		void ProgramObject::GetSubroutineName(GLenum _Stage, GLuint _Index, std::string& _OutName)
		{
			GLint _MaxLength = 0;
			GetStageParameter(_Stage, GL_ACTIVE_SUBROUTINE_MAX_LENGTH, &_MaxLength);
			_OutName.resize(_MaxLength);
			glGetActiveSubroutineName(__Handle, _Stage, _Index, _MaxLength, NULL, &_OutName[0]);
		}

		void ProgramObject::GetStageParameter(GLenum _Stage, GLenum _Parameter, GLint* _OutValue)
		{
			glGetProgramStageiv(__Handle, _Stage, _Parameter, _OutValue);
		}

		void ProgramObject::GetSubroutineParameter(GLenum _Stage, GLuint _Index, GLenum _Parameter, GLint* _OutValue)
		{
			glGetActiveSubroutineUniformiv(__Handle, _Stage, _Index, _Parameter, _OutValue);
		}

		void ProgramObject::GetSubroutineUniformName(GLenum _Stage, GLuint _Index, std::string& _OutName)
		{
			GLint _MaxLength = 0;
			GetStageParameter(_Stage, GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, &_MaxLength);
			_OutName.resize(_MaxLength);
			glGetActiveSubroutineUniformName(__Handle, _Stage, _Index, _MaxLength, NULL, &_OutName[0]);
		}
	}
}
#ifndef __VOR_PROGRAM_OBJECT_HPP__
#define __VOR_PROGRAM_OBJECT_HPP__

#include "vorGLObject.hpp"
#include "vorShaderObject.hpp"

#include <string>
#include <vector>
#include <functional>

#include "../VortexCore/vorTMatrix4.hpp"
#include "../VortexCore/vorTVector3.hpp"
#include "../VortexCore/vorTVector4.hpp"

namespace vortex {
	namespace renderer {
		class GLPLUS_API ProgramObject : public GlObject<__GlAllocatorV, __GlDeallocatorU, __GlBindFunctionU> {
		public:
			ProgramObject(void)
				: GlObject(glCreateProgram, glDeleteProgram, glUseProgram, glIsProgram) { }

			ProgramObject(GLuint _Handle)
				: GlObject(_Handle, glDeleteProgram, glUseProgram, glIsProgram) { }

			void FromBinary(GLenum _BinaryFormat, const void* _Data, GLsizei _Length);

			void AttachShader(const ShaderObject& _Shader);
			void DetachShader(const ShaderObject& _Shader);

			bool Link(void);

			GLint GetAttributeLocation(const std::string& _AttributeName);
			GLint GetUniformLocation(const std::string& _UniformName);
			
			GLuint GetUniformBlockIndex(const std::string& _BlockName);
			std::vector<GLuint> GetUniformIndices(const std::vector<std::string>& _NameIndices);	

			void SetSubRoutines(ShaderType _TargetShader, GLsizei _RoutineCount, const GLuint* _RoutineIndices);

			void SetUniform(GLint _Location, const core::Matrix4f& _Value);
			void SetUniform(GLint _Location, const core::Vector3f& _Value);
			void SetUniform(GLint _Location, const core::Vector4f& _Value);
			
			void BindAttributeLocation(GLuint _TargetIndex, const std::string& _AttributeName);
			void BindFragmentDataLocation(GLuint _ColorNumber, const std::string& _Name);
			void BindFragmentDataLocation(GLuint _ColorNumber, GLuint _Index, const std::string& _Name);

			void GetAttachedShaders(std::vector<ShaderObject>& _OutShaders);

			void GetStageParameter(GLenum _Stage, GLenum _Parameter, GLint* _OutValue);
			void GetParameter(GLenum _Parameter, GLint* _OutValue);
			void SetParameter(GLenum _Parameter, GLint _Value);

			template<class R, class ... Args>
			R GetBinary(std::function<R(GLsizei _BinaryLength, GLenum _BinaryFormat, const void* _Data, Args ...)> _BinaryAccessor, Args ... _Arguments);

			std::string GetInformationLog(void);

			void SetupFeedbackVaryings(const std::vector<std::string>& _Varyings, GLenum _BufferMode);

			bool ValidateProgram(void);

			void GetAtomicCounterParameter(GLuint _BufferIndex, GLenum _Parameter, GLint* _OutValue);
			void GetAttributeParameters(GLuint _Index, GLint* _Size, GLenum* _Type, std::string& _Name);

			GLint GetSubRoutineIndex(const std::string& _RoutineName, ShaderType _TargetShader);
			void GetSubroutineName(GLenum _Stage, GLuint _Index, std::string& _OutName);
			void GetSubroutineParameter(GLenum _Stage, GLuint _Index, GLenum _Parameter, GLint* _OutValue);

			void GetSubroutineUniformName(GLenum _Stage, GLuint _Index, std::string& _OutName);
		};

		template<class R, class ... Args>
		R vortex::renderer::ProgramObject::GetBinary(std::function<R(GLsizei _BinaryLength, GLenum _BinaryFormat, const void* _Data, Args ...)> _BinaryAccessor, Args ... _Arguments)
		{
			GLint _BinaryLength = 0;
			GetParameter(GL_PROGRAM_BINARY_LENGTH, &_BinaryLength);
			void* _BinaryData = malloc(_BinaryLength);

			GLenum _BinaryFormat = 0;
			glGetProgramBinary(__Handle, _BinaryLength, NULL, &_BinaryFormat, _BinaryData);

			R& _Result = _BinaryAccessor(_BinaryLength, _BinaryFormat, _BinaryData, _Arguments);

			free(_BinaryData);

			return _Result;
		}
	}
}

#endif // ~__VOR_PROGRAM_OBJECT_HPP__
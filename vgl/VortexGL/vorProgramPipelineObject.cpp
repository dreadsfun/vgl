#include "vorProgramPipelineObject.hpp"

namespace vortex {
	namespace renderer {
		void ProgramPipelineObject::BindProgramStage(GLbitfield _Stages, const ProgramObject& _SourceProgram)
		{
			glUseProgramStages(__Handle, _Stages, _SourceProgram);
		}

		void ProgramPipelineObject::SetActiveProgram(const ProgramObject& _Program)
		{
			glActiveShaderProgram(__Handle, _Program);
		}

		void ProgramPipelineObject::GetParameter(GLenum _Parameter, GLint* _OutValue)
		{
			glGetProgramPipelineiv(__Handle, _Parameter, _OutValue);
		}

		std::string ProgramPipelineObject::GetInformationLog(void)
		{
			GLint _InfoLength = 0;
			GetParameter(GL_INFO_LOG_LENGTH, &_InfoLength);
			std::string _Result(_InfoLength, 0);

			glGetProgramPipelineInfoLog(__Handle, _InfoLength, NULL, &_Result[0]);
			return _Result;
		}

		bool ProgramPipelineObject::ValidatePipeline(void)
		{
			glValidateProgramPipeline(__Handle);
			GLint _Result = 0;
			GetParameter(GL_VALIDATE_STATUS, &_Result);
			return _Result == GL_TRUE;
		}
	}
}
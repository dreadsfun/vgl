#ifndef _PROGRAMPIPELINEOBJECT_HPP
#define _PROGRAMPIPELINEOBJECT_HPP

#include "vorGLObject.hpp"
#include "vorProgramObject.hpp"

namespace vortex {
	namespace renderer {
		class ProgramPipelineObject : public GlObject<__GlAllocatorSU, __GlDeallocatorSCU, __GlBindFunctionU> {
		public:
			ProgramPipelineObject(void)
				: GlObject(glGenProgramPipelines, glDeleteProgramPipelines, glBindProgramPipeline, glIsProgramPipeline) { }

			ProgramPipelineObject(GLuint _Handle)
				: GlObject(_Handle, glDeleteProgramPipelines, glBindProgramPipeline, glIsProgramPipeline) { }

			void BindProgramStage(GLbitfield _Stages, const ProgramObject& _SourceProgram);
			void SetActiveProgram(const ProgramObject& _Program);

			void GetParameter(GLenum _Parameter, GLint* _OutValue);

			std::string GetInformationLog(void);

			bool ValidatePipeline(void);
		};
	}
}
#endif
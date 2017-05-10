#ifndef __SAMPLER_OBJECT_HPP__
#define __SAMPLER_OBJECT_HPP__

#include "vorGLObject.hpp"

namespace vortex {
	namespace renderer {
		class SamplerObject : public GlObject < __GlAllocatorSU, __GlDeallocatorSCU, __GlBindFunctionUU > {
		public:
			SamplerObject(void)
				: GlObject(glGenSamplers, glDeleteSamplers, glBindSampler, glIsSampler) { }

			void SetParameter(GLenum _Parameter, GLfloat _Value);
			void SetParameter(GLenum _Parameter, GLint _Value);
		};
	}
}
#endif
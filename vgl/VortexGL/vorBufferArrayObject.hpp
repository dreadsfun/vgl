#ifndef _BUFFERARRAYOBJECT_HPP
#define _BUFFERARRAYOBJECT_HPP

#include "vorGLObject.hpp"
#include "vorBufferObject.hpp"

namespace vortex {
	namespace renderer {
		class GLPLUS_API BufferArrayObject : public GlObject<__GlAllocatorSU, __GlDeallocatorSCU, __GlBindFunctionU> {
		public:
			BufferArrayObject(void)
				: GlObject(glGenVertexArrays, glDeleteVertexArrays, glBindVertexArray, glIsVertexArray) { }

			BufferArrayObject(GLuint _Handle)
				: GlObject(_Handle, glDeleteVertexArrays, glBindVertexArray, glIsVertexArray) { }

			void BindElements(BufferObject* _ElementBuffer);
			void BindAttribute(GLint _Attribute, BufferObject* _Buffer, DataType _DataType,
				unsigned int _Count, unsigned int _Stride, const void* _Offset);
			void BindTransformFeedback(unsigned int _Index, const BufferObject& _Buffer);
		};
	}
}

#endif
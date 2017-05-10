#include "vorBufferArrayObject.hpp"

namespace vortex {
	namespace renderer {
		void BufferArrayObject::BindElements(BufferObject* _ElementBuffer)
		{
			glBindVertexArray(__Handle);
			_ElementBuffer->BindObject(BufferTarget::ELEMENT_ARRAY_BUFFER);
		}

		void BufferArrayObject::BindAttribute(GLint _Attribute, BufferObject* _Buffer, DataType _DataType,
			unsigned int _Count, unsigned int _Stride, const void* _Offset)
		{
			glBindVertexArray(__Handle);
			_Buffer->BindObject(BufferTarget::ARRAY_BUFFER);
			glEnableVertexAttribArray(_Attribute);
			glVertexAttribPointer(_Attribute, _Count, _DataType, GL_FALSE, _Stride, _Offset);
		}

		void BufferArrayObject::BindTransformFeedback(unsigned int _Index, const BufferObject& _Buffer)
		{

		}
	}
}
#include "vorBufferObject.hpp"

namespace vortex {
	namespace renderer {
		void BufferObject::BufferData(const void* _Data, size_t _Size, Usage _Usage)
		{
			glBufferData(__Target, _Size, _Data, _Usage);
		}

		void BufferObject::BufferSubData(const void* _Data, size_t _Offset, size_t _Size)
		{
			glBufferSubData(__Target, _Offset, _Size, _Data);
		}

		void BufferObject::GetData(void* _Out, size_t _Offset, size_t _Size)
		{
			glGetBufferSubData(__Target, _Offset, _Size, _Out);
		}

		void BufferObject::BindIndexedTarget(BufferTarget _Target, GLuint _Index)
		{
			glBindBufferBase(_Target, _Index, __Handle);
		}

		void BufferObject::BindIndexedTarget(BufferTarget _Target, GLuint _Index, GLintptr _Offset, GLsizeiptr _Size)
		{
			glBindBufferRange(_Target, _Index, __Handle, _Offset, _Size);
		}

		void BufferObject::BindBuffersIndexedTarget(BufferTarget _Target, GLuint _FirstIndex,
			GLsizei _Count, const std::vector<BufferObject>& _Buffers)
		{
			size_t _BufferCount = _Buffers.size();
			GLuint* _BufferHandles = new GLuint[_BufferCount];
			for (size_t i = 0; i < _BufferCount; i++) {
				_BufferHandles[i] = _Buffers[i];
			}
			glBindBuffersBase(_Target, _FirstIndex, _Count, _BufferHandles);
			delete[] _BufferHandles;
		}

		void BufferObject::BindBuffersIndexedTarget(BufferTarget _Target, GLuint _FirstIndex,
			GLsizei _Count, const std::vector<BufferObject>& _Buffers, const GLintptr* _Offsets, const GLintptr* _Sizes)
		{
			size_t _BufferCount = _Buffers.size();
			GLuint* _BufferHandles = new GLuint[_BufferCount];
			for (size_t i = 0; i < _BufferCount; i++) {
				_BufferHandles[i] = _Buffers[i];
			}
			glBindBuffersRange(_Target, _FirstIndex, _Count, _BufferHandles, _Offsets, _Sizes);
			delete[] _BufferHandles;
		}

		void BufferObject::BufferStorage(GLsizeiptr _Size, const GLvoid* _Data, GLbitfield _Usage)
		{
			glBufferStorage(__Target, _Size, _Data, _Usage);
		}

		void BufferObject::InvalidateData(void)
		{
			glInvalidateBufferData(__Handle);
		}

		void BufferObject::InvalidateData(GLintptr _Offset, GLsizeiptr _Size)
		{
			glInvalidateBufferSubData(__Handle, _Offset, _Size);
		}

		void BufferObject::GetMappedPointer(GLvoid** _OutPointer)
		{
			glGetBufferPointerv(__Target, GL_BUFFER_MAP_POINTER, _OutPointer);
		}

		void BufferObject::GetBufferParameter(BufferParameter _Parameter, GLint64* _OutValue)
		{
			glGetBufferParameteri64v(__Target, _Parameter, _OutValue);
		}

		void BufferObject::CopySubDataTo(const BufferObject& _Destination, GLintptr _ReadOffset, GLintptr _WriteOffset, GLsizeiptr _Size)
		{
			glCopyBufferSubData(__Target, _Destination.__Target, _ReadOffset, _WriteOffset, _Size);
		}

		void BufferObject::ClearSubData(GLenum _InternalFormat, GLintptr _Offset, GLsizeiptr _Size, PixelDataFormat _Format, GLenum _Type, const void* _Data)
		{
			glClearBufferSubData(__Target, _InternalFormat, _Offset, _Size, _Format, _Type, _Data);
		}

		void BufferObject::ClearData(GLenum _InternalFormat, PixelDataFormat _Format, GLenum _Type, const void* _Data)
		{
			glClearBufferData(__Target, _InternalFormat, _Format, _Type, _Data);
		}
	}
}
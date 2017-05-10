#ifndef _BUFFEROBJECT_HPP
#define _BUFFEROBJECT_HPP

#include "vorGLObject.hpp"
#include "enBufferObject.hpp"

#include <functional>
#include <vector>

namespace vortex {
	namespace renderer {
		class GLPLUS_API BufferObject : public GlObject<__GlAllocatorSU, __GlDeallocatorSCU, __GlBindFunctionEU> {
		public:
			BufferObject(void)
				: GlObject(glGenBuffers, glDeleteBuffers, glBindBuffer, glIsBuffer) { }

			BufferObject(GLuint _Handle)
				: GlObject(_Handle, glDeleteBuffers, glBindBuffer, glIsBuffer) { }

			void BindIndexedTarget(BufferTarget _Target, GLuint _Index);
			void BindIndexedTarget(BufferTarget _Target, GLuint _Index, GLintptr _Offset, GLsizeiptr _Size);

			static void BindBuffersIndexedTarget(BufferTarget _Target, GLuint _FirstIndex,
				GLsizei _Count, const std::vector<BufferObject>& _Buffers);
			static void BindBuffersIndexedTarget(BufferTarget _Target, GLuint _FirstIndex,
				GLsizei _Count, const std::vector<BufferObject>& _Buffers, const GLintptr* _Offsets, const GLintptr* _Sizes);

			void BufferData(const void* _Data, size_t _Size, Usage _Usage);
			void BufferStorage(GLsizeiptr _Size, const GLvoid* _Data, GLbitfield _Usage);
			void BufferSubData(const void* _Data, size_t _Offset, size_t _Length);

			void InvalidateData(void);
			void InvalidateData(GLintptr _Offset, GLsizeiptr _Size);

			void GetData(void* _Out, size_t _Offset, size_t _Size);
			void GetMappedPointer(GLvoid** _OutPointer);
			void GetBufferParameter(BufferParameter _Parameter, GLint64* _OutValue);

			void CopySubDataTo(const BufferObject& _Destination, GLintptr _ReadOffset, GLintptr _WriteOffset, GLsizeiptr _Size);
			void ClearSubData(GLenum _InternalFormat, GLintptr _Offset, GLsizeiptr _Size, PixelDataFormat _Format, GLenum _Type, const void* _Data);
			void ClearData(GLenum _InternalFormat, PixelDataFormat _Format, GLenum _Type, const void* _Data);

			template<class R, class ... Args>
			R MapReadBuffer(std::function<R(const void*, Args ...)> _Accessor, Args ... _AccessorArguments);
			template<class R, class ... Args>
			R MapReadBuffer(std::function<R(const void*, Args ...)> _Accessor, Args ... _AccessorArguments, GLintptr _Offset, GLsizeiptr _Size);

			template<class R, class ... Args>
			R MapWriteBuffer(std::function<R(void*, Args ...)> _Accessor, Args ... _AccessorArguments);
			template<class R, class ... Args>
			R MapWriteBuffer(std::function<R(void*, Args ...)> _Accessor, Args ... _AccessorArguments, GLintptr _Offset, GLsizeiptr _Size);
		};

		template<class R, class ... Args>
		R vortex::renderer::BufferObject::MapWriteBuffer(std::function<R(void*, Args ...)> _Accessor, Args ... _AccessorArguments, GLintptr _Offset, GLsizeiptr _Size) {
			void* _Mapping = glMapBufferRange(__Target, _Offset, _Size, GL_READ_WRITE);
			R& _Result = _Accessor(_Mapping, _AccessorArguments);
			glFlushMappedBufferRange(__Target, 0, _Size);
			glUnmapBuffer(__Target);
			return _Result;
		}

		template<class R, class ... Args>
		R vortex::renderer::BufferObject::MapReadBuffer(std::function<R(const void*, Args ...)> _Accessor, Args ... _AccessorArguments, GLintptr _Offset, GLsizeiptr _Size) {
			void* _Mapping = glMapBufferRange(__Target, _Offset, _Size, GL_READ_ONLY);
			R& _Result = _Accessor(_Mapping, _AccessorArguments);
			glFlushMappedBufferRange(__Target, 0, _Size);
			glUnmapBuffer(__Target);
			return _Result;
		}

		template<class R, class ... Args>
		R vortex::renderer::BufferObject::MapWriteBuffer(std::function<R(void*, Args ...)> _Accessor, Args ... _AccessorArguments) {
			void* _Mapping = glMapBuffer(__Target, GL_READ_WRITE);
			R& _Result = _Accessor(_Mapping, _AccessorArguments);
			GLint64 _BufferLength = 0;
			GetBufferParameter(BUFFER_SIZE, &_BufferLength);
			glFlushMappedBufferRange(__Target, 0, _BufferLength);
			glUnmapBuffer(__Target);
			return _Result;
		}

		template<class R, class ... Args>
		R vortex::renderer::BufferObject::MapReadBuffer(std::function<R(const void*, Args ...)> _Accessor, Args ... _AccessorArguments) {
			void* _Mapping = glMapBuffer(__Target, GL_READ_ONLY);
			R& _Result = _Accessor(_Mapping, _AccessorArguments);
			GLint64 _BufferLength = 0;
			GetBufferParameter(BUFFER_SIZE, &_BufferLength);
			glFlushMappedBufferRange(__Target, 0, _BufferLength);
			glUnmapBuffer(__Target);
			return _Result;
		}
	}
}
#endif
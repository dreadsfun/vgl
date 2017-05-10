#include "vorSyncObject.hpp"

namespace vortex {
	namespace renderer {
		vortex::renderer::SyncObject SyncObject::PushFence(GLenum _Condition, GLbitfield _Flags)
		{
			SyncObject _Sync;
			_Sync.__Handle = glFenceSync(_Condition, _Flags);
			return _Sync;
		}

		bool SyncObject::IsSignaled(void)
		{
			if (__Handle == nullptr)
			{
				return false;
			}

			GLint _Signaled = 0;
			glGetSynciv(__Handle, GL_SYNC_STATUS, 1, nullptr, &_Signaled);

			return _Signaled == GL_SIGNALED;
		}

		void SyncObject::JoinServer(GLbitfield _Flags, GLuint64 _TimeOut)
		{
			if (__Handle == nullptr)
			{
				return;
			}

			glWaitSync(__Handle, _Flags, _TimeOut);
		}

		void SyncObject::JoinClient(GLbitfield _Flags, GLuint64 _TimeOut)
		{
			if (__Handle == nullptr)
			{
				return;
			}

			glClientWaitSync(__Handle, _Flags, _TimeOut);
		}

		void SyncObject::Release(void)
		{
			glDeleteSync(__Handle);
		}
	}
}
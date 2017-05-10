#ifndef _SYNCOBJECT_HPP
#define _SYNCOBJECT_HPP

#include "vorGLObject.hpp"

namespace vortex {
	namespace renderer {
		class SyncObject {
		public:
			static SyncObject PushFence(GLenum _Condition, GLbitfield _Flags);

			void Release(void);

			bool IsSignaled(void);

			void JoinServer(GLbitfield _Flags, GLuint64 _TimeOut);
			void JoinClient(GLbitfield _Flags, GLuint64 _TimeOut);

			operator GLsync () const {
				return __Handle;
			}

			SyncObject(const SyncObject& _Other) :
				__Handle(_Other.__Handle) { }

		private:
			SyncObject(void)
				: __Handle(nullptr) { }

			GLsync __Handle;
		};
	}
}
#endif
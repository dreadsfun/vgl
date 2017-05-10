#ifndef __QUERY_OBJECT_HPP
#define __QUERY_OBJECT_HPP

#include "vorGLObject.hpp"

namespace vortex {
	namespace renderer {
		class QueryObject : public GlObject<__GlAllocatorSU, __GlDeallocatorSCU, __NoBindFunction>{
		public:
			QueryObject(void)
				: GlObject(glGenQueries, glDeleteQueries, 0, glIsQuery) { }

			void BeginQuery(GLenum _QueryType);
			void EndQuery(void);

			bool IsResultAvailable(void);

			GLint64 WaitResult(void);
			GLint64 NoWaitResult(void);

		private:
			GLenum __QueryType;
		};
	}
}

#endif
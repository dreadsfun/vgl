#include "vorQueryObject.hpp"

namespace vortex {
	namespace renderer {
		void QueryObject::BeginQuery(GLenum _QueryType)
		{
			__QueryType = _QueryType;
			glBeginQuery(_QueryType, __Handle);
		}

		void QueryObject::EndQuery(void)
		{
			glEndQuery(__QueryType);
		}

		bool QueryObject::IsResultAvailable(void)
		{
			GLint _Param = 0;
			glGetQueryObjectiv(__Handle, GL_QUERY_RESULT_AVAILABLE, &_Param);
			return _Param != 0;
		}

		GLint64 QueryObject::WaitResult(void)
		{
			GLint64 _Result = 0;
			glGetQueryObjecti64v(__Handle, GL_QUERY_RESULT, &_Result);
			return _Result;
		}

		GLint64 QueryObject::NoWaitResult(void)
		{
			GLint64 _Result = 0;
			glGetQueryObjecti64v(__Handle, GL_QUERY_RESULT_NO_WAIT, &_Result);
			return _Result;
		}
	}
}
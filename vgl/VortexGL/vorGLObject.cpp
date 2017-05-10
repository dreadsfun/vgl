#include "vorGLObject.hpp"

namespace vortex {
	namespace renderer {
		template<>
		void GlBindHelper<__GlBindFunctionEU, GLuint>::BindObject(__GlBindFunctionEU* _Binder, GLenum _Target, GLuint _Handle)
		{
			_Binder(_Target, _Handle);
		}

		template<>
		void GlBindHelper<__GlBindFunctionU, GLuint>::BindObject(__GlBindFunctionU* _Binder, GLenum _Target, GLuint _Handle)
		{
			_Binder(_Handle);
		}
		
		template<>
		void GlBindHelper<__GlBindFunctionU, GLuint>::BindObject(__GlBindFunctionU* _Binder, GLuint _Handle)
		{
			_Binder(_Handle);
		}

		template<>
		void GlBindHelper<__GlBindFunctionEU, GLuint>::BindObject(__GlBindFunctionEU* _Binder, GLuint _Handle)
		{
			_Binder(0, _Handle);
		}

		template<>
		void GlBindHelper<__NoBindFunction, GLuint>::BindObject(__NoBindFunction* _Binder, GLuint _Handle)
		{
			return;
		}

		template<>
		void GlBindHelper<__GlBindFunctionU, GLuint>::ClearBindSlot(__GlBindFunctionU* _Binder, GLenum _Target)
		{
			_Binder(0);
		}

		template<>
		void GlBindHelper<__GlBindFunctionEU, GLuint>::ClearBindSlot(__GlBindFunctionEU* _Binder, GLenum _Target)
		{
			_Binder(_Target, 0);
		}

		template<>
		void GlBindHelper<__NoBindFunction, GLuint>::ClearBindSlot(__NoBindFunction* _Binder, GLenum _Target)
		{
			return;
		}

		template<>
		void GlBindHelper<__NoBindFunction, GLuint>::BindObject(__NoBindFunction* _Binder, GLenum _Target, GLuint _Handle)
		{
			return;
		}
	}
}
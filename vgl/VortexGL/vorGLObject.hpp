#ifndef _GLOBJECT_HPP
#define _GLOBJECT_HPP

#include "vorGLPlusShared.hpp"
#include "vorGLObjectPool.hpp"

#include <glew\glew.h>
#include <gl/GL.h>

namespace vortex {
	namespace renderer {
		enum DataType {
			BYTE = GL_BYTE,
			UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
			SHORT = GL_SHORT,
			UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
			INT = GL_INT,
			UNSIGNED_INT = GL_UNSIGNED_INT,
			FLOAT = GL_FLOAT,
			DOUBLE = GL_DOUBLE
		};

		typedef void GLAPICALL __GlBindFunctionUU(GLuint, GLuint);
		typedef void GLAPICALL __GlBindFunctionEU(GLenum, GLuint);
		typedef void GLAPICALL __GlBindFunctionU(GLuint);
		typedef void GLAPICALL __NoBindFunction(void);

		typedef GLboolean GLAPICALL __GlValidatorFuncU(GLuint);

		template<class B, class NT = GLuint>
		class GlBindHelper {
		public:
			void BindObject(B* _Binder, GLenum _Target, NT _Handle);
			void BindObject(B* _Binder, NT _Handle);
			void ClearBindSlot(B* _Binder, GLenum _Target);
		};

		template<class A, class DA, class B, class NT = GLuint>
		class GlObject {
		public:
			virtual ~GlObject(void);

			void BindObject(GLenum _Target);
			void BindObject(void);
			void ClearBindSlot(void);

			bool ValidateObject(void);
			bool ValidateObject(NT _Handle);

			void operator = (const GlObject<A, DA, B, NT>& _Other);

			const GLenum& Target(void) const {
				return __Target;
			}

			const NT& Handle(void) const {
				return __Handle;
			}

			operator NT () const {
				return __Handle;
			}

		protected:
			GlObject(NT _Handle, DA* _Deallocator, B* _Binder, __GlValidatorFuncU* _Validator);
			GlObject(A* _Allocator, DA* _Deallocator, B* _Binder, __GlValidatorFuncU* _Validator);
			GlObject(A* _Allocator, DA* _Deallocator, GLenum _AllocationTarget, B* _Binder, __GlValidatorFuncU* _Validator);
			GlObject(const GlObject<A, DA, B, NT>& _Other);

			NT __Handle;
			GLenum __Target;

			A* __Allocator;
			DA* __Deallocator;
			B* __Binder;
			__GlValidatorFuncU* __Validator;

			static GlObjectPool __ObjectPool;
			static GlBindHelper<B, NT> __BindHelper;
		};

		template<class A, class DA, class B, class NT /*= GLuint*/>
		void vortex::renderer::GlObject<A, DA, B, NT>::BindObject(void)
		{
			__BindHelper.BindObject(__Binder, __Handle);
		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		void vortex::renderer::GlObject<A, DA, B, NT>::ClearBindSlot(void)
		{
			__BindHelper.ClearBindSlot(__Binder, __Target);
		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		bool vortex::renderer::GlObject<A, DA, B, NT>::ValidateObject(NT _Handle)
		{
			return __Validator(_Handle) == GL_TRUE;
		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		bool vortex::renderer::GlObject<A, DA, B, NT>::ValidateObject(void)
		{
			return __Validator(__Handle) == GL_TRUE;
		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		vortex::renderer::GlObject<A, DA, B, NT>::GlObject(A* _Allocator, DA* _Deallocator,
			GLenum _AllocationTarget, B* _Binder, __GlValidatorFuncU* _Validator)
			: __Allocator(_Allocator),
			__Deallocator(_Deallocator),
			__Binder(_Binder),
			__Target(0),
			__Validator(_Validator)
		{
			__Handle = __ObjectPool.GrabHandle(__Allocator, _AllocationTarget);
		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		vortex::renderer::GlObject<A, DA, B, NT>::GlObject(const GlObject<A, DA, B, NT>& _Other)
			: __Target(_Other.__Target),
			__Allocator(_Other.__Allocator),
			__Deallocator(_Other.__Deallocator),
			__Handle(_Other.__Handle),
			__Binder(_Other.__Binder),
			__Validator(_Other.__Validator)
		{
			__ObjectPool.Copy(__Allocator, __Handle);
		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		vortex::renderer::GlObject<A, DA, B, NT>::GlObject(A* _Allocator, DA* _Deallocator, B* _Binder, __GlValidatorFuncU* _Validator)
			: __Target(0),
			__Allocator(_Allocator),
			__Deallocator(_Deallocator),
			__Binder(_Binder),
			__Validator(_Validator)
		{
			__Handle = __ObjectPool.GrabHandle(__Allocator);
		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		vortex::renderer::GlObject<A, DA, B, NT>::GlObject(NT _Handle, DA* _Deallocator, B* _Binder, __GlValidatorFuncU* _Validator)
			: __Target(0),
			__Handle(_Handle),
			__Deallocator(_Deallocator),
			__Binder(_Binder),
			__Validator(_Validator)
		{

		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		void vortex::renderer::GlObject<A, DA, B, NT>::operator=(const GlObject<A, DA, B, NT>& _Other)
		{
			__Handle = _Other.__Handle;
			__Target = _Other.__Target;
			__Deallocator = _Other.__Deallocator;
			__Allocator = _Other.__Allocator;
			__Binder = _Other.__Binder;
			__Validator = _Other.__Validator;
			__ObjectPool.Copy(__Allocator, __Handle);
		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		void vortex::renderer::GlObject<A, DA, B, NT>::BindObject(GLenum _Target)
		{
			__Target = _Target;
			__BindHelper.BindObject(__Binder, __Target, __Handle);
		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		vortex::renderer::GlObject<A, DA, B, NT>::~GlObject(void)
		{
			__ObjectPool.DropHandle(__Allocator, __Handle, __Deallocator);
		}

		template<class A, class DA, class B, class NT /*= GLuint*/>
		GlBindHelper<B, NT> vortex::renderer::GlObject<A, DA, B, NT>::__BindHelper;

		template<class A, class DA, class B, class NT /*= GLuint*/>
		GlObjectPool GlObject<A, DA, B, NT>::__ObjectPool;
	}
}
#endif
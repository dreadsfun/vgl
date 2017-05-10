#include "vorGLObjectPool.hpp"

namespace vortex {
	namespace renderer {
		void GlObjectPool::Copy(void* _Target, GLuint _Handle)
		{
			__ObjectPool[_Target][_Handle]++;
		}

		template<>
		void GlObjectPool::DropHandle(void* _Target, GLuint _Handle, __GlDeallocatorU _Deallocator)
		{
			std::unordered_map<GLuint, unsigned int>& _TargetReferenceMap = __ObjectPool[_Target];
			auto _FIt = _TargetReferenceMap.find(_Handle);

			if (_FIt != _TargetReferenceMap.end())
			{
				if (_FIt->second > 0)
				{
					_FIt->second--;

					if (_FIt->second == 0)
					{
						_Deallocator(_Handle);
						_TargetReferenceMap.erase(_FIt);
					}
				}
			}
		}

		template<>
		void GlObjectPool::DropHandle(void* _Target, GLuint _Handle, __GlDeallocatorSCU _Deallocator)
		{
			std::unordered_map<GLuint, unsigned int>& _TargetReferenceMap = __ObjectPool[_Target];
			auto _FIt = _TargetReferenceMap.find(_Handle);

			if (_FIt != _TargetReferenceMap.end())
			{
				if (_FIt->second > 0)
				{
					_FIt->second--;

					if (_FIt->second == 0)
					{
						_Deallocator(1, &_Handle);
						_TargetReferenceMap.erase(_FIt);
					}
				}
			}
		}

		template<>
		void GlObjectPool::DropHandle(void* _Target, GLuint _Handle, __GlDeallocatorSU* _Deallocator)
		{
			std::unordered_map<GLuint, unsigned int>& _TargetReferenceMap = __ObjectPool[_Target];
			auto _FIt = _TargetReferenceMap.find(_Handle);

			if (_FIt != _TargetReferenceMap.end())
			{
				if (_FIt->second > 0)
				{
					_FIt->second--;

					if (_FIt->second == 0)
					{
						_Deallocator(1, &_Handle);
						_TargetReferenceMap.erase(_FIt);
					}
				}
			}
		}

		template<>
		GLuint GlObjectPool::GrabHandle<__GlAllocatorE>(__GlAllocatorE* _Allocator, GLenum _Target)
		{
			GLuint _NewHandle = _Allocator(_Target);
			__ObjectPool[_Allocator][_NewHandle]++;
			return _NewHandle;
		}

		template<>
		GLuint GlObjectPool::GrabHandle<__GlAllocatorSU>(__GlAllocatorSU* _Allocator, GLenum _Target)
		{
			return 0;
		}

		template<>
		GLuint GlObjectPool::GrabHandle<__GlAllocatorV>(__GlAllocatorV* _Allocator, GLenum _Target)
		{
			return 0;
		}

		// This is impossible to be called.
		// Specialization only needed for compilation.
		template<>
		GLuint GlObjectPool::GrabHandle<__GlAllocatorE>(__GlAllocatorE* _Allocator)
		{
			return 0;
		}

		template<>
		GLuint GlObjectPool::GrabHandle<__GlAllocatorSU>(__GlAllocatorSU* _Allocator)
		{
			GLuint _NewHandle = 0;
			_Allocator(1, &_NewHandle);
			__ObjectPool[_Allocator][_NewHandle]++;
			return _NewHandle;
		}

		template<>
		GLuint GlObjectPool::GrabHandle<__GlAllocatorV>(__GlAllocatorV* _Allocator)
		{
			GLuint _NewHandle = _Allocator();
			__ObjectPool[_Allocator][_NewHandle]++;
			return _NewHandle;
		}
	}
}
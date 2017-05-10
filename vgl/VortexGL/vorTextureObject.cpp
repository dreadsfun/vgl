#include "vorTextureObject.hpp"

namespace vortex {
	namespace renderer {
		void TextureObject::BufferTextureData(GLint _InternalFormat, GLsizei _Width,
			GLsizei _Height, GLenum _Format, GLenum _DataType, const void* _Pixels)
		{
			glTexImage2D(__Target, 0, _InternalFormat, _Width, _Height, 0, _Format, _DataType, _Pixels);
		}

		void TextureObject::SetWrapType(WrapTarget _Target, WrapType _Type)
		{
			glTexParameteri(__Target, _Target, _Type);
		}

		void TextureObject::SetWrapType(WrapType _S, WrapType _T)
		{
			glTexParameteri(__Target, GL_TEXTURE_WRAP_S, _S);
			glTexParameteri(__Target, GL_TEXTURE_WRAP_T, _T);
		}

		void TextureObject::GenerateMipmaps(void)
		{
			glGenerateMipmap(__Target);
		}

		void TextureObject::SetFilterTypes(FilterType _Minimizing, FilterType _Magnifying)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _Minimizing);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _Magnifying);
		}
		
		void TextureObject::BufferTextureSubData(GLint _ImageLevel, GLint _XOffset, GLint _YOffset, GLsizei _Width,
			GLsizei _Height, GLenum _Format, GLenum _DataType, const void* _Pixels)
		{
			glTexSubImage2D(__Target, _ImageLevel, _XOffset, _YOffset, _Width, _Height, _Format, _DataType, _Pixels);
		}
	}
}
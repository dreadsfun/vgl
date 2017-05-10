#ifndef _TEXTUREOBJECT_HPP
#define _TEXTUREOBJECT_HPP

#include "vorGLObject.hpp"

namespace vortex {
	namespace renderer {
		enum InternalTextureFormat
		{
			COMPRESSED_RED = GL_COMPRESSED_RED,
			COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1,
			COMPRESSED_RG = GL_COMPRESSED_RG,
			COMPRESSED_RGB = GL_COMPRESSED_RGB,
			COMPRESSED_RGBA = GL_COMPRESSED_RGBA,
			COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2,
			COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
			COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2,
			COMPRESSED_SRGB = GL_COMPRESSED_SRGB,
//			DEPTH_STENCIL = GL_DEPTH_STENCIL,
			DEPTH_24_STENCIL_8 = GL_DEPTH24_STENCIL8,
			DEPTH_32F_STENCIL_8 = GL_DEPTH32F_STENCIL8,
//			DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
			DEPTH_COMPONENT_16 = GL_DEPTH_COMPONENT16,
			DEPTH_COMPONENT_24 = GL_DEPTH_COMPONENT24,
			DEPTH_COMPONENT_32F = GL_DEPTH_COMPONENT32F,
			R_16F = GL_R16F,
			R_16I = GL_R16I,
			R_16_S_Norm = GL_R16_SNORM,
			R_16UI = GL_R16UI,
			R_32F = GL_R32F,
			R_32I = GL_R32I,
			R_32UI = GL_R32UI,
			R_3_G_3_B_2 = GL_R3_G3_B2,
			R_8 = GL_R8,
			R_8I = GL_R8I,
			R_8_S_Norm = GL_R8_SNORM,
			R_8UI = GL_R8UI,
			Red = GL_RED,
//			RG = GL_RG,
			RG_16 = GL_RG16,
			RG_16F = GL_RG16F,
			RG_16_S_Norm = GL_RG16_SNORM,
			RG_32F = GL_RG32F,
			RG_32I = GL_RG32I,
			RG_32UI = GL_RG32UI,
			RG_8 = GL_RG8,
			RG_8I = GL_RG8I,
			RG_8_S_Norm = GL_RG8_SNORM,
			RG_8UI = GL_RG8UI,
			RGB_10 = GL_RGB10,
			RGB_10_A_2 = GL_RGB10_A2,
			RGB_12 = GL_RGB12,
			RGB_16 = GL_RGB16,
			RGB_16F = GL_RGB16F,
			RGB_16I = GL_RGB16I,
			RGB_16UI = GL_RGB16UI,
			RGB_32F = GL_RGB32F,
			RGB_32I = GL_RGB32I,
			RGB_32UI = GL_RGB32UI,
			RGB_4 = GL_RGB4,
			RGB_5 = GL_RGB5,
			RGB_5_A_1 = GL_RGB5_A1,
			RGB_8 = GL_RGB8,
			RGB_8I = GL_RGB8I,
			RGB_8UI = GL_RGB8UI,
			RGB_9_E_5 = GL_RGB9_E5,
			RGBA_12 = GL_RGBA12,
			RGBA_16 = GL_RGBA16,
			RGBA_16F = GL_RGBA16F,
			RGBA_16I = GL_RGBA16I,
			RGBA_16UI = GL_RGBA16UI,
			RGBA_2 = GL_RGBA2,
			RGBA_32F = GL_RGBA32F,
			RGBA_32I = GL_RGBA32I,
			RGBA_32UI = GL_RGBA32UI,
			RGBA_4 = GL_RGBA4,
			RGBA_8 = GL_RGBA8,
			RGBA_8UI = GL_RGBA8UI,
			SRGB_8 = GL_SRGB8,
			SRGB_8_ALPHA_8 = GL_SRGB8_ALPHA8,
			SRGB_ALPHA = GL_SRGB_ALPHA
		};

		enum TextureDataFormat {
//			RED = GL_RED,
//			RGB = GL_RGB,
//			BGR = GL_BGR,
//			RGBA = GL_RGBA,
//			BGRA = GL_BGRA
		};
		
		enum WrapType {
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
			REPEAT = GL_REPEAT,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT
		};

		enum WrapTarget {
			TARGET_S = GL_TEXTURE_WRAP_S,
			TARGET_T = GL_TEXTURE_WRAP_T,
			TARGET_R = GL_TEXTURE_WRAP_R
		};

		enum FilterType {
			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR,
			NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
			LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
			LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
		};

		class GLPLUS_API TextureObject : public GlObject<__GlAllocatorSU, __GlDeallocatorSCU, __GlBindFunctionEU> {
		public:
			TextureObject(void)
				: GlObject(glGenTextures, glDeleteTextures, glBindTexture, glIsTexture) { }

			TextureObject(GLuint _Handle)
				: GlObject(_Handle, glDeleteTextures, glBindTexture, glIsTexture) { }

			void BufferTextureData(GLint _InternalFormat, GLsizei _Width,
				GLsizei _Height, GLenum _Format, GLenum _DataType, const void* _Pixels);

			void BufferTextureSubData(GLint _ImageLevel, GLint _XOffset, GLint _YOffset, GLsizei _Width,
				GLsizei _Height, GLenum _Format, GLenum _DataType, const void* _Pixels);

			void SetWrapType(WrapTarget _Target, WrapType _Type);
			void SetWrapType(WrapType _S, WrapType _T);
			void GenerateMipmaps(void);
			void SetFilterTypes(FilterType _Minimizing, FilterType _Magnifying);
		};
	}
}
#endif
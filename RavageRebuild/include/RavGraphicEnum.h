#ifndef RAVGRAPHICENUM_H_INCLUDED
#define RAVGRAPHICENUM_H_INCLUDED

namespace Ravage
{
	enum LockingFlag
	{
		LOCK_READ,
		LOCK_WRITE,
		LOCK_READ_WRITE
	};

	enum GraphicResourceType
	{
		GR_TYPE_STATIC,
		GR_TYPE_DYNAMIC
	};

	enum IndexBufferType
	{
		IB_TYPE_16,
		IB_TYPE_32
	};

	enum GraphicCoordSystem
	{
		GCS_LEFT_HANDED,
		GCS_RIGHT_HANDED
	};

	enum ShaderType
	{
		ST_VERTEX,
		ST_GEOMETRY,
		ST_PIXEL
	};

	enum ClearMask
	{
		CM_TARGET = 1,
		CM_STENCIL = 2,
		CM_DEPTH = 4
	};

	enum FilterMode
	{
		FM_POINT,
		FM_BILINEAR,
		FM_TRILINEAR
	};

	enum TexWrapMode
	{
		TWM_REPEAT,
		TWM_CLAMP
	};

	enum RenderTextureFormat
	{
		RTF_R8,
		RTF_RG8,
		RTF_RGB8,
		RTF_RGBA8,
		RTF_R32F,
		RTF_RG32F,
		RTF_RGB32F,
		RTF_RGBA32F
	};

	enum TextureFormat
	{
		TF_A8,
		TF_RGB24,
		TF_RGBA32
	};

	//TODO: THIS: WARP, FOG... (NO ALPHA TEST, NO SHAPE MODE)
	enum RenderState
	{
		RS_ZENABLE,
		RS_ZFUNC,
		RS_ZVALUE,
		RS_CLEARCOLOR,
		RS_FILLMODE,
		RS_SRCBLEND,
		RS_DSTBLEND,
		RS_BLENDOP,
		RS_BLENDFACTOR
	};

	enum FillMode
	{
		FILL_POINT = 0,
		FILL_WIREFRAME,
		FILL_SOLID,
	};

	enum Blend
	{
		BLEND_ZERO = 0,
		BLEND_ONE,
		BLEND_SRCCOLOR,
		BLEND_INVSRCCOLOR,
		BLEND_SRCALPHA,
		BLEND_INVSRCALPHA,
		BLEND_DESTALPHA,
		BLEND_INVDESTALPHA,
		BLEND_DESTCOLOR,
		BLEND_INVDESTCOLOR,
		BLEND_BLENDFACTOR,
		BLEND_INVBLENDFACTOR
	};

	enum BlendOp
	{
		BLEND_ADD = 0,
		BLEND_SUBSTRUCT,
		BLEND_REVSUBSTRUCT,
		BLEND_MIN,
		BLEND_MAX
	};

	enum CmpFunc
	{
		CMP_NEVER = 0,
		CMP_LESS,
		CMP_EQUAL,
		CMP_LESSEQUAL,
		CMP_GREATER,
		CMP_NOTEQUAL,
		CMP_GREATEREQUAL,
		CMP_ALWAYS
	};
}

#endif /* RAVGRAPHICENUM_H_INCLUDED */
#pragma once

#ifndef __ENGINE_ENUM_H__

BEGIN(Engine)

enum class eWinMode
{ 
	Full,
	Window
};

enum class eRenderID
{
	Priority,
	NoAlpha,
	Alpha,
	UI,
	End
};

enum class eComponentID
{
	Transform,
	VIBuffer,
	StaticMesh,
	DynamicMesh,
	Texture,
	End
};

enum class eResourcesID
{
	StaticMesh,
	DynamicMesh,
	NaviMesh,
	Texture,
	End
};

enum eTransform 
{
	Scale,
	Rotate,
	Posision,
	Revolve,
	End
};

END

#define __ENGINE_ENUM_H__
#endif
#pragma once

#ifndef __ENGINE_ENUM_H__

BEGIN(Engine)

enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };
enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

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

ENUMSPACES(eComponentID)
{
	Transform,
	VIBuffer,
	StaticMesh,
	DynamicMesh,
	NaviMesh,
	Texture,
	CColliderBox,
	End
};
END

ENUMSPACES(eResourcesID)
{
	StaticMesh,
	DynamicMesh,
	NaviMesh,
	Texture,
	End
};
END

ENUMSPACES(eTransform)
{
	Scale,
	Rotate,
	Posision,
	Revolve,
	End
};
END
// CLine
ENUMSPACES(eLinePt)
{ 
	Start, 
	Last, 
	End 
};
END

ENUMSPACES(eRelationLine)
{
	OutLine,
	InLine
};
END

//CCell

ENUMSPACES(eCellpt)
{
	A,B,C,
	End
};
END
ENUMSPACES(eNeighbor)
{
	AB,
	BC,
	CA,
	End
};
END
ENUMSPACES(eLineID)
{
		AB,
		BC,
		CA,
		End
};
END
ENUMSPACES(eCompare)
{
	Move,
	Stop,
	End
};
END

ENUMSPACES(eCellType)
{
		Base,
		Leave,
		Connect,
		End
};
END

ENUMSPACES(eFileType)
{
		Obj,
		Dat,
		End
};
END

ENUMSPACES(eTextureType)
{
	Nomal,
		Cube,
		End
};
END


END // for  Engine


#define __ENGINE_ENUM_H__
#endif
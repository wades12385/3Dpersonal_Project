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

ENUMSPACES(eResourcesID)
{
	StaticMesh,
	DynamicMesh,
	NaviMesh,
	Texture,
	End
};
END

enum eTransform 
{
	Scale,
	Rotate,
	Posision,
	Revolve,
	End
};

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

END // for  Engine

#define __ENGINE_ENUM_H__
#endif
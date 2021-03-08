#pragma once
#ifndef __TOOLENUM_H__

ENUMSPACES(eToolScene)
{
	NaviModify,StaticObject,Dynamic, BoxDeploy,End
};
END

ENUMSPACES(eClickOption)
{
	Create, Peeking, End
};
END

ENUMSPACES(eBoxType)
{
	Collision, Trigger, End
};
END

ENUMSPACES(ePeekingMod)
{
	VTX,CELL,End
};
END
ENUMSPACES(eFloat3)
{
	X, Y, Z,End
};
END

ENUMSPACES(eStaticItemPeek)
{
	Create, Delete, Modify, None, End
};
END

#endif
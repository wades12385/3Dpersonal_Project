#pragma once
#ifndef __ENGINE_INCLUDE_H__

#pragma warning(disable : 4251)

#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>



#include <d3d9.h>
#include <d3dx9.h>

#include "Engine_Define.h"
#include "Engine_Typedef.h"
#include "Engine_Enum.h"
#include "Engine_Struct.h"
#include "Engine_Function.h"

#ifdef _DEBUG
#include <iostream>
#endif

#ifndef __MFCTOOL

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif

#endif

#endif

using namespace std;
using namespace Engine;

#define __ENGINE_INCLUDE_H__
#endif
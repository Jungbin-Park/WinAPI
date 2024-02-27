#pragma once


#include <Windows.h>
#include <vector>	// 동적배열
#include <list>		// 연결형 리스트
#include <map>		// 이진탐색트리
#include <string>   // 문자열 전용 관리 
#include <assert.h>

// TransParentBlt이 구현되어있는 라이브러리 링크
#pragma comment(lib, "Msimg32.lib")

using std::vector;
using std::list;
using std::map;
using std::make_pair;

using std::string;
using std::wstring;

#include "define.h"
#include "enum.h"
#include "struct.h"	
#include "func.h"

#include "CSelectObj.h"
#pragma once

namespace MAPTOOL
{
	enum ID { TILE, OBJECT, LINE, ID_END };
};

namespace LAYER
{
	enum ID { FLOOR1, FLOOR2, ID_END };
	static const wstring str[] = { L"1��", L"2��" };
}

namespace E_TILE
{
	enum OPTION { OPTION_END };
}
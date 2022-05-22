#pragma once
#include <cstdint>
#include <wtypes.h>
#include <vector>

struct _globals
{
	uint64_t World;
	uint64_t Entitylist;
	uint64_t Entity;
	uint32_t Size;
};

typedef struct _player_t
{
	std::uint64_t EntityPtr;
	std::uint64_t TableEntry;
	int NetworkID;
} player_t;

typedef struct _item_t
{
	std::uint64_t ItemPtr;
	std::uint64_t ItemTable;
} item_t;

extern _globals globals;
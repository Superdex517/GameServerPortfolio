#pragma once

struct SListEntry
{
	SListEntry* next;
};



struct SListHeader
{
	SListEntry* next = nullptr;
};

void InitHead(SListHeader* header);
void PushEntrySList(SListHeader* header, SListEntry* entry);
SListEntry* PopEntrySList(SListHeader* header);

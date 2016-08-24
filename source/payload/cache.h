#pragma once

#include "types.h"




void flushEntireDCache(void); //actually: "clean and flush"
void flushDCacheRange(void *startAddress, u32 size);
void flushEntireICache(void);
void flushICacheRange(void *startAddress, u32 size);
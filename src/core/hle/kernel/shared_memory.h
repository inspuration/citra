// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.  

#pragma once

#include "common/common_types.h"

#include "core/hle/kernel/kernel.h"

namespace Kernel {

/**
* Creates a shared memory object
* @param handle Reference to handle for the newly created mutex
* @param 
*/
Handle CreateSharedMemory(u32 size);

u32 GetSharedMemorySize(Handle handle);

void SetSharedMemoryPointer(Handle handle, u8* ptr);

template <typename T>
inline void ReadSharedMemory(Handle handle, T &var, const u32 addr);

template <typename T>
inline void WriteSharedMemory(Handle handle, const T data, const u32 addr);

} // namespace

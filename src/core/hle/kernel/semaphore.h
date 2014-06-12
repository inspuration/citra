// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.  

#pragma once

#include "common/common_types.h"

#include "core/hle/kernel/kernel.h"

namespace Kernel {

/**
* Releases a semaphore
* @param unknown
* @param handle Handle to mutex to release
* @param unknown
*/
Result ReleaseSemaphore(s32 * count, Handle handle, s32 release_count);

/**
* Creates a semaphore
* @param handle Reference to handle for the newly created semaphore
* @param initial_count Specifies if the semaphore is initialized with a count
* @param max_count Specifies the max count of the semaphore
* @param name Optional name of semaphore
* @return Handle to new Semaphore object
*/
Handle CreateSemaphore(s32 initial_count, s32 max_count, const std::string& name = "Unknown");

} // namespace

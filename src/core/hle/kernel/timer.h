// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.  

#pragma once

#include "common/common_types.h"

#include "core/hle/kernel/kernel.h"
#include "core/hle/svc.h"

namespace Kernel {

/**
* Sets a Timer
* @param handle Reference to handle for the timer
* @param intitial initial value of timer
* @param interval the period of the timer
* @return Result of operation, 0 on success, otherwise error code
*/
Result SetTimer(Handle handle, s64 initial, s64 interval);


/**
* Creates a Timer
* @param reset_type ResetType describing how to create timer
* @param name Optional name of timer
* @return Handle to newly created Timer object
*/
Handle CreateTimer(const ResetType reset_type, const std::string& name);
} // namespace

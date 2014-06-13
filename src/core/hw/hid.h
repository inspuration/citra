// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"
#include "core/mem_map.h"


namespace HID {
struct Registers {
    u32 buttons;
    //u32 pad1; etc...
};

extern Registers g_regs;

enum {
    OFFSET_BUTTONS = 0x1c,
};

const int g_num_pad_items = 12; 

enum PAD {
    PAD_A = (1 << 0),
    PAD_B = (1 << 1),
    PAD_SELECT = (1 << 2),
    PAD_START = (1 << 3),
    PAD_RIGHT = (1 << 4),
    PAD_LEFT = (1 << 5),
    PAD_UP = (1 << 6),
    PAD_DOWN = (1 << 7),
    PAD_R = (1 << 8),
    PAD_L = (1 << 9),
    PAD_X = (1 << 10),
    PAD_Y = (1 << 11),
};

const char * const PAD_NAMES[] = {
    "PAD_A",
    "PAD_B",
    "PAD_SELECT",
    "PAD_START",
    "PAD_RIGHT",
    "PAD_LEFT",
    "PAD_UP",
    "PAD_DOWN",
    "PAD_R",
    "PAD_L",
    "PAD_X",
    "PAD_Y"
};

void SetButtonReg(u32 button_data);

/// Update hardware
void Update();

/// Initialize hardware
void Init();

/// Shutdown hardware
void Shutdown();
}


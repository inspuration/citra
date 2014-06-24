// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/emu_window.h"

class EmuWindow_GLFW : public EmuWindow {
public:
    EmuWindow_GLFW();
    ~EmuWindow_GLFW();

    /// Swap buffers to display the next frame
    void SwapBuffers();

	/// Polls window events
	void PollEvents();

    /// Makes the graphics context current for the caller thread
    void MakeCurrent();
    
    /// Releases (dunno if this is the "right" word) the GLFW context from the caller thread
    void DoneCurrent();

    //used to set the key mappings to their default values
    void SetKeyDefaults();

	GLFWwindow* m_render_window;    ///< Internal GLFW render window

    typedef std::map<int, HID::PAD> GLFWKeyMapping;

    GLFWKeyMapping m_key_mapping;

    u32 m_button_reg;


private:

};

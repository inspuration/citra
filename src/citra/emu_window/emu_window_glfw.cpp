// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#include "common/common.h"

#include "video_core/video_core.h"
#include "core/hw/hid.h"

#include <map>

#include "citra/citra.h"
#include "citra/emu_window/emu_window_glfw.h"

typedef std::map<int, HID::PAD> GLFWKeyMapping;

GLFWKeyMapping g_key_mapping;

u32 g_button_reg;

static void OnKeyEvent(GLFWwindow* win, int key, int scancode, int action, int mods ) {
    try {
        HID::PAD button = g_key_mapping.at(key);
        if (action == GLFW_RELEASE) {
            g_button_reg &= 0xffffffff ^ button;
        }
        else if (action == GLFW_PRESS){
            g_button_reg |= button;
        }
        HID::SetButtonReg(g_button_reg);
    }
    catch (std::out_of_range& e){

    }
}

static void OnWindowSizeEvent(GLFWwindow* win, int width, int height) {
    EmuWindow_GLFW* emu_window = (EmuWindow_GLFW*)glfwGetWindowUserPointer(win);
    emu_window->SetClientAreaWidth(width);
    emu_window->SetClientAreaHeight(height);
}

void SetKeyDefaults() {
    g_key_mapping['Y'] = HID::PAD::PAD_A;
    g_key_mapping['H'] = HID::PAD::PAD_B;
    g_key_mapping['Z'] = HID::PAD::PAD_START;
    g_key_mapping['X'] = HID::PAD::PAD_SELECT;

    g_key_mapping['W'] = HID::PAD::PAD_UP;
    g_key_mapping['A'] = HID::PAD::PAD_LEFT;
    g_key_mapping['S'] = HID::PAD::PAD_DOWN;
    g_key_mapping['D'] = HID::PAD::PAD_RIGHT;

    g_key_mapping['6'] = HID::PAD::PAD_R;
    g_key_mapping['7'] = HID::PAD::PAD_L;
    g_key_mapping['U'] = HID::PAD::PAD_X;
    g_key_mapping['J'] = HID::PAD::PAD_Y;
}


/// EmuWindow_GLFW constructor
EmuWindow_GLFW::EmuWindow_GLFW() {
    // Initialize the window
    if(glfwInit() != GL_TRUE) {
        printf("Failed to initialize GLFW! Exiting...");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	
#if EMU_PLATFORM == PLATFORM_MACOSX
    // GLFW on OSX requires these window hints to be set to create a 3.2+ GL context.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	
    m_render_window = glfwCreateWindow(VideoCore::kScreenTopWidth, 
        (VideoCore::kScreenTopHeight + VideoCore::kScreenBottomHeight), 
        m_window_title.c_str(), NULL, NULL);

    if (m_render_window == NULL) {
        printf("Failed to create GLFW window! Exiting...");
        exit(1);
    }
    
    // Setup callbacks
    glfwSetWindowUserPointer(m_render_window, this);
    glfwSetKeyCallback(m_render_window, (GLFWkeyfun)OnKeyEvent);
    //glfwSetWindowSizeCallback(m_render_window, OnWindowSizeEvent);

    SetKeyDefaults();

    DoneCurrent();
}

/// EmuWindow_GLFW destructor
EmuWindow_GLFW::~EmuWindow_GLFW() {
    glfwTerminate();
}

/// Swap buffers to display the next frame
void EmuWindow_GLFW::SwapBuffers() {
    glfwSwapBuffers(m_render_window);
}

/// Polls window events
void EmuWindow_GLFW::PollEvents() {
    glfwPollEvents();
}

/// Makes the GLFW OpenGL context current for the caller thread
void EmuWindow_GLFW::MakeCurrent() {
    glfwMakeContextCurrent(m_render_window);
}

/// Releases (dunno if this is the "right" word) the GLFW context from the caller thread
void EmuWindow_GLFW::DoneCurrent() {
    glfwMakeContextCurrent(NULL);
}

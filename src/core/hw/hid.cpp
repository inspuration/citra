#include "hid.h"
#include "core/hle/service/hid.h"
#include "core/hle/kernel/shared_memory.h"


namespace HID {

void SetButtonReg(u32 buttonData) {
    Handle sharedMem = HID_User::GetMemIPCHandle();
    if (sharedMem != NULL)
        Kernel::WriteSharedMemory(sharedMem, buttonData, OFFSET_BUTTONS);
}

/// Update hardware
void Update() {
}

/// Initialize hardware
void Init() {
    NOTICE_LOG(HID, "initialized OK");
}

/// Shutdown hardware
void Shutdown() {
    NOTICE_LOG(HID, "shutdown OK");
}

}
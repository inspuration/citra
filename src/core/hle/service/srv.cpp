// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#include "core/hle/hle.h"
#include "core/hle/service/srv.h"
#include "core/hle/service/service.h"
#include "core/hle/kernel/mutex.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace SRV

namespace SRV {

Handle g_mutex = 0;

void Initialize(Service::Interface* self) {
    DEBUG_LOG(OSHLE, "called");
    if (!g_mutex) {
        g_mutex = Kernel::CreateMutex(true, "SRV:Lock");
    }
}

void GetProcSemaphore(Service::Interface* self) {
    DEBUG_LOG(OSHLE, "called");
    // Get process semaphore?
    u32* cmd_buff = Service::GetCommandBuffer();
    cmd_buff[1] = 0;        // No error
    cmd_buff[3] = g_mutex;  // Return something... 0 == nullptr, raises an exception
}

void GetServiceHandle(Service::Interface* self) {
    Result res = 0;
    u32* cmd_buff = Service::GetCommandBuffer();

    std::string port_name = std::string((const char*)&cmd_buff[1], 0, Service::kMaxPortSize);
    Service::Interface* service = Service::g_manager->FetchFromPortName(port_name);

    if (nullptr != service) {
        cmd_buff[3] = service->GetHandle();
        DEBUG_LOG(OSHLE, "called port=%s, handle=0x%08X", port_name.c_str(), cmd_buff[3]);
    } else {
        ERROR_LOG(OSHLE, "(UNIMPLEMENTED) called port=%s", port_name.c_str());
        res = -1;
    }
    cmd_buff[1] = res;
}

const Interface::FunctionInfo FunctionTable[] = {
    {0x00010002, Initialize,        "Initialize"},
    {0x00020000, GetProcSemaphore,  "GetProcSemaphore"},
    {0x00030100, nullptr,           "RegisterService"},
    {0x000400C0, nullptr,           "UnregisterService"},
    {0x00050100, GetServiceHandle,  "GetServiceHandle"},
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface class

Interface::Interface() {
    Register(FunctionTable, ARRAY_SIZE(FunctionTable));
}

Interface::~Interface() {
}

} // namespace

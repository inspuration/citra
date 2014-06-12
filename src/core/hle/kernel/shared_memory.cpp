// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.  

#include <map>
#include <vector>

#include "common/common.h"

#include "core/hle/kernel/kernel.h"
#include "core/hle/kernel/thread.h"

namespace Kernel {

class SharedMemory : public Object {
public:
    const char* GetTypeName() { return "SharedMemory"; }

    static Kernel::HandleType GetStaticHandleType() {  return Kernel::HandleType::SharedMemory; }
    Kernel::HandleType GetHandleType() const { return Kernel::HandleType::SharedMemory; }

    //TODO: implement
    /**
    * Wait for kernel object to synchronize
    * @param wait Boolean wait set if current thread should wait as a result of sync operation
    * @return Result of operation, 0 on success, otherwise error code
    */
    Result WaitSynchronization(bool* wait) {
        // TODO(bravia): ImplementMe
        return 0;
    }

    template <typename T>
    inline void Read(T &var, const u32 addr);

    template <typename T>
    inline void Write(T &var, const u32 addr);

    u32 size;
    u8* mem_ptr = NULL;
};

////////////////////////////////////////////////////////////////////////////////////////////////////



SharedMemory* CreateSharedMemory(Handle& handle, u32 size) {
    SharedMemory* mem = new SharedMemory;
    handle = Kernel::g_object_pool.Create(mem);
    mem->size = size;
    return mem;
}

Handle CreateSharedMemory(u32 size) {
    Handle handle;
    SharedMemory* mem = CreateSharedMemory(handle, size);
    return handle;
}

u32 GetSharedMemorySize(Handle handle) {
    SharedMemory* mem = Kernel::g_object_pool.GetFast<SharedMemory>(handle);
    _assert_msg_(KERNEL, (mem != nullptr), "called, but mem is nullptr!");
    return mem->size;
}

void SetSharedMemoryPointer(Handle handle, u8* ptr) {
    SharedMemory* mem = Kernel::g_object_pool.GetFast<SharedMemory>(handle);
    _assert_msg_(KERNEL, (mem != nullptr), "called, but mem is nullptr!");
    mem->mem_ptr = ptr;
}

template <typename T>
inline void ReadSharedMemory(Handle handle, T &var, const u32 addr) {
    SharedMemory* mem = Kernel::g_object_pool.GetFast<SharedMemory>(handle);
    _assert_msg_(KERNEL, (mem != nullptr), "called, but mem is nullptr!");
    if (mem->mem_ptr!=NULL)
        var = *((const T*)&mem->mem_ptr[addr & (mem->size - 1)]);
}

template <typename T>
inline void WriteSharedMemory(Handle handle, const T data, const u32 addr) {
    SharedMemory* mem = Kernel::g_object_pool.GetFast<SharedMemory>(handle);
    _assert_msg_(KERNEL, (mem != nullptr), "called, but mem is nullptr!");
    if (mem->mem_ptr != NULL)
        *(T*)&mem->mem_ptr[addr & (mem->size - 1)] = data;
}

template void WriteSharedMemory<u64>(Handle handle, const u64 data, const u32 addr);
template void WriteSharedMemory<u32>(Handle handle, const u32 data, const u32 addr);
template void WriteSharedMemory<u16>(Handle handle, const u16 data, const u32 addr);
template void WriteSharedMemory<u8>(Handle handle, const u8 data, const u32 addr);

template void ReadSharedMemory<u64>(Handle handle, u64 &var, const u32 addr);
template void ReadSharedMemory<u32>(Handle handle, u32 &var, const u32 addr);
template void ReadSharedMemory<u16>(Handle handle, u16 &var, const u32 addr);
template void ReadSharedMemory<u8>(Handle handle, u8 &var, const u32 addr);

} // namespace

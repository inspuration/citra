// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.  

#include <map>
#include <vector>

#include "common/common.h"

#include "core/hle/kernel/kernel.h"
#include "core/hle/kernel/mutex.h"
#include "core/hle/kernel/thread.h"

namespace Kernel {

class Semaphore : public Object {
public:
    const char* GetTypeName() const { return "Semaphore"; }
    const char* GetName() const { return name.c_str(); }

    static Kernel::HandleType GetStaticHandleType() { return Kernel::HandleType::Semaphore; }
    Kernel::HandleType GetHandleType() const { return Kernel::HandleType::Semaphore; }

    s32 initial_count;                          ///< Initial count state when semaphore was created
    s32 count;                                  ///< Current count state
    s32 max_count;                              ///< Max count state
    Handle lock_thread;                         ///< Handle to thread that currently has semaphore
    std::string name;

    /**
     * Synchronize kernel object 
     * @param wait Boolean wait set if current thread should wait as a result of sync operation
     * @return Result of operation, 0 on success, otherwise error code
     */
    Result SyncRequest(bool* wait) {
        // TODO(bravia): ImplementMe
        if (count > 0) {
            count--;
            *wait = false;
        }
        else{
            *wait = true;
        }
        return 0;
    }

    /**
     * Wait for kernel object to synchronize
     * @param wait Boolean wait set if current thread should wait as a result of sync operation
     * @return Result of operation, 0 on success, otherwise error code
     */
    Result WaitSynchronization(bool* wait) {
        *wait = (count == 0);
        if (count == 0) {
            Kernel::WaitCurrentThread(WAITTYPE_SEMA);
        }
        return 0;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Releases a semaphore
 * @param the previous count
 * @param handle Handle to mutex to release
 * @param the number of increments to be made
 */
Result ReleaseSemaphore(s32 * count, Handle handle, s32 release_count) {
    Semaphore* sem = Kernel::g_object_pool.GetFast<Semaphore>(handle);
    _assert_msg_(KERNEL, (sem != nullptr), "ReleaseSemaphore tried to release a nullptr sem!");

    *count = sem->count;
    if (sem->count + release_count <= sem->max_count) {
        sem->count += release_count;
        return 0;
    }
    else {
        return -1;
    }
}

/**
 * Creates a semaphore
 * @param handle Reference to handle for the newly created semaphore
 * @param initial_count Specifies if the semaphore is initialized with a count
 * @param max_count Specifies the max count of the semaphore
 * @param name Optional name of semaphore
 * @return Pointer to new Semaphore object
 */
Semaphore* CreateSemaphore(Handle& handle, s32 initial_count, s32 max_count, const std::string& name) {
    Semaphore* sem = new Semaphore;
    handle = Kernel::g_object_pool.Create(sem);

    sem->initial_count = sem->count = initial_count;
    sem->name = name;

    return sem;
}

/**
* Creates a semaphore
* @param handle Reference to handle for the newly created semaphore
* @param initial_count Specifies if the semaphore is initialized with a count
* @param max_count Specifies the max count of the semaphore
* @param name Optional name of semaphore
* @return Handle to new Semaphore object
*/
Handle CreateSemaphore(s32 initial_count, s32 max_count, const std::string& name) {
    Handle handle;
    Semaphore* sem = CreateSemaphore(handle, initial_count, max_count, name);
    return handle;
}

} // namespace

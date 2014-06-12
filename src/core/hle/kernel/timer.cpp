// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.  

#include <map>
#include <vector>
#include <algorithm>

#include "common/common.h"

#include "core/hle/kernel/kernel.h"
#include "core/hle/kernel/timer.h"
#include "core/hle/kernel/thread.h"

namespace Kernel {

class Timer : public Object {
public:
    const char* GetTypeName() const { return "Timer"; }
    const char* GetName() const { return name.c_str(); }

    static Kernel::HandleType GetStaticHandleType() { return Kernel::HandleType::Timer; }
    Kernel::HandleType GetHandleType() const { return Kernel::HandleType::Timer; }

    ResetType reset_type;                   ///<    ResetType

    s64 initial;
    s64 interval;

    bool set;                               ///<    has the timer been set

    std::string name;                       ///< Name of event (optional)


    /**
     * Wait for kernel object to synchronize
     * @param wait Boolean wait set if current thread should wait as a result of sync operation
     * @return Result of operation, 0 on success, otherwise error code
     */
    Result WaitSynchronization(bool* wait) {
        return 0;
    }
};


/**
* Cancels a Timer
* @param handle Reference to handle for the timer
* @return Result of operation, 0 on success, otherwise error code
*/
Result CancelTimer(Handle handle) {
    Timer* timer = g_object_pool.GetFast<Timer>(handle);
    _assert_msg_(KERNEL, (timer != nullptr), "called, but timer is nullptr!");
    timer->set = false;
    //TODO: unregister the callback created in settimer
}



/**
* Sets a Timer
* @param handle Reference to handle for the timer
* @param intitial initial value of timer
* @param interval the period of the timer
* @return Result of operation, 0 on success, otherwise error code
*/
Result SetTimer(Handle handle, s64 initial, s64 interval) {
    Timer* timer = g_object_pool.GetFast<Timer>(handle);
    _assert_msg_(KERNEL, (timer != nullptr), "called, but timer is nullptr!");
    if (interval < 0){
        return -1;
    }
    else if ((interval == 0) && (timer->reset_type == RESETTYPE_PULSE)) {
        return -1;
    }
    timer->initial = initial;
    timer->interval = interval;
    timer->set = true;
    //TODO: add some sort of callback for when the timer fires
    return 0;
}


/**
* Creates a Timer
* @param handle Reference to handle for the newly created timer
* @param reset_type ResetType describing how to create timer
* @param name Optional name of timer
* @return Newly created timer object
*/
Timer* CreateTimer(Handle& handle, const ResetType reset_type, const std::string& name) {
    Timer* timer = new Timer;

    handle = Kernel::g_object_pool.Create(timer);

    timer->set = false;
    timer->reset_type = reset_type;
    timer->name = name;

    return timer;
}

/**
* Creates a Timer
* @param reset_type ResetType describing how to create timer
* @param name Optional name of timer
* @return Handle to newly created Timer object
*/
Handle CreateTimer(const ResetType reset_type, const std::string& name) {
    Handle handle;
    Timer* timer = CreateTimer(handle, reset_type, name);
    return handle;
}

} // namespace

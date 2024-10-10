#include "custom_policy.hpp"

namespace iris::rt {

    CustomPolicy::CustomPolicy() = default;

    CustomPolicy::CustomPolicy(Scheduler* scheduler) {
        SetScheduler(scheduler);
    }

    CustomPolicy::~CustomPolicy() = default;

    void CustomPolicy::GetDevices(Task* task, Device** devices, int* n_devices) {
        if (*n_devices > 4) {
            Device* temp = devices[3];
            devices[0] = devices[3];
            devices[3] = temp;
        }
    }

}

REGISTER_CUSTOM_POLICY(CustomPolicy, custom_policy)
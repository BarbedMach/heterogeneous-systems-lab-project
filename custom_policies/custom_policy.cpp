#include "custom_policy.hpp"

namespace iris::rt {

    CustomPolicy::CustomPolicy() = default;

    CustomPolicy::~CustomPolicy() = default;

    void CustomPolicy::GetDevices(Task* task, Device** devices, int* n_devices) {
        if (*n_devices > 1) {
            auto* temp_dev = devices[1];
            devices[1] = devices[0];
            devices[0] = temp_dev;
        }
    }

}

REGISTER_CUSTOM_POLICY(CustomPolicy, custom_policy)
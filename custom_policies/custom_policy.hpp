#pragma once

#include <iris/rt/Policy.h>

namespace iris::rt {

    class CustomPolicy : public Policy {
        public:
            CustomPolicy();
            ~CustomPolicy() final;

            void GetDevices(Task* task, Device** devices, int* n_devices) final;
        private:
    };

}
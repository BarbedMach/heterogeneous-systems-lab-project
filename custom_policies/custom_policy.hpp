#pragma once

#include <iris/rt/Policy.h>

namespace iris::rt {

    class CustomPolicy : public Policy {
        public:
            CustomPolicy();
            CustomPolicy(Scheduler* scheduler);
            ~CustomPolicy() override;

            void GetDevices(Task* task, Device** devices, int* n_devices) override;
        private:
    };

}
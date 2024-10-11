#include <iris/iris.h>
#include <iris/rt/Policy.h>
#include <iris/rt/Debug.h>
#include <iris/rt/Device.h>
#include <iris/rt/Command.h>
#include <iris/rt/Device.h>
#include <iris/rt/Task.h>

namespace iris {
namespace rt {

int task_hook_pre(void* task) {
  Task* t = (Task*) task;
  printf("[%s:%d] enter task[%lu]\n", __FILE__, __LINE__, t->uid());
  return 0;
}

int task_hook_post(void* task) {
  Task* t = (Task*) task;
  printf("[%s:%d] exit task[%lu] time[%lf]\n", __FILE__, __LINE__, t->uid(), t->time());
  return 0;
}

int cmd_hook_pre(void* cmd) {
  Command* c = (Command*) cmd;
  printf("[%s:%d] enter cmd[%x]\n", __FILE__, __LINE__, c->type());
  return 0;
}

int cmd_hook_post(void* cmd) {
  Command* c = (Command*) cmd;
  if (c->type() == IRIS_CMD_KERNEL)
    printf("[%s:%d] exit cmd[%x] policy[%s] kernel[%s] gws[%lu][%lu][%lu] dev[%d][%s] time[%lf]\n", __FILE__, __LINE__, c->type(), c->task()->opt(), c->kernel()->name(), c->gws(0), c->gws(1), c->gws(2), c->task()->dev()->devno(), c->task()->dev()->name(), c->time());
  else printf("[%s:%d] exit cmd[%x] time[%lf]\n", __FILE__, __LINE__, c->type(), c->time());
  return 0;
}

class PolicyGWSHook: public Policy {
public:
  PolicyGWSHook() {
    iris_register_hooks_task(task_hook_pre, task_hook_post);
    iris_register_hooks_command(cmd_hook_pre, cmd_hook_post);
  }
  virtual ~PolicyGWSHook() {}
  virtual void Init(void* params) {
    threshold_ = (size_t) params;
  }
  virtual void GetDevices(Task* task, Device** devs, int* ndevs) {
    int chosenDeviceIndex = *getenv("IRIS_ENH_DEVICE_OPENCL_2") - '0';
    _info("Chosen dev index: %d", chosenDeviceIndex);
    _info("Number of devices: %d", *ndevs);
    devs[0] = device(chosenDeviceIndex);
    *ndevs = 1;
  }

  size_t threshold_;
};

} /* namespace rt */
} /* namespace iris */

REGISTER_CUSTOM_POLICY(PolicyGWSHook, policy_gws_hook)
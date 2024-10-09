#include <iris/iris.h>
#include <iostream>
#include <stdlib.h>


int main(int argc, char** argv) {
  iris_init(&argc, &argv, true);

  char vendor[64];
  char name[64];
  int type;
  int nplatforms = 0;
  int ndevs = 0;
  iris_platform_count(&nplatforms);
  for (int i = 0; i < nplatforms; i++) {
    size_t size;
    iris_platform_info(i, iris_name, name, &size);
    printf("platform[%d] name[%s]\n", i, name);
  }

  iris_device_count(&ndevs);
  for (int i = 0; i < ndevs; i++) {
    size_t size;
    iris_device_info(i, iris_vendor, vendor, &size);
    iris_device_info(i, iris_name, name, &size);
    iris_device_info(i, iris_type, &type, &size);
    printf("dev[%d] vendor[%s] name[%s] type[0x%x]\n", i, vendor, name, type);
  }

  size_t SIZE = argc > 1 ? atol(argv[1]) : 4;

  auto* A = static_cast<int*>(new int[SIZE]);

  //iris_register_policy("libCustomPolicy.so", "custom_policy", NULL); // nullptr/NULL can be replaced by policy init arguments if the policy depends on external arguments.

  iris_mem mem_A;
  iris_mem_create(SIZE * sizeof(int), &mem_A);

  void* params[] = { &mem_A };
  int params_info[] = { iris_w };

  iris_task task;
  iris_task_create(&task);

  iris_task_kernel(task, "process", 1, NULL, &SIZE, NULL, 1, params, params_info);

  iris_task_d2h_full(task, mem_A, A);

  iris_task_submit(task, iris_custom, "custom_policy", 1);

  for (auto i = 0; i < SIZE; ++i) {
    std::cout << "[" << i << "]  " << A[i] << std::endl;
  }

  iris_finalize();

  return iris_error_count();
}
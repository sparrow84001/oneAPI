//==============================================================
// Copyright © 2020 Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================
#include <CL/sycl.hpp>
using namespace sycl;

static const int N = 1024;

int main() {
  queue q;
  std::cout << "Device : " << q.get_device().get_info<info::device::name>()
            << "\n";

  //# Two USM allocation and initialization
  int *data1 = malloc_shared<int>(N, q);
  int *data2 = malloc_shared<int>(N, q);
  for (int i = 0; i < N; i++) { 
    data1[i] = 10; 
    data2[i] = 10; 
  }

  //# There are 3 kernel tasks submitted without data dependency, analyze the code and fix data dependency

  q.parallel_for(range<1>(N), [=](id<1> i) { data1[i] += 2; });

  q.parallel_for(range<1>(N), [=](id<1> i) { data2[i] += 3; });

  q.parallel_for(range<1>(N), [=](id<1> i) { data1[i] += data2[i]; }).wait();

  for (int i = 0; i < N; i++) std::cout << data1[i] << " ";
  std::cout << "\n";
  free(data1, q);
  free(data2, q);
  return 0;
}

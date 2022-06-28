//==============================================================
// Copyright © 2020 Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================
#include <CL/sycl.hpp>
using namespace sycl;

static const int N = 256;

int main() {
  queue q;
  std::cout << "Device : " << q.get_device().get_info<info::device::name>()
            << "\n";

  //# USM allocation and initialization
  int *data = malloc_shared<int>(N, q);
  for (int i = 0; i < N; i++) data[i] = 10;

  //# There are three kernel tasks submitted without data dependency, analyze the code and fix data dependency

  q.parallel_for(range<1>(N), [=](id<1> i) { data[i] += 2; });

  q.parallel_for(range<1>(N), [=](id<1> i) { data[i] += 3; });

  q.parallel_for(range<1>(N), [=](id<1> i) { data[i] += 5; }).wait();

  for (int i = 0; i < N; i++) std::cout << data[i] << " ";
  std::cout << "\n";
  free(data, q);
  return 0;
}

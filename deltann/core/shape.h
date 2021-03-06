/* Copyright (C) 2017 Beijing Didi Infinity Technology and Development Co.,Ltd.
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef DELTANN_CORE_SHAPE_H_
#define DELTANN_CORE_SHAPE_H_

#include <initializer_list>
#include <iostream>
#include <vector>

#ifdef USE_TF
#include "tensorflow/core/framework/tensor_shape.h"
#endif

namespace delta {

namespace core {

class Shape {
 public:
  Shape();

  explicit Shape(const std::vector<int>& v);

  Shape(const std::initializer_list<int>& s);

  Shape(const Shape& s);

  Shape& operator=(const Shape& s);

  void set_dim(int idx, int size);

  ~Shape();

  int ndim() const;

  const int operator[](int i) const;

  size_t size(void) const;

#ifdef USE_TF
  void set_shape(const tensorflow::TensorShape& shape);
#endif

  void set_shape(const Shape& shape);

  friend std::ostream& operator<<(std::ostream& os, const Shape& shape);

 private:
  static constexpr int _MaxDim = 7;
  int _ndim;
  int _data[_MaxDim];
};

}  // namespace core

}  // namespace delta

#endif  // DELTANN_CORE_SHAPE_H_

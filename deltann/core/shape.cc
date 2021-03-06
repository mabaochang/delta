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

#include <assert.h>

#include "core/shape.h"
#include "core/utils/logging.h"

namespace delta {

namespace core {

Shape::Shape() : _ndim(0) {}

Shape::Shape(const std::vector<int>& v) {
  _ndim = v.size();
  for (size_t i = 0; i < v.size(); i++) {
    _data[i] = v[i];
  }
}

Shape::Shape(const std::initializer_list<int>& s) {
  _ndim = 0;
  for (auto item : s) {
    _data[_ndim++] = item;
  }
}

Shape::Shape(const Shape& s) {
  _ndim = s.ndim();
  for (int i = 0; i < _ndim; ++i) {
    _data[i] = s[i];
  }
}

Shape& Shape::operator=(const Shape& s) {
  _ndim = s.ndim();
  for (int i = 0; i < _ndim; ++i) {
    _data[i] = s[i];
  }
}

void Shape::set_dim(int idx, int size) {
  assert(idx < (_ndim - 1));
  _data[idx] = size;
}

Shape::~Shape() {}

int Shape::ndim() const { return _ndim; }

const int Shape::operator[](int i) const {
  assert(i < _ndim);
  assert(i >= 0);
  return _data[i];
}

size_t Shape::size(void) const {
  if (_ndim < 1) {
    return 0;
  } else {
    assert(_ndim >= 1);
    size_t size = _data[0];
    for (int i = 1; i < _ndim; ++i) {
      assert(_data[i] >= 0);
      size *= _data[i];
    }
    return size;
  }
}

#ifdef USE_TF
void Shape::set_shape(const tensorflow::TensorShape& shape) {
  _ndim = shape.dims();
  for (int i = 0; i < _ndim; ++i) {
    set_dim(i, shape.dim_size(i));
  }
}
#endif

void Shape::set_shape(const Shape& shape) {
  _ndim = shape.ndim();
  for (int i = 0; i < _ndim; ++i) {
    set_dim(i, shape[i]);
  }
}

std::ostream& operator<<(std::ostream& os, const Shape& shape) {
  os << '[';
  for (int i = 0; i < shape.ndim(); ++i) {
    if (i != 0) os << ',';
    os << shape[i];
  }
  if (shape.ndim() == 1) {
    os << ',';
  }
  os << ']';
  return os;
}

}  // namespace core

}  // namespace delta

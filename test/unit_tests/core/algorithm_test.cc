//===------------------------------------------------------------*- C++ -*-===//
//
//                                     SHAD
//
//      The Scalable High-performance Algorithms and Data Structure Library
//
//===----------------------------------------------------------------------===//
//
// Copyright 2018 Battelle Memorial Institute
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy
// of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations
// under the License.
//
//===----------------------------------------------------------------------===//

#include "gtest/gtest.h"

#include "shad/core/algorithm.h"
#include "shad/data_structures/array.h"

class AlgorithmsTest : public ::testing::Test {
 public:
  AlgorithmsTest() { array_ = shad::array<size_t, 10001>::Create(); }

  void SetUp() { array_->fill(size_t(1)); }
  void TearDown() {}

 protected:
  std::shared_ptr<shad::array<size_t, 10001>> array_;
};

TEST_F(AlgorithmsTest, find) {
  auto res = shad::find(shad::distributed_parallel_tag{}, array_->begin(),
                        array_->end(), 0);

  ASSERT_EQ(res, array_->end());

  res = shad::find(shad::distributed_sequential_tag{}, array_->begin(),
                   array_->end(), 0);
  ASSERT_EQ(res, array_->end());

  array_->at(array_->size() - 1) = 2;

  res = shad::find(shad::distributed_sequential_tag{}, array_->begin(),
                   array_->end(), 2);
  ASSERT_EQ(res, (array_->end() - 1));

  res = shad::find(shad::distributed_parallel_tag{}, array_->begin(),
                   array_->end(), 2);
  ASSERT_EQ(res, (array_->end() - 1));
}

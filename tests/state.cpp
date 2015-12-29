/******************************************************************************
 *
 * state.cpp
 *
 * @author Copyright (C) 2015 Kotone Itaya
 * @version 2.2.0
 * @created  2015/12/30 Kotone Itaya -- Created!
 * @@
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *****************************************************************************/

#include "gtest/gtest.h"
#include "spira/spira.hpp"

namespace spira {
  namespace test {
    TEST(state, simple) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      state<int> state0(stream0);
      stream<int> stream1 = state0.mirror();
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      state0.update();
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
    }

    TEST(state, multiple) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      state<int> state0(stream0);
      stream<int> stream1 = state0.mirror();
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 += value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      state0.update();
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 84);
    }

    TEST(state, latest) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      state<int> state0(stream0);
      stream<int> stream1 = state0.mirror();
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 += value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      source0.dump(84);
      ASSERT_EQ(out0, 84);
      ASSERT_EQ(out1, 0);
      state0.latest();
      ASSERT_EQ(out0, 84);
      ASSERT_EQ(out1, 84);
    }
  }
}

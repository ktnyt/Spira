/******************************************************************************
 *
 * stream.cpp
 *
 * @author Copyright (C) 2015 Kotone Itaya
 * @version 2.0.0
 * @created  2015/10/15 Kotone Itaya -- Created!
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
#include "spira.hpp"

namespace spira {
  namespace test {
    TEST(stream, simple) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      int out0(0);

      stream0.bind([&out0](int value){out0 = value;});

      ASSERT_EQ(out0, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
    }

    TEST(stream, chain) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0.mirror().mirror();
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream0.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
    }

    TEST(stream, unique) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0.unique();
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 += value;});
      stream1.bind([&out1](int value){out1 += value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      source0.dump(42);
      ASSERT_EQ(out0, 84);
      ASSERT_EQ(out1, 42);
    }

    TEST(stream, mirror) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0.unique();
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
    }

    TEST(stream, merge) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0.merge(stream1);
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 42);
      source1.dump(21);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 21);
      ASSERT_EQ(out2, 21);
    }

    TEST(stream, filter) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0.filter([](int value){
          return value % 2 == 0;
        });
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      source0.dump(21);
      ASSERT_EQ(out0, 21);
      ASSERT_EQ(out1, 42);
    }

    TEST(stream, whilst) {
      source<int> source0;
      source<bool> source1;
      stream<int> stream0 = source0.draw();
      stream<bool> stream1 = source1.draw();
      stream<int> stream2 = stream0.whilst(stream1);
      int out0(0);
      bool out1(false);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](bool value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      source1.dump(false);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, false);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, false);
      ASSERT_EQ(out2, 0);
      source1.dump(true);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, true);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, true);
      ASSERT_EQ(out2, 42);
    }

    TEST(stream, scan) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0.scan(0, [](int a, int b){
          return a + b;
        });
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 84);
    }

    TEST(stream, map) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<bool> stream1 = stream0.map(std::function<bool(int)>([](int value){
            return value % 2 == 0;
          }));

      int out0(0);
      bool out1(false);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](bool value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, false);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, true);
      source0.dump(21);
      ASSERT_EQ(out0, 21);
      ASSERT_EQ(out1, false);
    }

    TEST(stream, combine) {
      source<int> source0;
      source<bool> source1;
      stream<int> stream0 = source0.draw();
      stream<bool> stream1 = source1.draw();
      stream<std::pair<int, bool> > stream2 = stream0.combine(stream1, SAMPLED_BY::BOTH);
      int out0(0);
      bool out1(false);
      std::pair<int, bool> out2(std::pair<int, bool>(0, false));

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](bool value){out1 = value;});
      stream2.bind([&out2](std::pair<int, bool> value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, false);
      ASSERT_EQ(out2.first, 0);
      ASSERT_EQ(out2.second, false);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, false);
      ASSERT_EQ(out2.first, 42);
      ASSERT_EQ(out2.second, false);
      source1.dump(true);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, true);
      ASSERT_EQ(out2.first, 42);
      ASSERT_EQ(out2.second, true);
    }

    TEST(stream, operator_eq) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 == stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      source1.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 1);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 0);
    }

    TEST(stream, operator_neq) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 != stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      source1.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 1);
    }

    TEST(stream, operator_lt) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 < stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      source1.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 1);
    }

    TEST(stream, operator_gt) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 > stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      source1.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 0);
    }

    TEST(stream, operator_lteq) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 <= stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      source1.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 1);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 1);
    }

    TEST(stream, operator_gteq) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 >= stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      source1.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 1);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 0);
    }

    TEST(stream, operator_eq_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 == 42;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_neq_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 != 42;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_lt_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 < 0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      source0.dump(-42);
      ASSERT_EQ(out0, -42);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_gt_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 > 0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1);
      source0.dump(-42);
      ASSERT_EQ(out0, -42);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_lteq_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 <= 0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      source0.dump(-42);
      ASSERT_EQ(out0, -42);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_gteq_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 >= 0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1);
      source0.dump(-42);
      ASSERT_EQ(out0, -42);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_eq_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 42 == stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_neq_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 42 != stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_lt_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 0 < stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1);
      source0.dump(-42);
      ASSERT_EQ(out0, -42);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_gt_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 0 > stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      source0.dump(-42);
      ASSERT_EQ(out0, -42);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_lteq_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 0 <= stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1);
      source0.dump(-42);
      ASSERT_EQ(out0, -42);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_gteq_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 0 >= stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      source0.dump(-42);
      ASSERT_EQ(out0, -42);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_plus) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 + stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 42);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 84);
    }

    TEST(stream, operator_minus) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 - stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 42);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 0);
    }

    TEST(stream, operator_star) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 * stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 1764);
    }

    TEST(stream, operator_slash) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 / stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      source1.dump(1); // Exception workaround
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 42);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 1);
    }

    TEST(stream, operator_percent) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 % stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      source1.dump(5); // Exception workaround
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 5);
      ASSERT_EQ(out2, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 5);
      ASSERT_EQ(out2, 2);
      source1.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 0);
    }

    TEST(stream, operator_plus_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 + 42;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 84);
    }

    TEST(stream, operator_minus_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 - 42;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_star_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 * 42;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1764);
    }

    TEST(stream, operator_slash_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 / 42;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_percent_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 % 42;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      source0.dump(50);
      ASSERT_EQ(out0, 50);
      ASSERT_EQ(out1, 8);
    }

    TEST(stream, operator_plus_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 42 + stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 84);
    }

    TEST(stream, operator_minus_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 42 - stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_star_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 42 * stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1764);
    }

    TEST(stream, operator_slash_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 42 / stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_percent_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 42 % stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      source0.dump(10);
      ASSERT_EQ(out0, 10);
      ASSERT_EQ(out1, 2);
    }

    TEST(stream, operator_bitnot) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = ~stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, ~0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, ~0 ^ 1);
    }

    TEST(stream, operator_bitand) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 & stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source1.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 1);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 0);
    }

    TEST(stream, operator_bitxor) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 ^ stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      source1.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 1);
    }

    TEST(stream, operator_bitor) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 | stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      source1.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 1);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 1);
    }

    TEST(stream, operator_bitshl) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 << stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      source1.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 2);
      source1.dump(2);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 2);
      ASSERT_EQ(out2, 4);
    }

    TEST(stream, operator_bitshr) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 >> stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(4);
      ASSERT_EQ(out0, 4);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 4);
      source1.dump(1);
      ASSERT_EQ(out0, 4);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 2);
      source1.dump(2);
      ASSERT_EQ(out0, 4);
      ASSERT_EQ(out1, 2);
      ASSERT_EQ(out2, 1);
    }

    TEST(stream, operator_bitand_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 & 1;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_bitxor_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 ^ 1;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_bitor_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 | 0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_bitshl_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 << 1;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 2);
    }

    TEST(stream, operator_bitshr_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 >> 1;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_bitand_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 1 & stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_bitxor_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 1 ^ stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_bitor_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 0 | stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_bitshl_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 1 << stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 2);
    }

    TEST(stream, operator_bitshr_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 1 >> stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_not) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = !stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
    }

    TEST(stream, operator_and) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 && stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source1.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 1);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 0);
    }

    TEST(stream, operator_or) {
      source<int> source0;
      source<int> source1;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = source1.draw();
      stream<int> stream2 = stream0 || stream1;
      int out0(0);
      int out1(0);
      int out2(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});
      stream2.bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      source1.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 1);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 1);
      ASSERT_EQ(out2, 1);
    }

    TEST(stream, operator_and_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 && 1;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_or_rhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = stream0 || 0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_and_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 1 && stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
    }

    TEST(stream, operator_or_lhs) {
      source<int> source0;
      stream<int> stream0 = source0.draw();
      stream<int> stream1 = 0 || stream0;
      int out0(0);
      int out1(0);

      stream0.bind([&out0](int value){out0 = value;});
      stream1.bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      source0.dump(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 1);
    }
  }
}

/******************************************************************************
 *
 * stream.cpp
 *
 * @author Copyright (C) 2015 Kotone Itaya
 * @version 1.0.0
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
#include "basin.hpp"
#include "stream.hpp"

namespace spira {
  namespace test {
    TEST(stream, simple) {
      basin<int> basin0;
      stream<int>* stream0 = basin0.draw();
      int out0(0);

      stream0->bind([&out0](int value){out0 = value;});

      ASSERT_EQ(out0, 0);
      basin0.dump(42);
      ASSERT_EQ(out0, 42);
    }

    TEST(stream, mirror) {
      basin<int> basin0;
      stream<int>* stream0 = basin0.draw();
      stream<int>* stream1 = stream0->mirror();
      int out0(0);
      int out1(0);

      stream0->bind([&out0](int value){out0 = value;});
      stream1->bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      basin0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
    }

    TEST(stream, merge) {
      basin<int> basin0;
      basin<int> basin1;
      stream<int>* stream0 = basin0.draw();
      stream<int>* stream1 = basin1.draw();
      stream<int>* stream2 = stream0->merge(stream1);
      int out0(0);
      int out1(0);
      int out2(0);

      stream0->bind([&out0](int value){out0 = value;});
      stream1->bind([&out1](int value){out1 = value;});
      stream2->bind([&out2](int value){out2 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      basin0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 42);
      basin0.dump(0);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      basin1.dump(42);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 42);
      ASSERT_EQ(out2, 42);
    }

    TEST(stream, filter) {
      basin<int> basin0;
      stream<int>* stream0 = basin0.draw();
      stream<int>* stream1 = stream0->filter([](int value){
          return value % 2 == 0;
        });
      int out0(0);
      int out1(0);

      stream0->bind([&out0](int value){out0 = value;});
      stream1->bind([&out1](int value){out1 = value;});

      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      basin0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, 42);
      basin0.dump(21);
      ASSERT_EQ(out0, 21);
      ASSERT_EQ(out1, 42);
    }

    TEST(stream, whilst) {
      basin<int>  basin0;
      basin<bool> basin1;
      stream<int>*  stream0 = basin0.draw();
      stream<bool>* stream1 = basin1.draw();
      stream<int>*  stream2 = stream0->whilst(stream1);
      int  out0(0);
      bool out1(false);
      int  out2(0);

      stream0->bind([&out0](int  value){out0 = value;});
      stream1->bind([&out1](bool value){out1 = value;});
      stream2->bind([&out2](int  value){out2 = value;});

      basin1.dump(false);
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, false);
      ASSERT_EQ(out2, 0);
      basin0.dump(42);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, false);
      ASSERT_EQ(out2, 0);
      basin1.dump(true);
      ASSERT_EQ(out0, 42);
      ASSERT_EQ(out1, true);
      ASSERT_EQ(out2, 0);
      basin0.dump(21);
      ASSERT_EQ(out0, 21);
      ASSERT_EQ(out1, true);
      ASSERT_EQ(out2, 21);
    }
  }
}

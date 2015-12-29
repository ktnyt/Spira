/******************************************************************************
 *
 * timer.cpp
 *
 * @author Copyright (C) 2015 Kotone Itaya
 * @version 2.1.0
 * @created  2015/11/02 Kotone Itaya -- Created!
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

#include <cstdint>
#include "gtest/gtest.h"
#include "spira/spira.hpp"

namespace spira {
  namespace test {
    TEST(timer, simple) {
      timer timer0(58);
      stream<int64_t> stream0 = timer0.draw();
      int64_t out0(0);

      stream0.bind([&out0](int64_t value){out0 = value;});

      std::chrono::steady_clock::time_point init = std::chrono::steady_clock::now();

      ASSERT_EQ(out0, 0);

      for(;;) {
        timer0.poll();
        std::chrono::steady_clock::time_point curr = std::chrono::steady_clock::now();
        std::chrono::nanoseconds duration = (curr - init);
        if(duration.count() >= 1000000000) break;
      }

      timer0.poll();

      ASSERT_EQ(out0, 58);
    }

    TEST(timer, reset) {
      timer timer0(58);
      stream<int64_t> stream0 = timer0.draw();
      int64_t out0(0);

      stream0.bind([&out0](int64_t value){out0 = value;});

      std::chrono::steady_clock::time_point init = std::chrono::steady_clock::now();

      ASSERT_EQ(out0, 0);

      for(;;) {
        timer0.poll();
        std::chrono::steady_clock::time_point curr = std::chrono::steady_clock::now();
        std::chrono::nanoseconds duration = (curr - init);
        if(duration.count() >= 1000000000) break;
      }

      timer0.poll();
      ASSERT_EQ(out0, 58);
      timer0.reset();

      init = std::chrono::steady_clock::now();

      ASSERT_EQ(out0, 0);

      for(;;) {
        timer0.poll();
        std::chrono::steady_clock::time_point curr = std::chrono::steady_clock::now();
        std::chrono::nanoseconds duration = (curr - init);
        if(duration.count() >= 1000000000) break;
      }

      timer0.poll();
      ASSERT_EQ(out0, 58);
    }
  }
}

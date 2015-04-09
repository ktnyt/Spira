/******************************************************************************
**  spira_unittest.cpp
**  SpiraFRP v1.0.0
**
**  Created by ktnyt on 2015/04/04
**  Copyright (c) 2015 Kotone Itaya. All rights reserved.
**
**  This file is part of SpiraFRP.
**
**  SpiraFRP is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  SpiraFRP is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with SpiraFRP.  If not, see <http://www.gnu.org/licenses/>.
**
******************************************************************************/

#include <string>

#include "gtest/gtest.h"
#include "spira.hpp"

namespace spira_test {
  TEST(stream_test, stream_simple_test) {
    spira::stream<int> stream0;
    int out0(0);

    stream0.bind([&](int value){out0 = value;});
    ASSERT_EQ(out0, 0);
    stream0.push(1);
    ASSERT_EQ(out0, 01);
  }

  TEST(stream_test, stream_seed_test) {
    spira::stream<int> stream0(0);
    int out0(0);

    stream0.bind([&](int value){out0 = value;});
    ASSERT_EQ(out0, 0);
    stream0.push(1);
    ASSERT_EQ(out0, 01);
  }

  TEST(stream_test, stream_skip_test) {
    spira::stream<int> stream0(spira::DUPLICATES::SKIP);
    int out0(0);

    stream0.bind([&](int value){out0++;});
    ASSERT_EQ(out0, 0);
    stream0.push(0);
    ASSERT_EQ(out0, 0);
    stream0.push(1);
    ASSERT_EQ(out0, 1);
    stream0.push(1);
    ASSERT_EQ(out0, 1);
    stream0.push(2);
    ASSERT_EQ(out0, 2);
    stream0.push(2);
    ASSERT_EQ(out0, 2);
  }

  TEST(stream_test, stream_mirror_test) {
    spira::stream<int> stream0;
    spira::stream<int> stream1(stream0);
    int out0(0);
    int out1(0);

    stream0.bind([&](int value){out0 = value;});
    stream1.bind([&](int value){out1 = value;});
    ASSERT_EQ(out0, 0);
    ASSERT_EQ(out1, 0);
    stream0.push(1);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 1);
    stream1.push(2);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 2);
  }

  TEST(stream_test, stream_mirror10_test) {
    spira::stream<int> stream0;
    spira::stream<int> stream1(stream0);
    spira::stream<int> stream2(stream1);
    spira::stream<int> stream3(stream2);
    spira::stream<int> stream4(stream3);
    spira::stream<int> stream5(stream4);
    spira::stream<int> stream6(stream5);
    spira::stream<int> stream7(stream6);
    spira::stream<int> stream8(stream7);
    spira::stream<int> stream9(stream8);
    int out0(0);
    int out1(0);
    int out2(0);
    int out3(0);
    int out4(0);
    int out5(0);
    int out6(0);
    int out7(0);
    int out8(0);
    int out9(0);

    stream0.bind([&](int value){out0 = value;});
    stream1.bind([&](int value){out1 = value;});
    stream2.bind([&](int value){out2 = value;});
    stream3.bind([&](int value){out3 = value;});
    stream4.bind([&](int value){out4 = value;});
    stream5.bind([&](int value){out5 = value;});
    stream6.bind([&](int value){out6 = value;});
    stream7.bind([&](int value){out7 = value;});
    stream8.bind([&](int value){out8 = value;});
    stream9.bind([&](int value){out9 = value;});
    ASSERT_EQ(out0, 0);
    ASSERT_EQ(out1, 0);
    ASSERT_EQ(out2, 0);
    ASSERT_EQ(out3, 0);
    ASSERT_EQ(out4, 0);
    ASSERT_EQ(out5, 0);
    ASSERT_EQ(out6, 0);
    ASSERT_EQ(out7, 0);
    ASSERT_EQ(out8, 0);
    ASSERT_EQ(out9, 0);
    stream0.push(1);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 1);
    ASSERT_EQ(out2, 1);
    ASSERT_EQ(out3, 1);
    ASSERT_EQ(out4, 1);
    ASSERT_EQ(out5, 1);
    ASSERT_EQ(out6, 1);
    ASSERT_EQ(out7, 1);
    ASSERT_EQ(out8, 1);
    ASSERT_EQ(out9, 1);
    stream1.push(2);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 2);
    ASSERT_EQ(out2, 2);
    ASSERT_EQ(out3, 2);
    ASSERT_EQ(out4, 2);
    ASSERT_EQ(out5, 2);
    ASSERT_EQ(out6, 2);
    ASSERT_EQ(out7, 2);
    ASSERT_EQ(out8, 2);
    ASSERT_EQ(out9, 2);
    stream2.push(3);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 2);
    ASSERT_EQ(out2, 3);
    ASSERT_EQ(out3, 3);
    ASSERT_EQ(out4, 3);
    ASSERT_EQ(out5, 3);
    ASSERT_EQ(out6, 3);
    ASSERT_EQ(out7, 3);
    ASSERT_EQ(out8, 3);
    ASSERT_EQ(out9, 3);
    stream3.push(4);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 2);
    ASSERT_EQ(out2, 3);
    ASSERT_EQ(out3, 4);
    ASSERT_EQ(out4, 4);
    ASSERT_EQ(out5, 4);
    ASSERT_EQ(out6, 4);
    ASSERT_EQ(out7, 4);
    ASSERT_EQ(out8, 4);
    ASSERT_EQ(out9, 4);
    stream4.push(5);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 2);
    ASSERT_EQ(out2, 3);
    ASSERT_EQ(out3, 4);
    ASSERT_EQ(out4, 5);
    ASSERT_EQ(out5, 5);
    ASSERT_EQ(out6, 5);
    ASSERT_EQ(out7, 5);
    ASSERT_EQ(out8, 5);
    ASSERT_EQ(out9, 5);
    stream5.push(6);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 2);
    ASSERT_EQ(out2, 3);
    ASSERT_EQ(out3, 4);
    ASSERT_EQ(out4, 5);
    ASSERT_EQ(out5, 6);
    ASSERT_EQ(out6, 6);
    ASSERT_EQ(out7, 6);
    ASSERT_EQ(out8, 6);
    ASSERT_EQ(out9, 6);
    stream6.push(7);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 2);
    ASSERT_EQ(out2, 3);
    ASSERT_EQ(out3, 4);
    ASSERT_EQ(out4, 5);
    ASSERT_EQ(out5, 6);
    ASSERT_EQ(out6, 7);
    ASSERT_EQ(out7, 7);
    ASSERT_EQ(out8, 7);
    ASSERT_EQ(out9, 7);
    stream7.push(8);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 2);
    ASSERT_EQ(out2, 3);
    ASSERT_EQ(out3, 4);
    ASSERT_EQ(out4, 5);
    ASSERT_EQ(out5, 6);
    ASSERT_EQ(out6, 7);
    ASSERT_EQ(out7, 8);
    ASSERT_EQ(out8, 8);
    ASSERT_EQ(out9, 8);
    stream8.push(9);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 2);
    ASSERT_EQ(out2, 3);
    ASSERT_EQ(out3, 4);
    ASSERT_EQ(out4, 5);
    ASSERT_EQ(out5, 6);
    ASSERT_EQ(out6, 7);
    ASSERT_EQ(out7, 8);
    ASSERT_EQ(out8, 9);
    ASSERT_EQ(out9, 9);
    stream9.push(0);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 2);
    ASSERT_EQ(out2, 3);
    ASSERT_EQ(out3, 4);
    ASSERT_EQ(out4, 5);
    ASSERT_EQ(out5, 6);
    ASSERT_EQ(out6, 7);
    ASSERT_EQ(out7, 8);
    ASSERT_EQ(out8, 9);
    ASSERT_EQ(out9, 0);
  }

  TEST(stream_test, stream_merge_test) {
    for(int i = 0; i < 1000; ++i) {
      spira::stream<int> stream0;
      spira::stream<int> stream1;
      spira::stream<int> stream2(stream0, stream1);
      int out0(0);
      int out1(0);
      int out2(0);
    
      stream0.bind([&](int value){out0 = value;});
      stream1.bind([&](int value){out1 = value;});
      stream2.bind([&](int value){out2 = value;});
      ASSERT_EQ(out0, 0);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 0);
      stream0.push(1);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 0);
      ASSERT_EQ(out2, 1);
      stream1.push(2);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 2);
      ASSERT_EQ(out2, 2);
      stream2.push(3);
      ASSERT_EQ(out0, 1);
      ASSERT_EQ(out1, 2);
      ASSERT_EQ(out2, 3);
    }
  }

  TEST(stream_test, stream_filter_test) {
    spira::stream<int> stream0;
    spira::stream<int> stream1(stream0, std::function<bool(int)>([&](int value){return value != 0;}));
    int out0(0);
    int out1(0);

    stream0.bind([&](int value){out0 = value;});
    stream1.bind([&](int value){out1 = value;});
    ASSERT_EQ(out0, 0);
    ASSERT_EQ(out1, 0);
    stream0.push(1);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 1);
    stream0.push(0);
    ASSERT_EQ(out0, 0);
    ASSERT_EQ(out1, 1);
    stream0.push(2);
    ASSERT_EQ(out0, 2);
    ASSERT_EQ(out1, 2);
  }

  TEST(stream_test, stream_while_teset) {
    spira::stream<int> stream0;
    spira::stream<bool> stream1;
    spira::stream<int> stream2(stream0, stream1, spira::TAKE_WHILE::TRUE);
    int out0(0);
    bool out1(false);
    int out2(0);

    stream0.bind([&](int value){out0 = value;});
    stream1.bind([&](bool value){out1 = value;});
    stream2.bind([&](int value){out2 = value;});
    ASSERT_EQ(out0, 0);
    ASSERT_EQ(out1, false);
    ASSERT_EQ(out2, 0);
    stream0.push(1);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, false);
    ASSERT_EQ(out2, 0);
    stream1.push(true);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, true);
    ASSERT_EQ(out2, 0);
    stream0.push(2);
    ASSERT_EQ(out0, 2);
    ASSERT_EQ(out1, true);
    ASSERT_EQ(out2, 2);
    stream1.push(false);
    ASSERT_EQ(out0, 2);
    ASSERT_EQ(out1, false);
    ASSERT_EQ(out2, 2);
    stream0.push(3);
    ASSERT_EQ(out0, 3);
    ASSERT_EQ(out1, false);
    ASSERT_EQ(out2, 2);
  }

  TEST(stream_test, stream_map_test) {
    spira::stream<int> stream0;
    spira::stream<bool> stream1(stream0, std::function<bool(int)>([](int value){return value != 0;}));
    int out0(0);
    bool out1(false);

    stream0.bind([&](int value){out0 = value;});
    stream1.bind([&](bool value){out1 = value;});
    ASSERT_EQ(out0, 0);
    ASSERT_EQ(out1, false);
    stream0.push(1);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, true);
    stream0.push(0);
    ASSERT_EQ(out0, 0);
    ASSERT_EQ(out1, false);
    stream0.push(2);
    ASSERT_EQ(out0, 2);
    ASSERT_EQ(out1, true);
  }

  TEST(stream_test, stream_scan_test) {
    spira::stream<int> stream0;
    spira::stream<int> stream1(stream0, 0, std::function<int(int,int)>([](int v1, int v2){return v1 + v2;}));
    int out0(0);
    int out1(0);

    stream0.bind([&](int value){out0 = value;});
    stream1.bind([&](int value){out1 = value;});
    ASSERT_EQ(out0, 0);
    ASSERT_EQ(out1, 0);
    stream0.push(1);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, 1);
    stream0.push(2);
    ASSERT_EQ(out0, 2);
    ASSERT_EQ(out1, 3);
    stream0.push(3);
    ASSERT_EQ(out0, 3);
    ASSERT_EQ(out1, 6);
  }

  TEST(stream_test, stream_combine_test) {
    spira::stream<int> stream0;
    spira::stream<bool> stream1(stream0, std::function<bool(int)>([](int value){return ((value & 1) == 1);}));
    spira::stream<std::pair<int, bool> > stream2(stream0, stream1, spira::SAMPLED_BY::SECOND);
    int out0(0);
    bool out1(0);
    std::pair<int, bool> out2(std::pair<int, bool>(0, false));

    stream0.bind([&](int value){out0 = value;});
    stream1.bind([&](bool value){out1 = value;});
    stream2.bind([&](std::pair<int, bool> value){out2 = value;});
    ASSERT_EQ(out0, 0);
    ASSERT_EQ(out1, false);
    ASSERT_EQ(out2, (std::pair<int, bool>(out0, out1)));
    stream0.push(1);
    ASSERT_EQ(out0, 1);
    ASSERT_EQ(out1, true);
    ASSERT_EQ(out2, (std::pair<int, bool>(out0, out1)));
    stream0.push(2);
    ASSERT_EQ(out0, 2);
    ASSERT_EQ(out1, false);
    ASSERT_EQ(out2, (std::pair<int, bool>(out0, out1)));
  }
}

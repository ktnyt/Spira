/******************************************************************************
**  spira_benchmark.cpp
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

#include "benchmark/benchmark.h"
#include "spira.hpp"

static void stream_simple_benchmark(benchmark::State& state) {
  spira::stream<int> stream0;
  int out(0);
  int iter(0);

  stream0.bind([&](int value){out = value;});

  while(state.KeepRunning()) {
    stream0.push(iter);
    iter++;
  }
}

static void stream_mirror_benchmark(benchmark::State& state) {
  spira::stream<int> stream0;
  spira::stream<int> stream1(stream0);
  int out(0);
  int iter(0);

  stream1.bind([&](int value){out = value;});

  while(state.KeepRunning()) {
    stream0.push(iter);
    iter++;
  }
}

static void stream_mirror10_benchmark(benchmark::State& state) {
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
  int out(0);
  int iter(0);

  stream9.bind([&](int value){out = value;});

  while(state.KeepRunning()) {
    stream0.push(iter);
    iter++;
  }
}

static void stream_merge_benchmark(benchmark::State& state) {
  spira::stream<int> stream0;
  spira::stream<int> stream1;
  spira::stream<int> stream2(stream0, stream1);
  int out(0);
  int iter(0);

  stream2.bind([&](int value){out = value;});

  while(state.KeepRunning()) {
    stream0.push(iter);
    stream1.push(iter);
    iter++;
  }
}

static void stream_filter_benchmark(benchmark::State& state) {
  spira::stream<int> stream0;
  spira::stream<int> stream1(stream0, std::function<bool(int)>([](int value){return value != 0;}));
  int out(0);
  int iter(0);

  stream1.bind([&](int value){out = value;});

  while(state.KeepRunning()) {
    stream0.push((iter & 1));
    iter++;
  }
}

static void stream_while_benchmark(benchmark::State& state) {
  spira::stream<int> stream0;
  spira::stream<bool> stream1;
  spira::stream<int> stream2(stream0, stream1, spira::TAKE_WHILE::TRUE);
  int out(0);
  int iter(0);

  stream2.bind([&](int value){out = value;});

  while(state.KeepRunning()) {
    stream0.push((iter & 1));
    stream1.push((iter != 0));
    iter++;
  }
}

static void stream_map_benchmark(benchmark::State& state) {
  spira::stream<int> stream0;
  spira::stream<bool> stream1(stream0, std::function<bool(int)>([](int value){return value != 0;}));
  bool out(0);
  int iter(0);

  stream1.bind([&](bool value){out = value;});

  while(state.KeepRunning()) {
    stream0.push(iter);
    iter++;
  }
}

static void stream_scan_benchmark(benchmark::State& state) {
  spira::stream<int> stream0;
  spira::stream<int> stream1(stream0, 0, std::function<int(int,int)>([](int v1, int v2){return v1 + v2;}));
  int out(0);
  int iter(0);

  stream1.bind([&](bool value){out = value;});

  while(state.KeepRunning()) {
    stream0.push(iter % 10);
    iter++;
  }
}

static void stream_combine_benchmark(benchmark::State& state) {
  spira::stream<int> stream0;
  spira::stream<bool> stream1(stream0, std::function<bool(int)>([](int value){return ((value & 1) == 1);}));
  spira::stream<std::pair<int, bool> > stream2(stream0, stream1, spira::SAMPLED_BY::SECOND);
  std::pair<int, bool> out(std::pair<int, bool>(0, false));
  int iter(0);

  stream2.bind([&](std::pair<int, bool> value){out = value;});

  while(state.KeepRunning()) {
    stream0.push(iter);
    iter++;
  }
}

BENCHMARK(stream_simple_benchmark);
BENCHMARK(stream_mirror_benchmark);
BENCHMARK(stream_mirror10_benchmark);
BENCHMARK(stream_merge_benchmark);
BENCHMARK(stream_filter_benchmark);
BENCHMARK(stream_while_benchmark);
BENCHMARK(stream_map_benchmark);
BENCHMARK(stream_scan_benchmark);
BENCHMARK(stream_combine_benchmark);

BENCHMARK_MAIN();


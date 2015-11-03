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

#include "spira/timer.hpp"

namespace spira {
  struct timer::impl {
    std::chrono::steady_clock::time_point init;
    std::chrono::steady_clock::time_point curr;
    double fps;
    unsigned long long int frame;
    unsigned long long int time;
  };

  timer::timer(double fps) : pimpl(std::shared_ptr<impl>(new impl())) {
    this->reset();
  }

  timer::timer(const timer& other) {
    this->pimpl = other.pimpl;
  }

  timer& timer::operator =(timer& other) {
    swap(*this, other);
    return *this;
  }

  void swap(timer& a, timer& b) {
    std::swap(a.pimpl, b.pimpl);
  }

  void timer::poll() {
    this->pimpl->curr = std::chrono::steady_clock::now();
    std::chrono::nanoseconds duration = (this->pimpl->curr - this->pimpl->init);
    this->pimpl->time = duration.count();
    unsigned long long int now = ((this->pimpl->time * this->pimpl->fps) / 1000000000);
    if(now > this->pimpl->frame) {
      while(now > this->pimpl->frame) this->dump(++this->pimpl->frame);
    }
  }

  void timer::reset() {
    this->pimpl->init = std::chrono::steady_clock::now();
    this->pimpl->frame = 0;
    this->pimpl->time = 0;
    this->dump(0);
  }
}

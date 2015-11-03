/******************************************************************************
 *
 * timer.hpp
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

#ifndef __SPIRA_TIMER_HPP__
#define __SPIRA_TIMER_HPP__

#include <chrono>
#include <memory>
#include "spira/stream.hpp"
#include "spira/source.hpp"

namespace spira {
  class timer : public source<unsigned long long int> {
  public:
    timer(double fps=1000);
    timer(const timer& other);
    timer& operator =(timer& other);
    friend void swap(timer& a, timer& b);
    void poll();
    void reset();
  private:
    struct impl; std::shared_ptr<impl> pimpl;
  };
}

#endif

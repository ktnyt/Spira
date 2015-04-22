/******************************************************************************
**  spira_generator.hpp
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

#ifndef __SPIRA_TIMER_HPP__
#define __SPIRA_TIMER_HPP__

#include <memory>
#include <chrono>
#include <thread>

#include "spira_stream.hpp"

namespace spira {
  typedef long double FPS;
  typedef unsigned long long int FRAME;
  typedef unsigned long long int TIME;
  class timer : public stream<TIME> {
  public:
    timer(FPS fps=1000);
    ~timer();
    void start();
    void stop();
    void reset();
  private:
    struct timer_impl;
    std::unique_ptr<timer_impl> impl_t;
  };
}

#endif

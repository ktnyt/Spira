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

#include "spira_timer.hpp"

namespace spira {
  struct timer::timer_impl {
    std::chrono::steady_clock::time_point init;
    std::chrono::steady_clock::time_point curr;
    std::thread thread;
    bool running;
    FPS fps;
    TIME time;
    FRAME frame;
  };

  timer::timer(FPS fps) : impl_t(std::unique_ptr<timer_impl>(new timer_impl())) {
    this->impl_t->fps = fps;
    this->impl_t->init = std::chrono::steady_clock::now();
    this->start();
  }

  timer::~timer() {
    this->stop();
  }

  void timer::start() {
    if(!this->impl_t->running) {
      this->impl_t->running = true;
      this->impl_t->time = 0;
      this->impl_t->frame = 0;
      this->impl_t->thread = std::thread([&](){
        this->push(0);
        while(this->impl_t->running) {
          this->impl_t->curr = std::chrono::steady_clock::now();
          std::chrono::nanoseconds duration = (this->impl_t->curr - this->impl_t->init);
          this->impl_t->time = duration.count();
          FRAME now = ((this->impl_t->time * this->impl_t->fps) / 1000000000);
          if(now > this->impl_t->frame) {
            while(now > this->impl_t->frame) this->impl_t->frame++;
            this->push(this->impl_t->time);
          }
        }
      });
    }
  }

  void timer::stop() {
    if(this->impl_t->running) {
      this->impl_t->running = false;
      this->impl_t->thread.join();
    }
  }

  void timer::reset() {
    this->impl_t->init = std::chrono::steady_clock::now();
    this->impl_t->frame = 0;
  }
}

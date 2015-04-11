/******************************************************************************
**  spira_stream.hpp
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

#ifndef __SPIRA_STREAM_WRAPPER_HPP__
#define __SPIRA_STREAM_WRAPPER_HPP__

#include "spira_stream.hpp"

namespace spira {
  template<typename T>
  class streamw {
  public:
    /* Original Constructor */
    streamw(DUPLICATES d_flag=DUPLICATES::TAKE)
      : ptr(std::make_shared<spira::stream<T> >(d_flag)) { }

    /* Constructor with seed */
    streamw(T seed, DUPLICATES d_flag=DUPLICATES::TAKE)
      : ptr(std::make_shared<spira::stream<T> >(seed, d_flag)) { }

    /* Mirror Constructor */
    streamw(streamw<T>& streamw0, DUPLICATES d_flag=DUPLICATES::TAKE)
      : ptr(std::make_shared<spira::stream<T> >((*streamw0.ptr), d_flag)) { }

    /* Merge Constructor */
    streamw(streamw<T>& streamw1, streamw<T>& streamw2, DUPLICATES d_flag=DUPLICATES::TAKE)
      : ptr(std::make_shared<spira::stream<T> >((*streamw1.ptr), (*streamw2.ptr), d_flag)) { }

    /* Filter Constructor */
    streamw(streamw<T>& streamw0, const std::function<bool(T)> filter, DUPLICATES d_flag=DUPLICATES::TAKE)
      : ptr(std::make_shared<spira::stream<T> >((*streamw0.ptr), filter, d_flag)) { }

    /* While Constructor */
    streamw(streamw<T>& streamw0, streamw<bool>& streamw1, TAKE_WHILE t_flag=TAKE_WHILE::TRUE, DUPLICATES d_flag=DUPLICATES::TAKE)
      : ptr(std::make_shared<spira::stream<T> >((*streamw0.ptr), (*streamw1.ptr), t_flag, d_flag)) { }

    /* Map Constructor */
    template<typename U>
    streamw(streamw<U>& streamw0, const std::function<T(U)> map, DUPLICATES d_flag=DUPLICATES::TAKE)
      : ptr(std::make_shared<spira::stream<T> >((*streamw0.ptr), map, d_flag)) { }

    /* Scan Constructor */
    streamw(streamw<T>& streamw0, T seed, const std::function<T(T,T)> scan, DUPLICATES d_flag=DUPLICATES::TAKE)
      : ptr(std::make_shared<spira::stream<T> >((*streamw0.ptr), seed, scan, d_flag)) { }

    /* Combine Constructor */
    template<typename T1, typename T2>
    streamw(streamw<T1>& streamw1, streamw<T2>& streamw2, SAMPLED_BY s_flag=SAMPLED_BY::BOTH, DUPLICATES d_flag=DUPLICATES::TAKE)
      : ptr(std::make_shared<spira::stream<T> >((*streamw1.ptr), (*streamw2.ptr), s_flag, d_flag)) { }

    /* Push values into streamw */
    void push(const T& value) {
      this->ptr->push(value);
    }

    /* Bind side-effects to streamw */
    void bind(const std::function<void(T)> function) {
      this->ptr->bind(function);
    }

  private:
    template<typename U>
    friend class streamw;

    std::shared_ptr<stream<T> > ptr;
  };
}

#endif

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

#ifndef __SPIRA_STREAM_HPP__
#define __SPIRA_STREAM_HPP__

#include <list>
#include <functional>
#include <memory>
#include <exception>

#include "config.h"

namespace spira {
  enum class SAMPLED_BY {FIRST, SECOND, BOTH};
  enum class DUPLICATES {TAKE, SKIP};
  enum class TAKE_WHILE {TRUE, FALSE};

  template<typename T>
  class stream {
  public:
    /* Original Constructor */
    stream(DUPLICATES d_flag=DUPLICATES::TAKE);

    /* Constructor with seed */
    stream(T seed, DUPLICATES d_flag=DUPLICATES::TAKE);

    /* Mirror Constructor */
    stream(stream<T>& stream0, DUPLICATES d_flag=DUPLICATES::TAKE);

    /* Merge Constructor */
    stream(stream<T>& stream1, stream<T>& stream2, DUPLICATES d_flag=DUPLICATES::TAKE);

    /* List Merge Constructor */
    stream(std::list<stream<T>* > streams, DUPLICATES d_flag=DUPLICATES::TAKE);

    /* Filter Constructor */
    stream(stream<T>& stream0, const std::function<bool(T)> filter, DUPLICATES d_flag=DUPLICATES::TAKE);

    /* While Constructor */
    stream(stream<T>& stream0, stream<bool>& stream1, TAKE_WHILE t_flag=TAKE_WHILE::TRUE, DUPLICATES d_flag=DUPLICATES::TAKE);

    /* Map Constructor */
    template<typename U>
    stream(stream<U>& stream0, const std::function<T(U)> map, DUPLICATES d_flag=DUPLICATES::TAKE);

    /* Scan Constructor */
    stream(stream<T>& stream0, T seed, const std::function<T(T,T)> scan, DUPLICATES d_flag=DUPLICATES::TAKE);

    /* Combine Constructor */
    template<typename T1, typename T2>
    stream(stream<T1>& stream1, stream<T2>& stream2, SAMPLED_BY s_flag=SAMPLED_BY::BOTH, DUPLICATES d_flag=DUPLICATES::TAKE);

    /* Push values into stream */
    void push(const T& value);

    /* Bind side-effects to stream */
    void bind(const std::function<void(T)> function);

  private:
    template<typename U>
    friend class stream;

    struct stream_impl;
    std::unique_ptr<stream_impl> impl;
  };
}

#include "spira_stream_impl.hpp"

#endif

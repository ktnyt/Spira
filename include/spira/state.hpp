/******************************************************************************
 *
 * include/spira/state.hpp
 *
 * @author Copyright (C) 2015 Kotone Itaya
 * @version 2.2.0
 * @created  2015/12/30 Kotone Itaya -- Created!
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

#ifndef __SPIRA_STATE_HPP__
#define __SPIRA_STATE_HPP__

#include <list>
#include <memory>
#include <cstdint>
#include "spira/stream.hpp"

namespace spira {
  template<typename T>
  class state : public stream<T> {
  public:
    state();
    state(stream<T> origin);
    state(const state& other);
    state(state&& other) noexcept;
    state& operator =(const state& other);
    state& operator =(state&& other) noexcept;
    friend void swap(state& a, state& b);
    void setup(stream<T> origin);
    void update();
    void latest();
  private:
    struct impl; std::shared_ptr<impl> pimpl;
  };
}

#include "state_impl.hpp"

#endif

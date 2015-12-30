/******************************************************************************
 *
 * include/spira/state_impl.hpp
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

#ifndef __SPIRA_STATE_IMPL_HPP__
#define __SPIRA_STATE_IMPL_HPP__

namespace spira {
  template<typename T>
  struct state<T>::impl {
    std::list<T> buffer;
  };
  
  template<typename T>
  state<T>::state() : pimpl(new impl()) {}

  template<typename T>
  state<T>::state(stream<T> origin) : pimpl(new impl()) {
    this->plug(origin);
  }
  
  template<typename T>
  state<T>::state(const state<T>& other) : pimpl(other.pimpl) {}
  
  template<typename T>
  state<T>::state(state<T>&& other) noexcept : pimpl(other.pimpl) {
    other.pimpl = nullptr;
  }
  
  template<typename T>
  state<T>& state<T>::operator =(const state<T>& other) {
    state<T> another(other);
    *this = std::move(another);
    return *this;
  }
  
  template<typename T>
  state<T>& state<T>::operator =(state<T>&& other) noexcept {
    swap(*this, other);
    return *this;
  }
  
  template<typename T>
  void swap(state<T>& a, state<T>& b) {
    std::swap(a.pimpl, b.pimpl);
  }

  template<typename T>
  void state<T>::plug(stream<T> origin) {
    origin.bind([=](T value){
        pimpl->buffer.push_back(value);
      });
  }

  template<typename T>
  void state<T>::update() {
    typename std::list<T>::const_iterator value;
    for(value = pimpl->buffer.begin(); value != pimpl->buffer.end(); ++value) {
      this->push(*value);
    }
    pimpl->buffer.clear();
  }

  template<typename T>
  void state<T>::latest() {
    this->push(pimpl->buffer.back());
    pimpl->buffer.clear();
  }
}

#endif

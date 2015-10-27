/******************************************************************************
 *
 * stream_impl.hpp
 *
 * @author Copyright (C) 2015 Kotone Itaya
 * @version 2.0.0
 * @created  2015/10/15 Kotone Itaya -- Created!
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

#ifndef __SPIRA_STREAM_IMPL_HPP__
#define __SPIRA_STREAM_IMPL_HPP__

namespace spira {
  template<typename T>
  struct stream<T>::impl {
    T value;
    std::list<std::function<void(T)> > bind_list;
    std::list<std::function<void(T)> > glue_list;
    std::list<std::function<void(T)> > hook_list;
  };

  template<typename T>
  stream<T>::stream() : pimpl(std::shared_ptr<impl>(new impl())) {}

  template<typename T>
  stream<T>::stream(const stream<T>& other) : pimpl(std::shared_ptr<impl>(new impl())) {
    this->pimpl = other.pimpl;
  }

  template<typename T>
  stream<T>& stream<T>::operator =(stream<T>& other) {
    swap(*this, other);
    return *this;
  }

  template<typename T>
  void swap(stream<T>& a, stream<T>& b) {
    std::swap(a.pimpl, b.pimpl);
  }

  template<typename T>
  stream<T> stream<T>::unique() {
    stream<T> ret;
    this->hook([=](T value){if(ret.pimpl->value != value) ret.push(value);});
    return ret;
  }

  template<typename T>
  stream<T> stream<T>::mirror() {
    stream<T> ret;
    this->hook([=](T value){ret.push(value);});
    return ret;
  }

  template<typename T>
  stream<T> stream<T>::merge(stream<T>& other) {
    stream<T> ret;
    this->hook([=](T value){ret.push(value);});
    other.hook([=](T value){ret.push(value);});
    return ret;
  }

  template<typename T>
  stream<T> stream<T>::filter(std::function<bool(T)> filter) {
    stream<T> ret;
    this->hook([=](T value){if(filter(value)) ret.push(value);});
    return ret;
  }

  template<typename T>
  stream<T> stream<T>::whilst(stream<bool>& whilst) {
    stream<T> ret;
    this->hook([=](T value){if(whilst.pimpl->value) ret.push(value);});
    return ret;
  }

  template<typename T>
  stream<T> stream<T>::scan(T seed, const std::function<T(T,T)> scan) {
    stream<T> ret;
    this->hook([=](T value){ret.push(scan(ret.pimpl->value, value));});
    return ret;
  }

  template<typename T>
  template<typename U>
  stream<U> stream<T>::map(std::function<U(T)> map) {
    stream<U> ret;
    this->hook([=](T value){ret.push(map(value));});
    return ret;
  }

  template<typename T>
  template<typename U>
  stream<std::pair<T, U> > stream<T>::combine(stream<U>& other, SAMPLED_BY flag) {
    stream<std::pair<T, U> > ret;
    ret.pimpl->value.first = this->pimpl->value;
    ret.pimpl->value.second = other.pimpl->value;
    this->glue([=](T value){
        ret.pimpl->value.first = value;
        if(flag != SAMPLED_BY::SECOND) {
          ret.call();
        }
      });
    other.glue([=](T value){
        ret.pimpl->value.second = value;
        if(flag != SAMPLED_BY::FIRST) {
          ret.call();
        }
      });
    return ret;
  }

  template<typename T>
  stream<T> operate(stream<T> a, stream<T> b, std::function<T(T, T)> operation) {
    return a.combine(b, SAMPLED_BY::BOTH)
      .map(std::function<T(std::pair<T, T>)>([operation](std::pair<T, T> value){
            return operation(value.first, value.second);
          }));
  }

  template<typename T>
  stream<T> operator ==(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a == b;}));
  }

  template<typename T>
  stream<T> operator !=(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a != b;}));
  }

  template<typename T>
  stream<T> operator <(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a < b;}));
  }

  template<typename T>
  stream<T> operator >(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a > b;}));
  }

  template<typename T>
  stream<T> operator <=(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a <= b;}));
  }

  template<typename T>
  stream<T> operator >=(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a >= b;}));
  }

  template<typename T>
  stream<T> operator +(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a + b;}));
  }

  template<typename T>
  stream<T> operator -(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a - b;}));
  }

  template<typename T>
  stream<T> operator *(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a * b;}));
  }

  template<typename T>
  stream<T> operator /(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a / b;}));
  }

  template<typename T>
  stream<T> operator %(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a % b;}));
  }

  template<typename T>
  stream<T> operator &(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a & b;}));
  }

  template<typename T>
  stream<T> operator ^(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a ^ b;}));
  }

  template<typename T>
  stream<T> operator |(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a | b;}));
  }

  template<typename T>
  stream<T> operator &&(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a && b;}));
  }

  template<typename T>
  stream<T> operator ||(stream<T> a, stream<T> b) {
    return operate(a, b, std::function<T(T, T)>([](T a, T b){return a || b;}));
  }

  template<typename T>
  void stream<T>::bind(const std::function<void(T)> function) {
    this->pimpl->bind_list.push_back(function);
  }

  template<typename T>
  void stream<T>::glue(const std::function<void(T)> function) {
    this->pimpl->glue_list.push_back(function);
  }

  template<typename T>
  void stream<T>::hook(const std::function<void(T)> function) {
    this->pimpl->hook_list.push_back(function);
  }

  template<typename T>
  void stream<T>::listcall(const std::list<std::function<void(T)> > list) const {
    typename std::list<std::function<void(T)> >::const_iterator func;
    for(func = list.begin(); func != list.end(); ++func) {
      (*func)(this->pimpl->value);
    }
  }

  template<typename T>
  void stream<T>::call() const {
    this->listcall(this->pimpl->bind_list);
    this->listcall(this->pimpl->glue_list);
    this->listcall(this->pimpl->hook_list);
  }

  template<typename T>
  void stream<T>::push(T value) const {
    this->pimpl->value = value;
    this->call();
  }
}

#endif

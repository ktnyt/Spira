/******************************************************************************
 *
 * stream.hpp
 *
 * @author Copyright (C) 2015 Kotone Itaya
 * @version 1.0.0
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

#ifndef __SPIRA_STREAM_HPP__
#define __SPIRA_STREAM_HPP__

#include <functional>
#include <list>
#include <memory>

namespace spira {
  template<typename T>
  class stream {
  public:
    template<typename U>
    friend class stream;

    stream() {}

    stream(T init) : value(init) {}

    stream(const stream<T>& other) {
      this->T = other.T;
      this->bind_list = other.bind_list;
      this->glue_list = other.glue_list;
      this->hook_list = other.hook_list;
    }

    ~stream() {
      while(!this->streams.empty()) {
        delete this->streams.front();
        this->streams.pop_front();
      }
    }

    stream<T>& operator =(stream<T>& other) {
      swap(*this, other);
      return *this;
    }

    template<typename U>
    friend void swap(stream<U>& a, stream<U>& b);

    void bind(const std::function<void(T)> function) {
      this->bind_list.push_back(function);
    }

    stream<T>* mirror() {
      stream<T>* ptr = new stream<T>();
      this->streams.push_back(ptr);
      this->hook([=](T value){ptr->push(value);});
      return ptr;
    }

    stream<T>* merge(stream<T>* other) {
      stream<T>* ptr = new stream<T>();
      this->streams.push_back(ptr);
      this->hook([=](T value){ptr->push(value);});
      other->hook([=](T value){ptr->push(value);});
      return ptr;
    }

    stream<T>* filter(const std::function<bool(T)> filter) {
      stream<T>* ptr = new stream<T>();
      this->streams.push_back(ptr);
      this->hook([=](T value){if(filter(value)) ptr->push(value);});
      return ptr;
    }

    stream<T>* whilst(stream<bool>* whilst) {
      stream<T>* ptr = new stream<T>();
      this->streams.push_back(ptr);
      this->hook([=](T value){
          if(whilst->value) {
            ptr->push(value);
          }
        });
      return ptr;
    }

  protected:
    void glue(const std::function<void(T)> function) {
      this->glue_list.push_back(function);
    }

    void hook(const std::function<void(T)> function) {
      this->hook_list.push_back(function);
    }

    void listcall(const std::list<std::function<void(T)> > list) {
      typename std::list<std::function<void(T)> >::const_iterator func;
      for(func = list.begin(); func != list.end(); ++func) {
        (*func)(this->value);
      }
    }

    void call() {
      this->listcall(this->bind_list);
      this->listcall(this->glue_list);
      this->listcall(this->hook_list);
    }

    void push(T value) {
      this->value = value;
      this->call();
    }

  private:
    T value;
    std::list<std::function<void(T)> > bind_list;
    std::list<std::function<void(T)> > glue_list;
    std::list<std::function<void(T)> > hook_list;
    std::list<stream<T>* > streams;
  };

  template<typename T>
  void swap(stream<T>& a, stream<T>& b) {
    std::swap(a.value, b.value);
    std::swap(a.bind_list, b.bind_list);
    std::swap(a.glue_list, b.glue_list);
    std::swap(a.hook_list, b.hook_list);
  }
}

#endif

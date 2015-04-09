/******************************************************************************
**  spira_impl.hpp
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

namespace spira {
  template<typename T>
  struct stream<T>::stream_impl {
    T value;
    DUPLICATES flag_d;

    std::list<std::function<void(T)> > bind_list;
    std::list<std::function<void(T)> > glue_list;
    std::list<std::function<void(T)> > hook_list;

    void glue(const std::function<void(T)> function) {
      this->glue_list.push_back(function);
    }

    void hook(const std::function<void(T)> function) {
      this->hook_list.push_back(function);
    }

    void call(const std::list<std::function<void(T)> > list) {
      typename std::list<std::function<void(T)> >::const_iterator func;
      for(func = list.begin(); func != list.end(); ++func) {
        (*func)(this->value);
      }
    }

    void call() {
      this->call(bind_list);
      this->call(glue_list);
      this->call(hook_list);
    }
  };

  /* Original Constructor */
  template<typename T>
  stream<T>::stream(DUPLICATES d_flag) : impl(std::make_unique<stream<T>::stream_impl>()) {
    this->impl->flag_d = d_flag;
  }

  /* Constructor with seed */
  template<typename T>
  stream<T>::stream(T seed, DUPLICATES d_flag) : stream(d_flag) {
    this->impl->value = seed;
  }

  /* Mirror Constructor */
  template<typename T>
  stream<T>::stream(stream<T>& stream0, DUPLICATES d_flag) : stream(d_flag) {
    stream0.impl->hook([&](T value){this->push(value);});
  }

  /* Merge Constructor */
  template<typename T>
  stream<T>::stream(stream<T>& stream1, stream<T>& stream2, DUPLICATES d_flag) : stream(d_flag) {
    stream1.impl->hook([&](T value){this->push(value);});
    stream2.impl->hook([&](T value){this->push(value);});
  }

  /* Filter Constructor */
  template<typename T>
  stream<T>::stream(stream<T>& stream0, const std::function<bool(T)> filter, DUPLICATES d_flag) : stream(d_flag) {
    stream0.impl->hook([&](T value){if(filter(value)) this->push(value);});
  }

  /* While Constructor */
  template<typename T>
  stream<T>::stream(stream<T>& stream0, stream<bool>& stream1, TAKE_WHILE t_flag, DUPLICATES d_flag) : stream(d_flag) {
    stream0.impl->hook([&, t_flag](T value){
        std::string str = stream1.impl->value ? "TRUE" : "FALSE";
        if(t_flag == TAKE_WHILE::TRUE) {
          if(stream1.impl->value) {
            this->push(value);
          }
        }
        if(t_flag == TAKE_WHILE::FALSE) {
          if(!stream1.impl->value) {
            this->push(value);
          }
        }
      });
  }

  /* Map Constructor */
  template<typename T>
  template<typename U>
  stream<T>::stream(stream<U>& stream0, const std::function<T(U)> map, DUPLICATES d_flag) : stream(d_flag) {
    stream0.impl->hook([&](U value){this->push(map(value));});
  }

  /* Scan Constructor */
  template<typename T>
  stream<T>::stream(stream<T>& stream0, T seed, const std::function<T(T,T)> scan, DUPLICATES d_flag) : stream(d_flag) {
    this->impl->value = seed;
    stream0.impl->hook([&](T value){this->push(scan(this->impl->value, value));});
  }

  /* Combine Constructor */
  template<typename T>
  template<typename T1, typename T2>
  stream<T>::stream(stream<T1>& stream1, stream<T2>& stream2, SAMPLED_BY s_flag, DUPLICATES d_flag) : stream(d_flag) {
    this->impl->value.first = stream1.impl->value;
    this->impl->value.second = stream2.impl->value;
    stream1.impl->glue([&, s_flag](T1 value){
        this->impl->value.first = value;
        if(s_flag != SAMPLED_BY::SECOND) {
          this->impl->call();
        }
      });
    stream2.impl->glue([&, s_flag](T2 value){
        this->impl->value.second = value;
        if(s_flag != SAMPLED_BY::FIRST) {
          this->impl->call();
        }
      });
  }

  template<typename T>
  void stream<T>::bind(const std::function<void(T)> function) {
    this->impl->bind_list.push_back(function);
  }

  template<typename T>
  void stream<T>::push(const T& value) {
    if(this->impl->flag_d == DUPLICATES::SKIP) {
      if(this->impl->value == value) {
        return;
      }
    }
    this->impl->value = value;
    this->impl->call();
  }
}

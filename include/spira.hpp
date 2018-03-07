#include <functional>
#include <tuple>

#include <iostream>

namespace spira {

template <class T>
class Variable {
 public:
  Variable() {}
  virtual ~Variable() {}

  virtual const T& pull() { return value; }
  const T& get() const { return value; }
  void set(T v) { value = v; }

 private:
  T value;
};

template <class F>
class Node;

template <class O, class... I>
class Node<O(I...)> : public Variable<O> {
  using F = std::function<O(I...)>;

 public:
  Node(F f) : f(f), pulled(false) {}
  ~Node() {}

  Node<O(I...)>* operator()(Variable<I>*... args) {
    deps = std ::tuple<Variable<I>*...>(args...);
    return this;
  }

  decltype(auto) operator()(I... args) { return f(args...); }

  const O& pull() {
    if (!pulled) {
      invoke(std::make_index_sequence<sizeof...(I)>());
      pulled = true;
    }

    return Variable<O>::get();
  }

  void reset() { pulled = false; }

 private:
  template <std::size_t... S>
  void invoke(std::index_sequence<S...>) {
    std::cout << this << " invoke" << std::endl;
    Variable<O>::set(f(std::get<S>(deps)->pull()...));
  }

  std::tuple<Variable<I>*...> deps;
  F f;
  bool pulled;
};

}  // namespace spira

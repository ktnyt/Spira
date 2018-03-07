#define CATCH_CONFIG_MAIN
#include "spira.hpp"
#include "catch.hpp"

using namespace spira;

int inc(int a) { return a + 1; }
int dec(int a) { return a - 1; }
int mul(int a, int b) { return a * b; }

TEST_CASE("Simple case", "[simple]") {
  auto n_inc = new Node<int(int)>(inc);
  auto n_dec = new Node<int(int)>(dec);
  auto n_mul = new Node<int(int, int)>(mul);

  auto result = (*n_mul)(n_inc, n_dec);

  n_inc->set(42);
  n_dec->set(42);

  REQUIRE(result->pull() == 41 * 43);

  delete n_inc;
  delete n_dec;
  delete n_mul;
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "distributed_trace.h"

TEST_CASE("test_printHello") {
    CHECK(printHello() == 0);
}
TEST_CASE("test_1") {
    CHECK(1 == 1);
}
TEST_CASE("test_2") {
    CHECK(2 == 2);
}

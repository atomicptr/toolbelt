#include <iostream>

#include <toolbelt/unit_tests.hpp>

#include "tests/crc32_test.hpp"
#include "tests/make_smart_test.hpp"
#include "tests/string_test.hpp"

int main(int argc, char** argv) {
    toolbelt::test_suite s;

    add_crc32_tests(s);
    add_make_smart_tests(s);
    add_string_tests(s);

    return s.run_tests();
}

#ifndef __TESTS_CRC32_TEST_HPP__
#define __TESTS_CRC32_TEST_HPP__

#include <toolbelt/unit_tests.hpp>
#include <toolbelt/crc32.hpp>

#include <string>
#include <vector>

void add_crc32_tests(toolbelt::test_suite& s) {
    s.test("can crc32 \"Hello\"", []() {
        return ExpectEquals(toolbelt::crc32("Hello"), std::uint32_t{4157704578});
    });

    s.test("can crc32 \"World\"", []() {
        return ExpectEquals(toolbelt::crc32("World"), std::uint32_t{4223024711});
    });

    s.test("can crc32 \"Is this real life?\"", []() {
        return ExpectEquals(toolbelt::crc32("Is this real life?"), std::uint32_t{568811195});
    });

    s.test("can crc32 \"Test String\"", []() {
        return ExpectEquals(toolbelt::crc32("Test String"), std::uint32_t{2457313188});
    });

    s.test("can crc32 \"I don't know more test strings\"", []() {
        return ExpectEquals(toolbelt::crc32("I don't know more test strings"), std::uint32_t{3779608744});
    });
}

#endif

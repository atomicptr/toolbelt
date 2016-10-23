#ifndef __TESTS_STRING_TEST_HPP__
#define __TESTS_STRING_TEST_HPP__

#include <toolbelt/unit_tests.hpp>

#include <toolbelt/string.hpp>

void add_string_tests(toolbelt::test_suite& s) {
    s.test("can replace Java with C++14", []() {
        auto str = toolbelt::replace("Java is awesome", "Java", "C++14");

        return ExpectEquals(std::string{"C++14 is awesome"}, str);
    });

    s.test("can replace letters", []() {
        auto str = toolbelt::replace("AaAaAaAaAaAaAaAaAaAaAa", "A", "B");

        return ExpectEquals(std::string{"BaBaBaBaBaBaBaBaBaBaBa"}, str);
    });

    s.test("can replace with spaces", []() {
        auto str = toolbelt::replace("Luke, I'm your mother yes", "your mother yes", "your father! D:");

        return ExpectEquals(std::string{"Luke, I'm your father! D:"}, str);
    });

    s.test("can replace in both ways", []() {
        auto str = toolbelt::replace(toolbelt::replace("Hello\tWorld\tand\tUniverse", "\t", "\n"), "\n", "\t");

        return ExpectEquals(std::string{"Hello\tWorld\tand\tUniverse"}, str);
    });

    s.test("can replace nothing", []() {
        auto str = toolbelt::replace("Bacon Melt", "Veggie", "Bacon");

        return ExpectEquals(std::string{"Bacon Melt"}, str);
    });

    s.test("can replace empty string", []() {
        auto str = toolbelt::replace("", "", "toolbelt");

        return ExpectEquals(std::string{""}, str);
    });

    s.test("can split spaces", []() {
        auto strings = toolbelt::split("Lorem ipsum dolor sit amet", ' ');

        auto vec = std::vector<std::string>{"Lorem", "ipsum", "dolor", "sit", "amet"};

        return ExpectEquals(strings.size(), vec.size());
    });

    s.test("can split line breaks", []() {
        auto strings = toolbelt::split("Lorem\nipsum\ndolor\nsit\namet", '\n');

        auto vec = std::vector<std::string>{"Lorem", "ipsum", "dolor", "sit", "amet"};

        return ExpectEquals(strings.size(), vec.size());
    });

    s.test("can split nothing", []() {
        auto strings = toolbelt::split("Hello, World!", 'x');

        return ExpectEquals(std::string{"Hello, World!"}, strings[0]);
    });

    s.test("can lower string", []() {
        auto string = std::string{"HELLO WORLD"};

        return ExpectEquals(std::string{"hello world"}, toolbelt::to_lower(string));
    });

    s.test("can upper string", []() {
        auto string = std::string{"hello world"};

        return ExpectEquals(std::string{"HELLO WORLD"}, toolbelt::to_upper(string));
    });

    s.test("can trim from left", []() {
        return ExpectEquals(std::string{"Hello, World!"}, toolbelt::ltrim("          Hello, World!"));
    });

    s.test("can trim from right", []() {
        return ExpectEquals(std::string{"Hello, World!"}, toolbelt::rtrim("Hello, World!          "));
    });

    s.test("can trim", []() {
        return ExpectEquals(std::string{"Hello, World!"}, toolbelt::trim("     Hello, World!     "));
    });

    s.test("ends with .app", []() {
        return ExpectTrue(toolbelt::ends_with("BestAppEver.app", ".app"));
    });
}

#endif

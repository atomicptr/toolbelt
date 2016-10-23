#ifndef __TOOLBELT_UNIT_TESTS_HPP__
#define __TOOLBELT_UNIT_TESTS_HPP__

#include <functional>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

#define ExpectEquals(a, b) toolbelt::expect_equals(a, b, __FILE__, __LINE__)
#define ExpectTrue(a) toolbelt::expect_true(a, __FILE__, __LINE__)
#define ExpectFalse(a) toolbelt::expect_false(a, __FILE__, __LINE__)
#define ExpectNotNull(a) toolbelt::expect_not_null(a, __FILE__, __LINE__)

namespace toolbelt {
    namespace unit_tests_helper {
        template<typename T>
        auto to_string(T val) {
            std::ostringstream ss;
            ss << val;
            return ss.str();
        }
    }


    struct test_result {
        bool passed_;
        std::string message_;
        std::string file_;
        unsigned int line_;
    };

    template<typename T>
    inline test_result expect_equals(T a, T b, std::string file, unsigned int line) {
        bool result = (a == b);
        auto expected_str = unit_tests_helper::to_string(a);
        auto got_str = unit_tests_helper::to_string(b);
        auto message = std::string{"\""} + expected_str + "\" should be equal to \"" + got_str + "\"";

        test_result res = {
            .passed_ = result,
            .message_ = message,
            .file_ = file,
            .line_ = line
        };

        return res;
    }

    inline test_result expect_true(bool result, std::string file, unsigned int line) {
        auto got = std::string{result ? "true" : "false"};
        auto message = std::string{"true, got "} + got;

        test_result res = {
            .passed_ = result,
            .message_ = message,
            .file_ = file,
            .line_ = line
        };

        return res;
    }

    inline test_result expect_false(bool result, std::string file, unsigned int line) {
        auto got = std::string{result ? "true" : "false"};
        auto message = std::string{"false, got "} + got;

        test_result res = {
            .passed_ = result,
            .message_ = message,
            .file_ = file,
            .line_ = line
        };

        return res;
    }

    template<typename T>
    inline test_result expect_not_null(T* ptr, std::string file, unsigned int line) {
        test_result res = {
            .passed_ = (ptr != nullptr),
            .message_ = "pointer is not null",
            .file_ = file,
            .line_ = line
        };

        return res;
    }

    class test_suite {
    public:
        test_suite();

        void test(const std::string& desc, std::function<test_result()> test_function);

        bool run_tests();
    private:
        std::vector<std::pair<std::string, std::function<test_result()>>> tests_;
    };

    test_suite::test_suite() {
    }

    void test_suite::test(const std::string& desc, std::function<test_result()> test_function) {
        tests_.emplace_back(desc, test_function);
    }

    bool test_suite::run_tests() {
        auto num_tests = tests_.size();

        std::string lastfile = "";

        std::cout << "Toolbelt: Found " << num_tests << " unit tests:" << std::endl;

        auto failed_counter = 0u;

        for(auto& test : tests_) {
            auto& test_desc = test.first;
            auto& test_func = test.second;

            auto result = test_func();

            if(lastfile != result.file_) {
                std::cout << std::endl;
                lastfile = result.file_;
            }

            std::cout << (result.passed_ ? "\tPASS: " : "\tFAIL: ") << "" << result.file_ << ":" << result.line_ << ", " << test_desc << std::endl;

            if(!result.passed_) {
                std::cout << "\t\t=> " << result.message_<< std::endl;

                failed_counter++;
            }
        }

        std::cout << std::endl << (num_tests - failed_counter) << "/" << num_tests << " tests PASSED." << std::endl;

        return failed_counter > 0;
    }
}

#endif

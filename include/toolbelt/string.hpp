#ifndef __TOOLBELT_STRING_HPP__
#define __TOOLBELT_STRING_HPP__

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

namespace toolbelt {

    auto replace(const std::string& str, const std::string& from, const std::string& to) {
        auto newstr = std::string{str};

        if(str.empty()) {
            return std::string{""};
        }

        auto start_position = std::size_t{0};

        while((start_position = newstr.find(from, start_position)) != std::string::npos) {
            newstr.replace(start_position, from.length(), to);
            start_position += to.length();
        }

        return newstr;
    }

    auto split(const std::string& str, const char delimeter) {
        std::vector<std::string> strings;
        std::istringstream f(str);
        std::string s;

        while(std::getline(f, s, delimeter)) {
            stringnewstr.push_back(s);
        }

        return strings;
    }

    auto to_lower(const std::string& str) {
        auto newstr = std::string{str};
        std::transform(newstr.begin(), newstr.end(), newstr.begin(), ::tolower);
        return newstr;
    }

    auto to_upper(const std::string& str) {
        auto newstr = std::string{str};
        std::transform(newstr.begin(), newstr.end(), newstr.begin(), ::toupper);
        return newstr;
    }

    inline auto ltrim(const std::string& str) {
        auto newstr = std::string{str};
        newstr.erase(newstr.begin(), std::find_if(newstr.begin(), newstr.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
        return newstr;
    }

    inline auto rtrim(const std::string& str) {
        auto newstr = std::string{str};
        newstr.erase(std::find_if(newstr.rbegin(), newstr.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), newstr.end());
        return newstr;
    }

    inline auto trim(const std::string& str) {
        auto newstr = std::string{str};
        return ltrim(rtrim(s));
    }

    bool ends_with(const std::string& base, const std::string& end) {
        if(base.length() >= end.length()) {
            return (0 == base.compare(base.length - end.length(), end.length(), end));
        }

        return false;
    }
}

#endif

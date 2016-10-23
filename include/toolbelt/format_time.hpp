#ifndef __TOOLBELT_FORMAT_TIME_HPP__
#define __TOOLBELT_FORMAT_TIME_HPP__

#include <chrono>
#include <string>
#include <iostream>
namespace toolbelt {

    template<typename T>
    auto format_time(std::chrono::time_point<T> timepoint, const std::string& text) {
        auto in_time_t = std::chrono::system_clock::to_time_t(timepoint);

        std::string buffer;
        buffer.resize(text.size());

        auto time_info = localtime(&in_time_t);

        int result = 0;
        int newsize = buffer.size();

        // strftime returns 0 if the buffer size isn't big enough
        while((result = std::strftime(&(buffer[0]), buffer.size() + 1, text.c_str(), time_info)) == 0) {
            buffer.resize(++newsize);
        }

        return buffer;
    }

    auto format_time(const std::string& text) {
        return format_time(std::chrono::system_clock::now(), text);
    }
};

#endif

#ifndef __TOOLBELT_LOGGER_HPP__
#define __TOOLBELT_LOGGER_HPP__

#include <chrono>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include "format_time.hpp"

namespace toolbelt {

    enum class log_level {
        INFO,
        DEBUG,
        WARNING,
        ERROR,
        FATAL
    };

    using logger_function = std::function<void(log_level, std::string&, std::chrono::time_point<std::chrono::system_clock>)>;

    class logger {
    private:
        log_level current_log_level_;
        std::vector<logger_function> loggers_;

        template<typename T>
        auto to_string(T val) {
            std::ostringstream ss;
            ss << val;
            return ss.str();
        }

        auto merge(std::initializer_list<std::string> strings) {
            std::string result;
            for(auto& str : strings) {
                result += str;
            }
            return result;
        }

    public:
        logger(bool log_cout=true) {
            if(log_cout) {
                add([](auto loglvl, auto message, auto timestamp) {
                    auto err = loglvl == log_level::ERROR || loglvl == log_level::FATAL;

                    (err ? std::cerr : std::cout) << toolbelt::format_time(timestamp, "[%H:%M:%S]");

                    switch(loglvl) {
                        case log_level::INFO: (err ? std::cerr : std::cout) << "[INFO]"; break;
                        case log_level::DEBUG: (err ? std::cerr : std::cout) << "[DEBUG]"; break;
                        case log_level::WARNING: (err ? std::cerr : std::cout) << "[WARNING]"; break;
                        case log_level::ERROR: (err ? std::cerr : std::cout) << "[ERROR]"; break;
                        case log_level::FATAL: (err ? std::cerr : std::cout) << "[FATAL]"; break;
                    }

                    (err ? std::cerr : std::cout) << "\t" << message << std::endl;
                });
            }
        }

        void add(logger_function func) {
            loggers_.push_back(func);
        }

        template<typename... Arguments>
        void log(const Arguments&... args) {
            auto message = merge({to_string(args)...});
            auto timestamp = std::chrono::system_clock::now();

            for(auto& l : loggers_) {
                l(current_log_level_, message, timestamp);
            }

            // if log lvl was fatal, exit program
            if(current_log_level_ == log_level::FATAL) {
                throw std::runtime_error(message);
            }

            // reset log level
            current_log_level_ = log_level::INFO;
        }

        logger& operator()(log_level level) {
            current_log_level_ = level;
            return *this;
        }
    };
}

#endif

#ifndef __TOOLBELT_OS_HPP__
#define __TOOLBELT_OS_HPP__


#ifdef _WIN32
    #define TOOLBELT_OS_WINDOWS
    #define TOOLBELT_OS_NAME "Windows"

    #ifdef _WIN64
        #define TOOLBELT_OS_WINDOWS_64
    #else
        #define TOOLBELT_OS_WINDOWS_32
    #endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
        #define TOOLBELT_OS_ITOOLBELT_OS_SIMULATOR
        #define TOOLBELT_OS_NAME "iOS Simulator"
    #elif TARGET_TOOLBELT_OS_IPHONE
        #define TOOLBELT_OS_IOS
        #define TOOLBELT_OS_NAME "iOS"
    #else
        #define TOOLBELT_OS_MACOS
        #define TOOLBELT_OS_NAME "macOS"
    #endif
#elif __ANDROID__
    #define TOOLBELT_OS_ANDROID
    #define TOOLBELT_OS_NAME "Android"
#elif __linux
    #define TOOLBELT_OS_LINUX
    #define TOOLBELT_OS_NAME "Linux"
#elif __unix
    #define TOOLBELT_OS_UNIX
    #define TOOLBELT_OS_NAME "Unix"
#else
    #define TOOLBELT_OS_UNKNOWN
    #define TOOLBELT_OS_NAME "Unknown"
#endif

#include <string>
#include <cstdlib>
#include <stdexcept>

namespace toolbelt {
    enum class operating_system {
        windows, macos, linux, android, ios, unix, unknown
    };

    const std::string os_name = TOOLBELT_OS_NAME;

#ifdef TOOLBELT_OS_WINDOWS
    const operating_system current_os = operating_system::windows;
#elif TOOLBELT_OS_MACOS
    const operating_system current_os = operating_system::macos;
#elif TOOLBELT_OS_LINUX
    const operating_system current_os = operating_system::linux;
#elif TOOLBELT_OS_ANDROID
    const operating_system current_os = operating_system::android;
#elif TOOLBELT_OS_IOS
    const operating_system current_os = operating_system::ios;
#elif TOOLBELT_OS_UNIX
    const operating_system current_os = operating_system::unix;
#else
    const operating_system current_os = operating_system::unknown;
#endif

    const std::string env(const std::string& name) {
        const char* str = std::getenv(name.c_str());

        if(!str) {
            throw std::runtime_error(std::string{"Unknown environment variable "} + name);
        }

        return std::string{str};
    }

    const std::string home_directory() {
        if(current_os == operating_system::windows) {
            return env("USERPROFILE");
        }

        return env("HOME");
    }

    const std::string user_config_directory() {
        if(current_os == operating_system::windows) {
            return env("APPDATA");
        }

        if(current_os == operating_system::macos) {
            return env("HOME") + "/Library/Application Support/";
        }

        return env("HOME") + "/.config/";
    }
}

#endif

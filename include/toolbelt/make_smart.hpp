#ifndef __TOOLBELT_MAKE_SMART_HPP__
#define __TOOLBELT_MAKE_SMART_HPP__

#include <memory>
#include <utility>

namespace toolbelt {

    template<typename T, typename Constructor, typename Destructor, typename... Arguments>
    auto make_smart(Constructor construct, Destructor destruct, Arguments... args) {
        auto ptr = construct(std::forward<Arguments>(args)...);

        if(!ptr) {
            throw std::runtime_error("Error: Not able to create smart pointer");
        }

        return std::unique_ptr<T, decltype(destruct)>(ptr, destruct);
    }
}

#endif

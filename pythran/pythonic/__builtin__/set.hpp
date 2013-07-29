#ifndef PYTHONIC_BUILTIN_SET_HPP
#define PYTHONIC_BUILTIN_SET_HPP

#include "pythonic/types/set.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        types::empty_set set() {
            return types::empty_set();
        }

        template <class Iterable>
            types::set<typename std::remove_reference<Iterable>::type::iterator::value_type > set(Iterable&& t) {
                return types::set<typename std::remove_reference<Iterable>::type::iterator::value_type >(t.begin(), t.end());
            } 
        PROXY(pythonic::__builtin__,set);
    }

}
#endif

#ifndef PYTHONIC_BUILTIN_DICT_HPP
#define PYTHONIC_BUILTIN_DICT_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/dict.hpp"

#include <utility>

namespace pythonic {

    namespace __builtin__ {

        types::empty_dict dict() {
            return types::empty_dict();
        }

        template<class Iterable>
            types::dict<typename std::tuple_element<0, typename std::remove_reference<Iterable>::type::iterator::value_type>::type ,
            typename std::tuple_element<1, typename std::remove_reference<Iterable>::type::iterator::value_type>::type >
                dict( Iterable&& iterable) {
                    types::dict<typename std::tuple_element<0, typename std::remove_reference<Iterable>::type::iterator::value_type>::type ,
                    typename std::tuple_element<1, typename std::remove_reference<Iterable>::type::iterator::value_type>::type > out=types::empty_dict();
                    for(auto const & i : iterable)
                        out[std::get<0>(i)] = std::get<1>(i);
                    return out;
                }

        PROXY(pythonic::__builtin__,dict);

    }

}

#endif

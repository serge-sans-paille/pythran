#ifndef PYTHONIC_INCLUDE_BUILTIN_DICT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_DICT_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace {
            inline types::empty_dict dict();

            template<class Iterable>
                inline
                types::dict<
                    typename std::tuple_element<0, typename std::remove_reference<Iterable>::type::iterator::value_type>::type,
                    typename std::tuple_element<1, typename std::remove_reference<Iterable>::type::iterator::value_type>::type
                    >
                    dict(Iterable&& iterable);
        }

        PROXY_DECL(pythonic::__builtin__, dict);

    }

}

#endif


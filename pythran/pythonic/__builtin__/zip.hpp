#ifndef PYTHONIC_BUILTIN_ZIP_HPP
#define PYTHONIC_BUILTIN_ZIP_HPP

#include "pythonic/types/list.hpp"
#include "pythonic/types/tuple.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/fwd.hpp"

#include "pythonic/__builtin__/len.hpp"
#include "pythonic/__builtin__/min.hpp"

namespace pythonic {

    namespace __builtin__ {

        template<class Iterator0, class... Iterators>
            types::list< std::tuple<typename Iterator0::value_type, typename Iterators::value_type... > >
            _zip(size_t n, Iterator0 first, Iterators...  iters)
            {
                types::list< std::tuple< typename Iterator0::value_type, typename Iterators::value_type... > > out = types::empty_list();
                out.reserve(n);
                for(size_t i=0; i<n ; ++i, ++first, utils::fwd(++iters...)) {
                    out.push_back(std::make_tuple( *first, *iters... ));
                }
                return out;
            }

        template<class List0, class... Lists>
            types::list< std::tuple<typename std::remove_reference<List0>::type::value_type, typename std::remove_reference<Lists>::type::value_type... > > zip(List0 && s0, Lists &&...  lists) {
                size_t n = min(len(std::forward<List0>(s0)), len(std::forward<Lists>(lists))...);
                return _zip(n, s0.begin(), lists.begin()...);
            }

        types::empty_list zip() {
            return types::empty_list();
        }

        PROXY(pythonic::__builtin__,zip);

    }

}

#endif

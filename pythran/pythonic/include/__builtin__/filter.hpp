#ifndef PYTHONIC_INCLUDE_BUILTIN_FILTER_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILTER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __builtin__ {

        template<class F, class Iterable>
            types::list<typename Iterable::iterator::value_type>
            filter(F const& f, Iterable const& iterable);

        PROXY_DECL(pythonic::__builtin__, filter);

    }

}

#endif

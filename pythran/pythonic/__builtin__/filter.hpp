#ifndef PYTHONIC_BUILTIN_FILTER_HPP
#define PYTHONIC_BUILTIN_FILTER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __builtin__ {
        template<class F, class Iterable>
            types::list<typename Iterable::iterator::value_type> filter(F const& f, Iterable const& iterable) { /* does not implement the full standard */
                types::list<typename Iterable::iterator::value_type> out;
                out=types::empty_list();
                std::copy_if(iterable.begin(), iterable.end(), std::back_inserter(out), f);
                return out;
            }

        PROXY(pythonic::__builtin__, filter);

    }

}

#endif


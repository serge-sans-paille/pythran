#ifndef PYTHONIC_INCLUDE_BUILTIN_REVERSED_HPP
#define PYTHONIC_INCLUDE_BUILTIN_REVERSED_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        template <class Iterable>
            struct _reversed {

                using value_type = typename Iterable::value_type;
                using iterator = typename Iterable::reverse_iterator;
                using const_iterator = typename Iterable::const_reverse_iterator;

                Iterable iterable;

                _reversed();
                _reversed(Iterable const& iterable);
                iterator begin();
                iterator end();
                const_iterator begin() const;
                const_iterator end() const;
            };


        template <class Iterable>
            _reversed<Iterable> reversed(Iterable const& iterable);

        PROXY_DECL(pythonic::__builtin__, reversed);

    }

}

#endif

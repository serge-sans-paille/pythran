#ifndef PYTHONIC_BUILTIN_REVERSED_HPP
#define PYTHONIC_BUILTIN_REVERSED_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        template <class Iterable>
            struct _reversed {
                Iterable iterable;
                _reversed() {}
                _reversed(Iterable const& iterable) : iterable(iterable) {}
                typedef typename Iterable::value_type value_type;
                typedef typename Iterable::reverse_iterator iterator;
                typedef typename Iterable::const_reverse_iterator const_iterator;
                iterator begin() { return iterable.rbegin(); }
                iterator end() { return iterable.rend(); }
                const_iterator begin() const { return iterable.rbegin(); }
                const_iterator end() const { return iterable.rend(); }
            };


        template <class Iterable>
            _reversed<Iterable> reversed(Iterable const& iterable) {
                return _reversed<Iterable>(iterable);
            }

        PROXY(pythonic::__builtin__, reversed);

    }

}
#endif

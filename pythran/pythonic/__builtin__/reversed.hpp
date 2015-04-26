#ifndef PYTHONIC_BUILTIN_REVERSED_HPP
#define PYTHONIC_BUILTIN_REVERSED_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/include/__builtin__/reversed.hpp"

namespace pythonic {

    namespace __builtin__ {

        template <class Iterable>
            _reversed<Iterable>::_reversed()
            {}

        template <class Iterable>
            _reversed<Iterable>::_reversed(Iterable const& iterable):
                iterable(iterable)
            {}

        template <class Iterable>
            typename _reversed<Iterable>::iterator
            _reversed<Iterable>::begin()
            {
                return iterable.rbegin();
            }

        template <class Iterable>
            typename _reversed<Iterable>::iterator
            _reversed<Iterable>::end()
            {
                return iterable.rend();
            }

        template <class Iterable>
            typename _reversed<Iterable>::const_iterator
            _reversed<Iterable>::begin() const
            {
                return iterable.rbegin();
            }

        template <class Iterable>
            typename _reversed<Iterable>::const_iterator
            _reversed<Iterable>::end() const
            {
                return iterable.rend();
            }

        template <class Iterable>
            _reversed<Iterable> reversed(Iterable const& iterable)
            {
                return _reversed<Iterable>(iterable);
            }

        PROXY_IMPL(pythonic::__builtin__, reversed);

    }

}

#endif

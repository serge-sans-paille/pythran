#ifndef PYTHONIC_BUILTIN_ITER_HPP
#define PYTHONIC_BUILTIN_ITER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/include/__builtin__/iter.hpp"

namespace pythonic {

    namespace __builtin__ {


        /// _iter implementation

        template <class T>
            _iter<T>::_iter()
            {}

        template <class T>
            _iter<T>::_iter(T data):
                iterator(data.begin()),
                _end(data.end()),
                data(data)
            {}

        template <class T>
            typename _iter<T>::iterator& _iter<T>::begin()
            {
                return *this;
            }

        template <class T>
            typename _iter<T>::iterator const& _iter<T>::begin() const
            {
                return *this;
            }

        template <class T>
            typename _iter<T>::iterator const& _iter<T>::end() const
            {
                return _end;
            }

        /// iter implementation

        template <class T>
            _iter<typename std::remove_cv<typename std::remove_reference<T>::type>::type>
            iter(T&& t)
            {
                return _iter<typename std::remove_cv<typename std::remove_reference<T>::type>::type>(std::forward<T>(t));
            }

        PROXY_IMPL(pythonic::__builtin__,iter);

    }

}

#endif


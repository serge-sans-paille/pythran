#ifndef PYTHONIC_BUILTIN_ITER_HPP
#define PYTHONIC_BUILTIN_ITER_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {
        template <class T>
            struct _iter : T::iterator {
                typedef typename T::iterator iterator;
                iterator _end;
                T data;
                _iter() {}
                _iter(T data) : iterator(data.begin()), _end(data.end()), data(data) {
                }
                iterator& begin() { return *this; }
                iterator const& begin() const { return *this; }
                iterator const& end() const { return _end; }
            };

        template <class T>
            _iter<typename std::remove_cv<typename std::remove_reference<T>::type>::type> iter(T&& t)  {
                return _iter<typename std::remove_cv<typename std::remove_reference<T>::type>::type>(std::forward<T>(t));
            }

        PROXY(pythonic::__builtin__,iter);

    }

}

#endif


#ifndef PYTHONIC_INCLUDE_BUILTIN_ITER_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ITER_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        template <class T>
            struct _iter : T::iterator
            {
                using iterator = typename T::iterator;

                iterator _end;
                T data;

                _iter();
                _iter(T data);
                iterator& begin();
                iterator const& begin() const;
                iterator const& end() const;
            };

        template <class T>
            _iter<typename std::remove_cv<typename std::remove_reference<T>::type>::type>
            iter(T&& t);

        PROXY_DECL(pythonic::__builtin__, iter);

    }

}

#endif

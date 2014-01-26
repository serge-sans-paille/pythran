#ifndef PYTHONIC_NUMPY_FLATNONZERO_HPP
#define PYTHONIC_NUMPY_FLATNONZERO_HPP

#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            types::ndarray<long, 1> flatnonzero(E const& expr) {
                long n = expr.size();
                long *buffer = new long[n];
                long *iter = buffer;
                for(long i=0;i<n;++i) 
                    if(expr.at(i))
                        *iter++ = i;
                long shape[1] = { iter - buffer };
                return types::ndarray<long, 1>(buffer, shape);
            }
        template<class E>
            auto flatnonzero(types::list<E> const & l)
            -> decltype(flatnonzero(asarray(l)))
            {
                return flatnonzero(asarray(l));
            }

        PROXY(pythonic::numpy, flatnonzero);

    }

}

#endif


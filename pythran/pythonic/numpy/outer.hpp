#ifndef PYTHONIC_NUMPY_OUTER_HPP
#define PYTHONIC_NUMPY_OUTER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 2> outer(E const& a, F const& b)
            {
                types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 2> out(types::array<long, 2>{{a.size(), b.size()}}, __builtin__::None);
                for(size_t i=0; i<a.size(); ++i)
                    for(size_t j=0; j<b.size(); ++j)
                        out.buffer[i * b.size() + j] = a.at(i) * b.at(j);
                return out;
            }

        PROXY(pythonic::numpy, outer);

    }

}

#endif


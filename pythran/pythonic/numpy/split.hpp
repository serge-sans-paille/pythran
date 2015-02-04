#ifndef PYTHONIC_NUMPY_SPLIT_HPP
#define PYTHONIC_NUMPY_SPLIT_HPP

#include "pythonic/numpy/array_split.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::list<types::ndarray<T,N>> split(types::ndarray<T,N> const& a, long nb_split) {
                if(a.flat_size()%nb_split != 0)
                    throw types::ValueError("array split does not result in an equal division");
                return  array_split(a, nb_split);
            }

        template<class T, size_t N, class I>
            typename std::enable_if<types::is_iterable<I>::value, types::list<types::ndarray<T,N>>>::type
            split(types::ndarray<T,N> const& a, I const& split_mask) {
                return array_split(a, split_mask);
            }

        template<class E, class I>
            types::list<types::ndarray<typename E::dtype, E::value>>
            split(E const& a, I const& ) {
                throw std::runtime_error("split only partially implemented");
            }

        PROXY(pythonic::numpy, split);

    }

}

#endif


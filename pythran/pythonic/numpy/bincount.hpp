#ifndef PYTHONIC_NUMPY_BINCOUNT_HPP
#define PYTHONIC_NUMPY_BINCOUNT_HPP

#include "pythonic/numpy/max.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<long,1>
            bincount(types::ndarray<T,N> const & expr, types::none_type weights=__builtin__::None, types::none<long> minlength = __builtin__::None) {
                long length = 0;
                if(minlength) length = (long)minlength;
                length = std::max(length, 1 + max(expr));
                types::ndarray<long, 1> out( types::make_tuple(length), 0L);
                for(auto iter = expr.fbegin(), end = expr.fend(); iter != end; ++iter)
                    ++out[ *iter ];
                return out;
            }

        template<class T, size_t N, class E>
            types::ndarray<decltype(std::declval<long>()*std::declval<typename E::dtype>()),1>
            bincount(types::ndarray<T,N> const & expr, E const& weights, types::none<long> minlength = __builtin__::None) {
                long length = 0;
                if(minlength) length = (long)minlength;
                length = std::max(length, 1 + max(expr));
                types::ndarray<decltype(std::declval<long>()*std::declval<typename E::dtype>()), 1> out( types::make_tuple(length), 0L);
                auto iweight = weights.fbegin();
                for(auto iter = expr.fbegin(), end = expr.fend(); iter != end; ++iter, ++iweight)
                    out[ *iter ] += *iweight;
                return out;
            }

        PROXY(pythonic::numpy, bincount);

    }

}

#endif


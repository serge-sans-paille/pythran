#ifndef PYTHONIC_NUMPY_SUM_HPP
#define PYTHONIC_NUMPY_SUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            typename std::enable_if<
            std::is_scalar< typename types::numpy_expr_to_ndarray<E>::type::dtype >::value,
            typename types::numpy_expr_to_ndarray<E>::type::dtype
                >::type
                sum(E const& expr, types::none_type axis=__builtin__::None) {
                    typedef typename types::numpy_expr_to_ndarray<E>::type::dtype T;
                    long n= expr.size();
#ifdef USE_BOOST_SIMD
                    long i;
                    typedef typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
                    static const std::size_t vN = boost::simd::meta::cardinal_of< vT >::value;
                    const long bound = n/vN*vN;
                    vT vp = boost::simd::splat<vT>(T(0));
#else
                    T vp(0);
#endif
#pragma omp parallel for reduction(+:vp)
#ifdef USE_BOOST_SIMD
                    for(i=0;i< bound; i+= vN) {
                        vp += expr.load(i);
                    }
                    T p = boost::simd::sum(vp);
                    for(;i< n; ++i)
                        p += expr.at(i);
                    return p;
#else
                    for(long i=0 ; i<n; ++i) {
                        vp += expr.at(i);
                    }
                    return vp;
#endif
                }
        /* no fancy parallelization for non-scalar types */
        template<class E>
            typename std::enable_if<
            !std::is_scalar< typename types::numpy_expr_to_ndarray<E>::type::dtype >::value,
            typename types::numpy_expr_to_ndarray<E>::type::dtype
                >::type
                sum(E const& expr, types::none_type axis=__builtin__::None) {
                    typedef typename types::numpy_expr_to_ndarray<E>::type::dtype T;
                    long n= expr.size();
                    T vp(0);
                    for(long i=0 ; i<n; ++i) {
                        vp += expr.at(i);
                    }
                    return vp;
                }

        template<class T>
            T sum( types::ndarray<T,1> const& array, long axis)
            {
                if(axis!=0)
                    throw types::ValueError("axis out of bounds");
                return sum(array);
            }

        template<class T, size_t N>
            typename std::enable_if<N!=1, typename types::ndarray<T,N>::value_type>::type
            sum( types::ndarray<T,N> const& array, long axis)
            {
                if(axis<0 || axis >=long(N))
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape;
                if(axis==0)
                {
                    return std::accumulate(array.begin() + 1, array.end(), *array.begin());
                }
                else
                {
                    types::array<long, N-1> shp;
                    std::copy(shape.begin(), shape.end() - 1, shp.begin());
                    types::ndarray<T,N-1> sumy(shp, __builtin__::None);
                    std::transform(array.begin(), array.end(), sumy.begin(), [=](types::ndarray<T,N-1> const& other) {return sum(other, axis-1);});
                    return sumy;
                }
            }

        PROXY(pythonic::numpy, sum);

    }

}

#endif


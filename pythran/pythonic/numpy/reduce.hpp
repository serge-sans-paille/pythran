#ifndef PYTHONIC_NUMPY_REDUCE_HPP
#define PYTHONIC_NUMPY_REDUCE_HPP

#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/utils/neutral.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/memory/functions/aligned_store.hpp>
#endif

#include <algorithm>

namespace pythonic {

    namespace numpy {

    template<class Op, size_t N, bool vector_form>
      struct _reduce;

    template<class Op, bool vector_form>
      struct _reduce<Op, 1, vector_form> {
        template <class E, class F>
          F operator()(E e, F acc) {
          for (auto const &value : e)
            Op{}(acc, value);
          return acc;
        }
      };
#ifdef USE_BOOST_SIMD
    template<class Op>
      struct _reduce<Op, 1, true> {
        template <class E, class F>
          F operator()(E e, F acc) {
            typedef typename E::dtype T;
            typedef typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
            static const size_t vN = boost::simd::meta::cardinal_of<vT>::value;
            const long n = e.shape()[0];
            const long bound = n / vN * vN;
            long i = 0;
            if(bound > 0) {
              vT vacc = e.load(i);
              for (i = vN; i < bound; i += vN)
                Op{}(vacc, e.load(i));
              alignas(sizeof(vT)) T stored[vN];
              boost::simd::store(vacc, &stored[0]);
              for(size_t j=0; j<vN; ++j)
                Op{}(acc, stored[j]);
            }
            for(;i< n; ++i)
              Op{}(acc, e.fast(i));
            return acc;
        }
      };
#endif

    template<class Op, size_t N, bool vector_form>
      struct _reduce {
        template<class E, class F>
            F operator()(E e, F acc)
            {
              for(auto const & value: e)
                acc = _reduce<Op, N-1, vector_form>{}(value, acc);
              return acc;
            }
      };


        namespace {
          template<class E>
            using reduce_result_type = typename std::conditional<std::is_same<typename E::dtype, bool>::value, long, typename E::dtype>::type;
        }
        template<class Op, class E>
          reduce_result_type<E>
            reduce(E const& expr, types::none_type _ = types::none_type()) {
                bool constexpr is_vectorizable = E::is_vectorizable and not std::is_same<typename E::dtype, bool>::value;
                reduce_result_type<E> p = utils::neutral<Op, typename E::dtype>::value;
                return _reduce<Op, types::numpy_expr_to_ndarray<E>::N, is_vectorizable>{}(expr, p);
            }

        template<class Op, class E>
            auto reduce(E const& array, long axis)
            -> typename std::enable_if<E::value == 1, decltype(reduce<Op>(array))>::type
            {
                if(axis != 0)
                    throw types::ValueError("axis out of bounds");
                return reduce<Op>(array);
            }

        namespace {
          template<class E>
            using reduced_type = types::ndarray<typename E::dtype, E::value - 1>;
        }
        template<class Op, class E>
            typename std::enable_if<E::value != 1, reduced_type<E>>::type
            reduce(E const& array, long axis)
            {
                if(axis<0 || size_t(axis) >= E::value)
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape();
                if(axis==0)
                {
                    types::array<long, E::value - 1> shp;
                    std::copy(shape.begin() + 1, shape.end(), shp.begin());
                    return _reduce<Op, 1, false /* not on scalars*/>{}(array, reduced_type<E>{shp, utils::neutral<Op, typename E::dtype>::value});
                }
                else
                {
                    types::array<long, E::value-1> shp;
                    auto next = std::copy(shape.begin(), shape.begin() + axis, shp.begin());
                    std::copy(shape.begin() + axis + 1, shape.end(), next);
                    reduced_type<E> sumy{shp, __builtin__::None};
                    std::transform(array.begin(), array.end(), sumy.begin(),
                                   [axis](typename E::iterator::value_type other) { return reduce<Op>(other, axis - 1); });
                    return sumy;
                }
            }
    }

}

#endif



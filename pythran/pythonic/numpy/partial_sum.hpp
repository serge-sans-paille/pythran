#ifndef PYTHONIC_NUMPY_PARTIAL_SUM_HPP
#define PYTHONIC_NUMPY_PARTIAL_SUM_HPP

#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/utils/neutral.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {

    template<class Op, size_t N>
      struct _partial_sum;

    template<class Op>
      struct _partial_sum<Op, 1> {
        template <class E, class F, class A>
          A operator()(E e, F& o, A acc) {
            for (auto const &value : e) {
              Op{}(acc, value);
              *o = acc;
              ++o;
            }
            return acc;
          }
      };

    template<class Op, size_t N>
      struct _partial_sum {
        template<class E, class F, class A>
            A operator()(E e, F& o, A acc)
            {
              for(auto const & value: e) {
                acc = _partial_sum<Op, N-1>{}(value, o, acc);
              }
              return acc;
            }
      };


    template<class Op, class E, class dtype=typename E::dtype>
      types::ndarray<typename types::numpy_type<dtype>::type,1>
      partial_sum(E const& expr, dtype d = dtype()) {
        const long count = expr.flat_size();
        types::ndarray<typename types::numpy_type<dtype>::type, 1> the_partial_sum{types::make_tuple(count), __builtin__::None};
        auto const p = utils::neutral<Op, typename E::dtype>::value;
        auto iter = the_partial_sum.begin();
        _partial_sum<Op, types::numpy_expr_to_ndarray<E>::N>{}(expr, iter, p);
        return the_partial_sum;
      }

    template<class Op, class E, class dtype=typename std::remove_reference<E>::type::dtype>
      auto partial_sum(E const& expr, long axis, dtype d = dtype())
      -> typename std::enable_if<E::value == 1, decltype(partial_sum<Op, E, dtype>(expr))>::type
      {
          if(axis !=0)
              throw types::ValueError("axis out of bounds");
          return partial_sum<Op, E, dtype>(expr);
      }

    template<class E, class dtype=typename E::dtype>
      using partial_sum_type = types::ndarray<typename types::numpy_type<dtype>::type, E::value>;

    template<class Op, class E, class dtype=typename E::dtype>
      typename std::enable_if<E::value != 1, partial_sum_type<E, dtype> >::type
      partial_sum(E const& expr, long axis, dtype d = dtype())
      {
        if(axis<0 || size_t(axis) >= E::value)
            throw types::ValueError("axis out of bounds");

        auto shape = expr.shape();
        partial_sum_type<E, dtype> the_partial_sum{shape, __builtin__::None};
        if(axis==0) {
          auto iter = the_partial_sum.begin();
          _partial_sum<Op, 1>{}(expr, iter,
                                types::ndarray<dtype, 1>{types::make_tuple(shape[E::value - 1]), utils::neutral<Op, dtype>::value});
        }
        else {
            std::transform(expr.begin(), expr.end(), the_partial_sum.begin(),
                           [axis,d](typename E::iterator::value_type other) { return partial_sum<Op>(other, axis-1, d); });
        }
        return the_partial_sum;
      }

    }

}

#endif



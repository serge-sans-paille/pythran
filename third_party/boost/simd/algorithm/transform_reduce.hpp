//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_TRANSFORM_REDUCE_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_TRANSFORM_REDUCE_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/function/aligned_load.hpp>
#include <boost/simd/function/load.hpp>
#include <boost/simd/pack.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/simd/meta/cardinal_of.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Applies unary_op to each element in the range [first; last) and reduces the results
    (possibly permuted and aggregated in unspecified manner) along with the initial value init over binary_op.

    @param first  Beginning of the range of elements to transform
    @param last   End of the range of elements to transform
    @param unop   unary operation function object that will be applied.
    @param init   the initial value of the reduction
    @param binop  binary operation function object that will be applied.

    @par Requirement

      - @c first, @c last must be pointer to Vectorizable type.

      - @c unop and binop must be a polymorphic unary function object, i.e callable on generic types,
        at least @c T and  @c boost::simd::pack<T>
      - returns the generalized sum of init and unary_op(*first), unary_op(*(first+1)), . unary_op(*(last-1)) over binary_op,

      where generalized sum GSUM(op, a1, ., aN) is defined as follows:

      if N=1, a1
      if N > 1, op(GSUM(op, b1, ., bK), GSUM(op, bM, ., bN)) where

        - b1, ., bN may be any permutation of a1, ., aN and
        - 1 < K+1 = M <= N

      in other words, the results of unary_op may be grouped and arranged in arbitrary order.
      a pointer to the element past the last element transformed.

    @par Note:

      - unop is not applied to init

      - If the range is empty, init is returned, unmodified

    @par Example:

      The following code uses simd::transform to compute sum of the square of the values stored in a
      @c std::vector.

      @snippet transform_reduce.cpp transform_reduce

    @par possible output:

       @snippet transform_reduce.txt transform_reduce

  **/
  template<typename T, typename Unop, typename Binop>
  T transform_reduce(T const* first, T const* last
                    , Unop unop, T init, Binop binop)
  {
    auto pr = segmented_aligned_range(first,last);

    for( auto const& x : pr.head ) init = binop(init, unop(x));
    auto b = pr.body.begin();
    auto e = pr.body.end();
    if (b != e)
    {
      pack<T> acc(unop(*b++));
      for( ; b != e; b++) acc  = binop(acc , unop(*b));
      for( T     x : acc) init = binop(init, x);
    }
    for( auto const& x : pr.tail ) init = binop(init, unop(x));

    return init;
  }

  /*!
    @ingroup group-algo

    Applies transform binary operator  to each element in the range [first1; last1) and [first2, )
    and reduces the results (possibly permuted and aggregated in unspecified manner)
    along with the initial value init over generalized sum gsum binary operator.

    @param first1      Beginning of the first range of elements to transform
    @param last1       End of the first range of elements to transform
    @param first2      Beginning of the second range of elements to transform
    @param transform   binary operation function object that will be applied.
    @param init        the initial value of the reduction
    @param gsum        binary operation function object that will be applied.

    @par Requirement

      - T, U and V must be types which can be used within
      - @c transform and gsum must be a polymorphic unary function object, i.e callable on generic types,
        at least
          - transform must be able to be called on couples @c (T, U) and  @c (boost::simd::pack<T>, boost::simd::pack<U>)
          to produce respectively @c V and boost::simd::pack<V> types
          - gsum must be able to be called on V and boost::simd::pack<V> types to produce the same output type.
      - returns the generalized sum of init and transform(*first1, *first2), transform(*(first+1), *(first2+1)), .,
        transform(*(last1-1), *(first2-(last1-first1)-1)) over binary_op,

      where generalized sum GSUM(op, a1, ., aN) is defined as follows:

      if N=1, a1
      if N > 1, op(GSUM(op, b1, ., bK), GSUM(op, bM, ., bN)) where

        - b1, ., bN may be any permutation of a1, ., aN and
        - 1 < K+1 = M <= N

      in other words, the results of transform may be grouped and arranged in arbitrary order.
      a pointer to the element past the last element transformed.

    @par Note:

      - If the range is empty, init is returned, unmodified

    @par Example:

      The following code uses simd::transform to compute the dot-product of the values stored in two
      @c std::vector.

      @snippet transform_reduce2.cpp transform_reduce2

    @par possible output:

       @snippet transform_reduce2.txt transform_reduce2

  **/
  template<typename T, typename U, typename V, typename Binop1, typename Binop2>
  V transform_reduce(T const* first1, T const* last1, U const* first2
                    , Binop1 transform, V init, Binop2 gsum)
  {
    using vU = pack<U>;
    using vV = pack<V>;
    using vT = pack<T>;
    static_assert ( bs::cardinal_of_t<vT>::value == bs::cardinal_of_t<vU>::value
                  , "SIMD cardinal mismatch between T and U"
                  );
    static_assert (  bs::cardinal_of_t<vT>::value == bs::cardinal_of_t<vV>::value
                  , "SIMD cardinal mismatch between T and V"
                  );
    auto pr = segmented_aligned_range(first1,last1);

    for( auto const& x : pr.head ){
      init = gsum(init, transform(x, *first2++));
    }

    // main SIMD part
    auto b = pr.body.begin();
    auto e = pr.body.end();
    if (b !=  e)
    {
      if( boost::simd::detail::is_aligned(first2 , vU::alignment) ) // first2 is aligned
      {
        vV acc(transform(vT(*b++), aligned_load<vU>(first2)));
        first2+= vU::static_size;
        for( ; b != e; b++, first2+= vU::static_size){
          acc  = gsum(acc, transform(vT(*b), aligned_load<vU>(first2)));
        }
        for( V x : acc) init = gsum(init, x);
      }
      else
      {
        vV acc(transform(vT(*b++), load<vU>(first2)));
        first2+= vU::static_size;
        for( ; b != e; b++, first2+= vU::static_size){
          acc  = gsum(acc, transform(vT(*b), load<vU>(first2)));
        }
        for( V x : acc) init = gsum(init, x);
      }
    }

    for( auto const& x : pr.tail )
      init = gsum(init, transform(x, *first2++));

    return init;
  }

} }

#endif

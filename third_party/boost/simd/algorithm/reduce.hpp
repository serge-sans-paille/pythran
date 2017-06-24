//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_REDUCE_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_REDUCE_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/function/sum.hpp>
#include <boost/simd/pack.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Computes the sum over elements in the given Contiguous Range @range{first,last} and
    the initial value @c init.

    \notebox{The summation order can be different from the order of a sequential summation
            , thus leading to different results.
            }

    @par Example:
    @snippet reduce.simple.cpp reduce-simple
    Possible output:
    @code
    SIMD reduce     : 45
    STD  accumulate : 45
    @endcode

    @param first  Beginning of the range of elements to sum
    @param last   End of the range of elements to sum
    @param init   Initial value of the sum

    @return The sum of the given value and elements in the given range.
  **/
  template<typename T> T reduce(T const* first, T const* last, T init)
  {
    pack<T> acc(0);
    auto pr = segmented_aligned_range(first,last);

    for( T        e : pr.head ) init += e;
    for( pack<T>  e : pr.body ) acc  += e;
    for( T        e : pr.tail ) init += e;

    return init + sum(acc);
  }

  /*!
    @ingroup group-algo

     Reduces the range [first; last), possibly permuted and aggregated in unspecified manner,
     along with the initial value init over binary_op.


    \notebox{The summation order can be different from the order of a sequential summation
            , thus leading to different results.
            }

    @par Example:
    @snippet reduce.phases.cpp reduce-phases
    Possible output:
    @code
    SIMD reduce     : 285
    @endcode

    @param first    Beginning of the range of elements to sum
    @param last     End of the range of elements to sum
    @param init     Initial value of the reduction
    @param binop    Binary function object that will be applied in unspecified order to the
                    result of dereferencing the input pointers, the results of other @c binop
                    and @ init.

    @return The generalized sum of the given init value and elements in the given range over @ binop.
  **/
  template<typename T, typename F>
  T reduce( T const* first, T const* last, T init, F binop )
  {
    auto pr = segmented_aligned_range(first,last);
    for( T v : pr.head ) init = binop(init, v);
    auto b = pr.body.begin();
    auto e = pr.body.end();
    if (b !=  e){
      pack<T> acc(*b++);
      for( ; b != e; b++) acc  = binop(acc, pack<T>(*b));
      for( T     x : acc) init = binop(init, x);
    }
    for( T v : pr.tail ) init = binop(init, v);
    return init;
  }

} }

#endif

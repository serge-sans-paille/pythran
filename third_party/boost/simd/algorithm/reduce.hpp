//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_REDUCE_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_REDUCE_HPP_INCLUDED

#include <boost/simd/range/segmented_input_range.hpp>
#include <boost/simd/function/sum.hpp>
#include <boost/simd/pack.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-std

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
    auto pr = segmented_input_range(first,last);

    for( auto const& e : std::get<0>(pr) ) init += e;
    for( auto const& e : std::get<1>(pr) ) acc  += e;
    for( auto const& e : std::get<2>(pr) ) init += e;

    return init + sum(acc);
  }

  /*!
    @ingroup group-std

    Computes the generalized sum of the elements in the given Contiguous Range @range{first,last}
    over the binary functions @c binop and @c reduce, using @c init as the initial value.

    While @c binop is applied over the result of dereferencing the input pointers, @c reduce is to
    be used in the final reduction of the SIMD part of the generalized sum.

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
    @param neutral  Value containing the neutral element of @c binop
    @param reduce   Binary function object that will be applied to complete the reduction

    @return The generalized sum of the given value and elements in the given range over @ binop.
  **/
  template<typename T, typename U, typename F, typename N, typename G>
  U reduce( T const* first, T const* last, U init, F binop, N neutral, G reduce )
  {
    pack<U> acc(neutral);
    auto pr = segmented_input_range(first,last);

    for( auto const& e : std::get<0>(pr) ) init = binop(init,e);
    for( auto const& e : std::get<1>(pr) ) acc  = binop(acc,e);
    for( auto const& e : std::get<2>(pr) ) init = binop(init,e);
    for( U           e : acc)              init = reduce(init,e);

    return init;
  }

  /*!
    @ingroup group-std

    Computes the generalized sum of the elements in the given Contiguous Range @range{first,last}
    over the binary function @c binop, using @c init as the initial value.

    @c binop is applied over the result of dereferencing the input pointers and in the final
    reduction of the SIMD part of the generalized sum.

    \notebox{The summation order can be different from the order of a sequential summation
            , thus leading to different results.
            }

    @par Example:
    @snippet reduce.phase.cpp reduce-phase
    Possible output:
    @code
    SIMD reduce     : 362880
    @endcode

    @param first    Beginning of the range of elements to sum
    @param last     End of the range of elements to sum
    @param init     Initial value of the reduction
    @param binop    Binary function object that will be applied in unspecified order to the
                    result of dereferencing the input pointers, the results of other @c binop
                    and @c init.
    @param neutral  Value containing the neutral element of @c binop

    @return The sum of the given value and elements in the given range.
  **/
  template<typename T, typename U, typename F, typename N>
  U reduce(T const* first, T const* last, U init, F binop, N neutral)
  {
    return reduce(first,last,init,binop,neutral,binop);
  }
} }

#endif

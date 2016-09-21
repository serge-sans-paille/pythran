//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CORRECT_FMA_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CORRECT_FMA_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-arithmetic
    Function object function implementing correct_fma

    Computes the "correct" fused multiply/add of its parameter: this is perhaps not that you need
    if speed is needed more than accuracy (this remark is hardware dependent).

    @par semantic:
    For any given value @c x, @c y, @c z of type @c T:

    @code
    T r = correct_fma(x, y, z);
    @endcode

    is similar to:

    @code
    T r = x*y+z;
    @endcode

    but is only rounded once and with no intermediate overflow.

    @par Notes:
    - For integers x*y+z is always performed in 2-complement wraping.

    - For floating points numbers, the correct fused multiply add is computed,
    meaning the computation of x*y+z with only one rounding operation.
    This operation may be very expensive on architectures where this
    functionality is not hardware provided.

    - @c correct_fma is in fact a transitory function which ensures
    strict @ref fma capabilities, i.e. only one rounding operation and no undue
    overflow in intermediate computations.

    - If you are using this function on an architecture without @ref fma
    and are sure that overflow is not a problem
    you may define BOOST_SIMD_DONT_CARE_CORRECT_FMA_OVERFLOW for better
    performance.

    - @c correct_fma is never used internally in boost.simd.

    @par Decorators
      std_ for floating entries calls std::fma but does not guarantee performances...

    @see  fma, fms fnma, fnms
**/
     Value correct_fma(Value const& v0, Value const& v1, Value const& v2);
} }
#endif

#include <boost/simd/function/scalar/correct_fma.hpp>
#include <boost/simd/function/simd/correct_fma.hpp>

#endif

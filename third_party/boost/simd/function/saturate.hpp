//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SATURATE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing saturate capabilities

    Returns the saturated value of the first input in the template parameter type,
    but in the same type as the input.

    @par Semantic:


    For every parameter of type @c T and type @c Target

    @code
    T r = saturate<Target>(x)
    @endcode

    is similar to:

    @code
    if (x >  Inf<Target>()) r =  T(Inf<Target>());
    else if  (x <  Minf<Target>()) r =  T(Minf<Target>());
    else r = x;
    @endcode

    @see Minf, Inf, Valmax, Valmin

    @par Note

    Let us recall that @ref Valmin and @ref Minf (resp. @ref Valmax and @ref Inf)
    are identical if Target is  an integer type.

  **/
  Value saturate(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/saturate.hpp>
#include <boost/simd/function/simd/saturate.hpp>

#endif

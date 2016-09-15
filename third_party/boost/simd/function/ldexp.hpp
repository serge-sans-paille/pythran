//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LDEXP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing ldexp capabilities

    The function multiply a floating entry \f$x\f$
    by \f$2^{n}\f$


    @par Semantic:

    @code
    auto r = ldexp(x,n);
    @endcode

    is similar to:

    @code
    auto r = x*pow(2, n);
    @endcode

    The @ref cardinal_of value of the types of @c x and @c n must be identical

  **/
  Value ldexp(Value const & x, Value const& n);
} }
#endif

#include <boost/simd/function/scalar/ldexp.hpp>
#include <boost/simd/function/simd/ldexp.hpp>

#endif

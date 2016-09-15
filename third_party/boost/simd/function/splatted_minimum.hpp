//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SPLATTED_MINIMUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SPLATTED_MINIMUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-swar
    Function object implementing splatted_minimum capabilities

    Splatted minimum

    Computes the splatted minimum of the element of its argument.

    @par Semantic

    Depending on the type of its arguments, splatted_maximum exhibits different
    semantics. For any type @c T and value @c x of type @c T:

    @code
    T r = splatted_maximum(x);
    @endcode

    is similar to:

    @code
    for(int i=0;i<T::static_size;++i) x[i] = minimum(x);
    @endcode

  **/
  Value splatted_minimum(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/splatted_minimum.hpp>
#include <boost/simd/function/simd/splatted_minimum.hpp>

#endif

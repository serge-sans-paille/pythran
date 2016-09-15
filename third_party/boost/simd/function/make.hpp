//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MAKE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MAKE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-swar

    Build a value of type @c T from a list of scalar values of types @c Args

    Splatted product

    Computes the splatted product of the of its argument.

    @par Semantic

    For any type @c T and value @c x of type @c T:

    @code
    T r = splatted_prod(x);
    @endcode

    is similar to:

    @code
    T product = 1;
    for(int i=0;i<T::static_size;++i) product *= x[i];
    for(int i=0;i<T::static_size;++i) r[i] = product;
    @endcode

  **/
  template<typename T, typename.. Args> auto make(Args&&... args) {}
} }
#endif

#include <boost/simd/function/scalar/make.hpp>
#include <boost/simd/function/simd/make.hpp>

#endif

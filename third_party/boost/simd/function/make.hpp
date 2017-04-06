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


    @par Header <boost/simd/function/make.hpp>

    @par Scalar Semantic
    For any type @c T and value @c x of type @c T:
    @code
    auto r = make<T>(x);
    @endcode
    is equivalent to:
    @code
    T r{x};
    @endcode

    @par SIMD Semantic
    For any type @c T , any integral constant @c N and @c N values @c xs of type @c T, the following
    code:
    @code
    auto r = make<boost::simd::pack<T,N>>(x0,...,xn);
    @endcode
    is equivalent to:
    @code
    boost::simd::pack<T,N> r{x0,...,xn};
    @endcode

    @param  args  List of value to build the result from.
    @tparam T Type of the expected output.
    @return A value of type @c T built from each args.
  **/
  template<typename T, typename.. Args> T make(Args const&... args);

  /*!
    @overload
  **/
  template<typename Target, typename.. Value> T make(as_<Target> const& t, Value const&... args);
} }
#endif

#include <boost/simd/function/scalar/make.hpp>
#include <boost/simd/function/simd/make.hpp>

#endif

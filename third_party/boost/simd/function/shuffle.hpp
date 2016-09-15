//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-swar
    Function object implementing shuffle capabilities

    SIMD register shuffling

    Shuffle the elements of two SIMD registers following a compile-time
    permutation pattern passed as a @metafunction.

    @par Semantic:

    Let @c T be a SIMD register type of cardinal @c N, @c Perm be a
    binary @metafunction. For any SIMD register @c x and  @c y of type @c T,
    the following code:

    @code
    T r = shuffle<Perm>(x,y);
    @endcode

    is equivalent to

    @code
    T r = shuffle< mpl::apply<Perm, int_<0>, int_<N> >::type::value
                 , ...
                 , mpl::apply<Perm, int_<C-1>, int_<N> >::type::value
                 >(x,y);
    @endcode

    @usage{shuffle_perm1.cpp}

    @tparam Perm Permutation pattern @metafunction

  **/
  template<std::ptrdiff_t... Ps, typename T>  T shuffle(T const& a);
  template<std::ptrdiff_t... Ps, typename T>  T shuffle(T const& a,T const& b);

  template<typename Permutation, typename T>  T shuffle(T const& a);
  template<typename Permutation, typename T>  T shuffle(T const& a,T const& b);
} }
#endif

#include <boost/simd/function/scalar/shuffle.hpp>
#include <boost/simd/function/simd/shuffle.hpp>

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_IS_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_META_IS_POWER_OF_2_HPP_INCLUDED

#include <cstddef>
#include <boost/mpl/bool.hpp>

namespace boost { namespace simd {  namespace meta
{
  /*!
    @brief Checks if an integral value is a power of two.

    is_power_of_2_c checks if any given integral @c N is a non-zero power of two.

    @par Semantic:
    For any given integral value @c N:

    @code
    typedef is_power_of_2_c<N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef mpl::bool<(!(N & (N - 1)) && N)> r;
    @endcode

    @usage{meta/is_power_of_2_c.cpp}

    @tparam N Integral value to check
  **/
  template<std::size_t N> struct  is_power_of_2_c
#if !defined(DOXYGEN_ONLY)
        : boost::mpl::bool_<(!(N & (N - 1)) && N)>
#endif
  {};

  /*!
    @brief Checks if an @mplint is a power of two.

    is_power_of_2_c is a Boolean @metafunction that checks if any given
    @mplint @c N is a non-zero power of two.

    @par Semantic:
    For any given @mplint @c N:

    @code
    typedef is_power_of_2<N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef is_power_of_2_c<N::value>::type r;
    @endcode

    @usage{meta/is_power_of_2.cpp}

    @tparam N @mplint to check
  **/
  template<class N> struct  is_power_of_2
#if !defined(DOXYGEN_ONLY)
        : boost::mpl::bool_<(!(N::value & (N::value - 1)) && N::value)>
#endif
  {};
} } }

#endif

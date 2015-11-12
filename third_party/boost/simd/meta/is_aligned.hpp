//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_IS_ALIGNED_HPP_INCLUDED
#define BOOST_SIMD_META_IS_ALIGNED_HPP_INCLUDED

#include <boost/simd/meta/is_power_of_2.hpp>
#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <cstddef>

namespace boost { namespace simd {  namespace meta
{
  /*!
    @brief Check alignment of arbitrary integral value

    Checks if any given integral value @c V is aligned on any
    given power of two boundary @c N.

    @par Semantic:
    For any given integral value @c N and @c V:

    @code
    typedef is_aligned_c<V,N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef mpl::bool<!(V & (N-1) )>::type r;
    @endcode

    If @c N is not a power of two, a BOOST_SIMD_INVALID_ALIGNMENT_VALUE static
    assertion is triggered.

    @usage{meta/is_aligned_c.cpp}

    @tparam V Integral value to check
    @tparam N Alignment to check for. By default, @c N is equal to current
            architecture preferred alignment.
  **/
  template< std::size_t V
          , std::size_t N = BOOST_SIMD_CONFIG_ALIGNMENT
          >
  struct  is_aligned_c
#if !defined(DOXYGEN_ONLY)
        : boost::mpl::bool_<!(V & (N-1) )>
#endif
  {
#if !defined(DOXYGEN_ONLY)
    //==========================================================================
    //               ****BOOST_SIMD_INVALID_ALIGNMENT_VALUE****
    // If this static assert triggers, a call to is_aligned_c has been issued
    // with a non-power of 2 boundary argument.
    //               ****BOOST_SIMD_INVALID_ALIGNMENT_VALUE****
    //==========================================================================
    BOOST_MPL_ASSERT_MSG
    ( (boost::simd::meta::is_power_of_2_c<N>::value)
    , BOOST_SIMD_INVALID_ALIGNMENT_VALUE
    , (boost::mpl::int_<N>)
    );
#endif
  };

  /*!
    @brief Check alignment of arbitrary @mplint

    Checks if any given @mplint @c V is aligned on any given power of two
    boundary @c N.

    @par Semantic:
    For any given @mplint @c N and @c V:

    @code
    typedef is_aligned<V,N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef is_aligned_c<V::value,N::value>::type r;
    @endcode

    If @c N is not a power of two, a BOOST_SIMD_INVALID_ALIGNMENT_VALUE static
    assertion is triggered.

    @par Models:

    @metafunction

    @usage{meta/is_aligned.cpp}

    @tparam V @mplint to check
    @tparam N Alignment to check for. By default, @c N is equal to current
            architecture preferred alignment.
  **/
  template< typename V
          , typename N = boost::mpl::size_t<BOOST_SIMD_CONFIG_ALIGNMENT>
          >
  struct  is_aligned
#if !defined(DOXYGEN_ONLY)
        : is_aligned_c<V::value,N::value>
#endif
  {};
} } }

#endif

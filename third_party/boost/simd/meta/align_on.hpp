//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_ALIGN_ON_HPP_INCLUDED
#define BOOST_SIMD_META_ALIGN_ON_HPP_INCLUDED

#include <boost/simd/meta/is_power_of_2.hpp>
#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/assert.hpp>
#include <cstddef>

namespace boost { namespace simd {  namespace meta
{
  /*!
    @brief Align integral value on arbitrary boundary

    Statically align an integral value on an arbitrary alignment boundary.

    @par Semantic

    For any integral value @c Value and any power of 2 @c Align :

    @code
    typedef align_on_c<Value,Align>::type r;
    @endcode

    is equivalent to

    @code
    typedef integral_constant<std::size_t,N>::type r;
    @endcode

    where @c N verifies :

    @code
    N >= Value && N % Align = 0
    @endcode

    If @c Align is not a power of two, a @c BOOST_SIMD_INVALID_ALIGNMENT_VALUE
    static assertion is triggered.

    @usage{meta/align_on_c.cpp}

    @tparam Value Value to align.
    @tparam Align Integral power of two alignment boundary. By default,
            @c Align is equal to current SIMD extension alignment boundary.
  **/
  template< std::size_t Value
          , std::size_t Align = BOOST_SIMD_CONFIG_ALIGNMENT
          >
  struct  align_on_c
    #if !defined(DOXYGEN_ONLY)
        : boost::mpl::integral_c<std::size_t, (Value+Align-1) & ~(Align-1) >
    #endif
  {
    #if !defined(DOXYGEN_ONLY)
    //==========================================================================
    //               ****BOOST_SIMD_INVALID_ALIGNMENT_VALUE****
    //       If you trigger this assert, you tried to align a value on
    //   a boundary which is not a power of two. Fix your code accordingly.
    //               ****BOOST_SIMD_INVALID_ALIGNMENT_VALUE****
    //==========================================================================
    /// INTERNAL ONLY
    BOOST_MPL_ASSERT_MSG( (meta::is_power_of_2_c<Align>::value)
                        , BOOST_SIMD_INVALID_ALIGNMENT_VALUE
                        , (boost::mpl::integral_c<std::size_t,Align>)
                        );
    #endif
  };

  /*!
    @brief Align @mplint on arbitrary boundary

    Statically align @mplint value on arbitrary alignment boundary.

    @par Semantic

    For any @mplint @c Value and any power of 2 @c Align :

    @code
    typedef align_on<Value,Align>::type r;
    @endcode

    is equivalent to

    @code
    typedef integral_constant<Value::value_type,N>::type r;
    @endcode

    where @c N verifies :

    @code
    N >= Value::value && N % Align::value = 0
    @endcode

    If @c Align is not a power of two, a  @c BOOST_SIMD_INVALID_ALIGNMENT_VALUE
    static assertion is triggered.

    @par Models:

    @metafunction

    @usage{meta/align_on.cpp}

    @tparam Value Value to align
    @tparam Align @mplint power of two alignment boundary. By default,
            @c Align is equal to current SIMD extension alignment boundary.
  **/
  template< typename Value
          , typename Align = boost::mpl::integral_c<std::size_t,BOOST_SIMD_CONFIG_ALIGNMENT>
          >
  struct align_on
#if !defined(DOXYGEN_ONLY)
       :  boost::mpl::integral_c
          < typename Value::value_type
          , typename Value::value_type(align_on_c < std::size_t(Value::value)
                                                  , std::size_t(Align::value)
                                                  >::value
                                      )
          >
#endif
  {};
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_PREV_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_META_PREV_POWER_OF_2_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements prev_power_of_2 and prev_power_of_2_c
**/

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/size_t.hpp>
#include <cstddef>

namespace boost { namespace simd {  namespace details
{
  // Adaptation of :
  // http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
  template<std::size_t N> struct prev_power_of_2_impl
  {
    BOOST_STATIC_CONSTANT(std::size_t, x0    = N               );
    BOOST_STATIC_CONSTANT(std::size_t, x1    = x0 | (x0 >>  1) );
    BOOST_STATIC_CONSTANT(std::size_t, x2    = x1 | (x1 >>  2) );
    BOOST_STATIC_CONSTANT(std::size_t, x3    = x2 | (x2 >>  4) );
    BOOST_STATIC_CONSTANT(std::size_t, x4    = x3 | (x3 >>  8) );
    BOOST_STATIC_CONSTANT(std::size_t, x5    = x4 | (x4 >> 16) );
    BOOST_STATIC_CONSTANT(std::size_t, value = (x5 >> 1) + 1   );
  };

  // Requried for MSVC
  template<> struct prev_power_of_2_impl<0>
  {
    BOOST_STATIC_CONSTANT(std::size_t, value = 0 );
  };
} } }

namespace boost { namespace simd {  namespace meta
{
  /*!
    @brief Evaluates previous power of two

    Computes the power of two lesser or equal to any given integral value @c N.

    @par Semantic:
    For any given integral value @c N:

    @code
    typedef prev_power_of_2_c<N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef mpl::size_t<M> r;
    @endcode

    Where @c M is lesser or equal to N and so that it exists a given @c P so
    that @c M is equal to two at the power of @c P.

    @usage{meta/prev_power_of_2_c.cpp}

    @tparam N Integral constant to downgrade
  **/
  template<std::size_t N> struct  prev_power_of_2_c
#if !defined(DOXYGEN_ONLY)
        : boost::mpl::size_t<details::prev_power_of_2_impl<N>::value>
#endif
  {};

  /*!
    @brief Evaluates previous power of two

    Computes the power of two lesser or equal to any given @mplint @c N.

    @par Semantic:
    For any given @mplint @c N:

    @code
    typedef prev_power_of_2<N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef prev_power_of_2<N::value>::type r;
    @endcode

    @par Models:

    @metafunction

    @usage{meta/prev_power_of_2.cpp}

    @tparam N @mplint to downgrade
  **/
  template<typename N> struct  prev_power_of_2
#if !defined(DOXYGEN_ONLY)
        : boost::mpl::integral_c< typename N::value_type
                                , details::prev_power_of_2_impl<N::value>::value
                                >
#endif
  {};
} } }

#endif

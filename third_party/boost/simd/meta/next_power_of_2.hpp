//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_NEXT_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_META_NEXT_POWER_OF_2_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements next_power_of_2 and next_power_of_2_c
**/

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/integral_c.hpp>

namespace boost { namespace simd {  namespace details
{
  // Implementation courtesy from :
  // http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
  template<std::size_t N> struct next_power_of_2_impl
  {
    BOOST_STATIC_CONSTANT(std::size_t, x0    = N-1             );
    BOOST_STATIC_CONSTANT(std::size_t, x1    = x0 | (x0 >>  1) );
    BOOST_STATIC_CONSTANT(std::size_t, x2    = x1 | (x1 >>  2) );
    BOOST_STATIC_CONSTANT(std::size_t, x3    = x2 | (x2 >>  4) );
    BOOST_STATIC_CONSTANT(std::size_t, x4    = x3 | (x3 >>  8) );
    BOOST_STATIC_CONSTANT(std::size_t, x5    = x4 | (x4 >> 16) );
    BOOST_STATIC_CONSTANT(std::size_t, value = x5 + 1          );
  };

  // Required for MSVC
  template<> struct next_power_of_2_impl<0>
  {
    BOOST_STATIC_CONSTANT(std::size_t, value = 0 );
  };
} } }

namespace boost { namespace simd {  namespace meta
{
  /*!
    @brief Evaluates next power of 2

    Computes the power of two greater or equal to any given integral value @c N.

    @par Semantic:
    For any given integral value @c N:

    @code
    typedef next_power_of_2_c<N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef mpl::size_t<M> r;
    @endcode

    Where @c M is greater or equal to N and so that it exists a given @c P so
    that @c M is equal to 2 at the power of @c P.

    @usage{meta/next_power_of_2_c.cpp}

    @tparam N Integral value to upgrade
  **/
  template<std::size_t N> struct  next_power_of_2_c
#if !defined(DOXYGEN_ONLY)
        : boost::mpl::size_t<details::next_power_of_2_impl<N>::value>
#endif
  {};

  /*!
    @brief Evaluates next power of 2

    Computes the power of two greater or equal to any given @mplint @c N.

    @par Semantic:
    For any given @mplint @c N:

    @code
    typedef next_power_of_2<N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef boost::mpl::integral_c< N::value_type
                                  , next_power_of_2_c<N::value>::value
                                  > r;
    @endcode

    @par Models:

    @metafunction

    @usage{meta/next_power_of_2.cpp}

    @tparam N @mplint to downgrade
  **/
  template<class N> struct  next_power_of_2
#if !defined(DOXYGEN_ONLY)
        : boost::mpl::integral_c< typename N::value_type
                                , details::next_power_of_2_impl<N::value>::value
                                >
#endif
  {};
} } }

#endif

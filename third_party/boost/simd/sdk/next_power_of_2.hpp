//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_NEXT_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_SDK_NEXT_POWER_OF_2_HPP_INCLUDED

namespace boost { namespace simd
{

/*!
    @brief Evaluates next power of 2

    Computes the power of two greater or equal to any given integral value @c n.

    @par Semantic:
    For any given integral value @c n:

    @code
    std::size_t r = next_power_of_2(n);
    @endcode

    where @c r verifies:

    @code
    is_power_of_2(r) == true && r >= n
    @endcode

    @param n Integral value.

    @return An unsigned integral value.
  **/
  inline std::size_t next_power_of_2(std::size_t n)
    {
      std::size_t x0    = n-1;
      std::size_t x1    = x0 | (x0 >>  1);
      std::size_t x2    = x1 | (x1 >>  2);
      std::size_t x3    = x2 | (x2 >>  4);
      std::size_t x4    = x3 | (x3 >>  8);
      std::size_t x5    = x4 | (x4 >> 16);
      return x5 + 1;
    }


} }

#endif

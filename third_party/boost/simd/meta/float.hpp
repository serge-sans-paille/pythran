//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_FLOAT_HPP_INCLUDED
#define BOOST_SIMD_META_FLOAT_HPP_INCLUDED

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/meta/real_c.hpp>

namespace boost { namespace simd { namespace meta
{
 template<boost::simd::uint32_t Value>
 struct single_ : real_c<boost::simd::uint32_t,Value> {};
} } }

#endif

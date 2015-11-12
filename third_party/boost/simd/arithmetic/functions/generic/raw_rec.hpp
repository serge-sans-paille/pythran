//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_RAW_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_RAW_REC_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/raw_rec.hpp>
#include <boost/simd/include/functions/simd/rec.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::raw_rec_, tag::cpu_
                                    , (A0)
                                    , (generic_< arithmetic_<A0> >)
                                    )
  {
    BOOST_DISPATCH_RETURNS(1,(A0 const& a0), boost::simd::rec(a0));
  };
} } }

#endif

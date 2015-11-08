//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SCALAR_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SCALAR_SPLIT_HPP_INCLUDED

#include <boost/simd/swar/functions/split.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_, tag::cpu_
                                    , (A0)
                                    , (scalar_< unspecified_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(a0);
    }
  };
} } }

#endif

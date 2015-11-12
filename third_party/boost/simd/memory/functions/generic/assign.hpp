//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_GENERIC_ASSIGN_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_GENERIC_ASSIGN_HPP_INCLUDED

#include <boost/simd/memory/functions/assign.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::assign_, tag::cpu_
                                    , (A0)
                                    , (generic_<unspecified_<A0> >)
                                      (generic_<unspecified_<A0> >)
                                    )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, const A0& a1) const
    {
      return a0 = a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::assign_, tag::cpu_
                                    , (A0)(A1)
                                    , (proxy_<A0>)
                                      (unspecified_<A1>)
                                    )
  {
    typedef A1& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, const A1& a1) const
    {
      a0 = a1;
      return a1;
    }
  };
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SCALAR_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SCALAR_BROADCAST_HPP_INCLUDED

#include <boost/simd/swar/functions/broadcast.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::broadcast_, tag::cpu_
                                   , (A0)(A1)
                                   , (scalar_< unspecified_<A0> >)
                                     (mpl_integral_< scalar_< integer_<A1> > >)
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&) const
    {
      return a0;
    }
  };
} } }

#endif

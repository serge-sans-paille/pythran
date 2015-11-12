//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SCALAR_IF_ELSE_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SCALAR_IF_ELSE_ALLBITS_HPP_INCLUDED
#include <boost/simd/boolean/functions/if_else_allbits.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/include/functions/scalar/is_nez.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_else_allbits_, tag::cpu_, (A0)(A1)
                                    , (scalar_< logical_<A0> >)
                                      (scalar_< fundamental_<A1> >)
                                    )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return a0 ? a1 : Allbits<A1>();
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_else_allbits_, tag::cpu_, (A0)(A1)
                                    , (scalar_< fundamental_<A0> >)
                                      (scalar_< fundamental_<A1> >)
                                    )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return is_nez(a0) ? a1 : Allbits<A1>();
    }
  };


} } }

#endif

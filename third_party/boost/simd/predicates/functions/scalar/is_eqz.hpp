//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_SCALAR_IS_EQZ_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_SCALAR_IS_EQZ_HPP_INCLUDED
#include <boost/simd/predicates/functions/is_eqz.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/include/functions/scalar/logical_not.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_eqz_, tag::cpu_
                            , (A0)
                            , (scalar_< fundamental_<A0> >)
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return result_type(!a0); }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_eqz_, tag::cpu_
                            , (A0)
                            , (scalar_< logical_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return logical_not(a0); }
  };
} } }


#endif

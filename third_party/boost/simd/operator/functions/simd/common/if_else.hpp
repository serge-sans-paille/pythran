//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_IF_ELSE_HPP_INCLUDED
#include <boost/simd/operator/functions/if_else.hpp>
#include <boost/simd/include/functions/simd/bitwise_select.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/logical_andnot.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/is_bitwise_logical.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_else_, tag::cpu_, (A0)(A1)(X)
                                    , ((simd_< logical_<A0>, X >))
                                      ((simd_< arithmetic_<A1>, X >))
                                      ((simd_< arithmetic_<A1>, X >))
                                    )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return bitwise_select(genmask(a0), a1, a2);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_else_, tag::cpu_, (A0)(A1)(X)
                                    , ((simd_< arithmetic_<A0>, X >))
                                      ((simd_< arithmetic_<A1>, X >))
                                      ((simd_< arithmetic_<A1>, X >))
                                    )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return if_else( is_nez(a0), a1, a2 );
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_else_, tag::cpu_, (A0)(A1)(X)
                                    , ((simd_< arithmetic_<A0>, X >))
                                      ((simd_< logical_<A1>, X >))
                                      ((simd_< logical_<A1>, X >))
                                    )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return if_else( is_nez(a0), a1, a2 );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_else_, tag::cpu_, (A0)(A1)(X)
                                    , ((simd_< logical_<A0>, X >))
                                      ((simd_< logical_<A1>, X >))
                                      ((simd_< logical_<A1>, X >))
                                    )
  {
    typedef A1 result_type;

    template<class A0_>
    typename enable_if< meta::is_bitwise_logical<A0_>, result_type>::type
    BOOST_FORCEINLINE operator()(const A0_& a0, const A1& a1, const A1&a2) const
    {
      typedef typename meta::as_arithmetic<A1>::type atype;
      return bitwise_cast<result_type>(if_else(a0,bitwise_cast<atype>(a1),bitwise_cast<atype>(a2)));
    }

    template<class A0_>
    typename disable_if< meta::is_bitwise_logical<A0_>, result_type>::type
    BOOST_FORCEINLINE operator()(const A0_& a0, const A1& a1, const A1&a2) const
    {
      return logical_or(logical_and(a1,a0),logical_andnot(a2,a0));
    }
  };

} } }

#endif

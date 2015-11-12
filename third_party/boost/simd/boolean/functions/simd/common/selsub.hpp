//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_SELSUB_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_SELSUB_HPP_INCLUDED

#include <boost/simd/boolean/functions/selsub.hpp>
#include <boost/simd/include/functions/simd/if_else_zero.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/unary_minus.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::selsub_, tag::cpu_, (A0)(A1)(X)
                                       , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                               , boost::simd::meta::cardinal_of<A1>
                                                               >
                                         )
                                       , ((simd_<unspecified_<A0>,X>))
                                         ((simd_<unspecified_<A1>,X>))
                                         ((simd_<unspecified_<A1>,X>))
                                       )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A1 const& a2) const
    {
     return a1 - if_else_zero(a0, a2);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::selsub_, tag::cpu_, (A0)(A1)(X)
                                       , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                               , boost::simd::meta::cardinal_of<A1>
                                                               >
                                         )
                                       , ((simd_<unspecified_<A0>,X>))
                                         ((simd_<floating_<A1>,X>))
                                         ((simd_<floating_<A1>,X>))
                                       )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A1 const& a2) const
    {
      // this is a workaround for a gcc (at least 4.6) over-optimization in case or a1 and a2 are
      // equal (constant?) and invalid (inf -inf or nan) in which case the general impl sometimes
      // return 0 in place of nan in float cases.
     return a1 + if_else_zero(a0, -a2);
    }
  };
} } }

#endif

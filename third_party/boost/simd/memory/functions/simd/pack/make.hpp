//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_MAKE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_MAKE_HPP_INCLUDED

#include <boost/simd/include/functions/make.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>

// make forces evaluation due to arity limitations
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::make_ , tag::cpu_
                            , (Target)
                            , ((target_< ast_<Target, boost::simd::domain> >))
                            )
  {
    typedef typename Target::type                           result_type;

    typedef typename boost::dispatch::meta::
            semantic_of<result_type>::type                  vtype;
    typedef typename meta::scalar_of<vtype>::type           stype;

    #define M0(z,n,t)                                                          \
    BOOST_FORCEINLINE result_type                                    \
    operator()(BOOST_PP_ENUM_PARAMS(n, stype const& a)) const                  \
    {                                                                          \
      return make<vtype>(BOOST_PP_ENUM_PARAMS(n, a));                          \
    }                                                                          \
    /**/
    BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)

    #undef M0
  };
} } }

#endif

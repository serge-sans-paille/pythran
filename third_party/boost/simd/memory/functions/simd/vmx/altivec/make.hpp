//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_MAKE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_MAKE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/memory/functions/make.hpp>
#include <boost/simd/preprocessor/make_helper.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((target_ < simd_ < type32_<A0>
                                                        , boost::simd::tag::vmx_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(4)
    {
      typename result_type::native_type that = { a0, a1, a2, a3 };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((target_ < simd_ < type16_<A0>
                                                        , boost::simd::tag::vmx_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(8)
    {
      typename result_type::native_type that = { a0, a1, a2, a3 , a4, a5, a6, a7 };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((target_ < simd_ < type8_<A0>
                                                        , boost::simd::tag::vmx_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(16)
    {
      typename result_type::native_type that = { a0, a1 , a2,  a3 ,  a4,  a5,  a6,  a7
                                               , a8, a9, a10, a11 , a12, a13, a14, a15 };
      return that;
    }
  };
} } }

#endif
#endif

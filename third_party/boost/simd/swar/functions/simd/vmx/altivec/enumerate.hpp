//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_ENUMERATE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/swar/functions/enumerate.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_
                                    , boost::simd::tag::vmx_
                                    , (T)
                                    , ((target_
                                        < simd_ < ints8_<T>
                                                , boost::simd::tag::vmx_
                                                >
                                        >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE result_type operator()(T const& ) const
    {
      typedef typename result_type::template rebind<unsigned char>::type u8type;

      // [0 1 2 ... 12 15]
      u8type that = vec_lvsl(0,(unsigned char*)(0));

      return bitwise_cast<result_type>(that);
    }
  };
} } }

#endif
#endif

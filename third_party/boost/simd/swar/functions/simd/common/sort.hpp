//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SORT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SORT_HPP_INCLUDED

#include <boost/simd/swar/functions/sort.hpp>
#include <boost/simd/include/functions/simd/aligned_load.hpp>
#include <boost/simd/include/functions/simd/aligned_store.hpp>
#include <boost/simd/preprocessor/aligned_type.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

#include <algorithm>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::sort_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      static const size_t size = boost::simd::meta::cardinal_of<A0>::value;
      BOOST_SIMD_ALIGNED_TYPE(stype) tmp[size];
      aligned_store(a0, &tmp[0], 0);
      std::sort(tmp, tmp + size);
      return aligned_load<A0>(&tmp[0], 0);
    }
  };
} } }


#endif

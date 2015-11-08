//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_SORT_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_SORT_HPP_INCLUDED
#include <nt2/swar/functions/sort.hpp>
#include <nt2/include/functions/simd/aligned_load.hpp>
#include <nt2/include/functions/simd/aligned_store.hpp>
#include <boost/simd/preprocessor/aligned_type.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/include/functions/real.hpp>

#include <algorithm>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sort_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<complex_<floating_<A0> >,X>))
                            )
  {
    typedef A0 result_type;
    typedef typename meta::scalar_of<A0>::type stype;
    NT2_FUNCTOR_CALL(1)
    {
      static const size_t size = nt2::meta::cardinal_of<A0>::value;
      BOOST_SIMD_ALIGNED_TYPE(stype) tmp[size];
      aligned_store(a0, &tmp[0], 0);
      std::sort(tmp, tmp + size, cmp);
      return aligned_load<A0>(&tmp[0], 0);
    }
   private:
    static bool cmp(const stype& a0, const stype& a1)
    {
      //  when x is complex, the elements are sorted by abs(x).  complex
      //  matches are further sorted by arg(x).
      return (nt2::abs(a0) < nt2::abs(a1)) || ((nt2::abs(a0) == nt2::abs(a1))&& (arg(a0) <= arg(a1)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sort_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<dry_<floating_<A0> >,X>))
                            )
  {
    typedef A0 result_type;
    typedef typename meta::scalar_of<A0>::type stype;
    NT2_FUNCTOR_CALL(1)
    {
      result_type(nt2::sort(nt2::real(a0)));
    }
  };

 } }


#endif

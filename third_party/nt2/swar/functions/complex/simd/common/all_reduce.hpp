//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_ALL_REDUCE_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_ALL_REDUCE_HPP_INCLUDED

#include <nt2/swar/functions/all_reduce.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/shuffle.hpp>
#include <nt2/include/functions/insert.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::all_reduce_
                            , boost::simd::tag::simd_
                            , (Tag)(A0)(X)
                            , ((simd_<dry_<arithmetic_<A0> >,X>))
                              (target_< unspecified_<Tag> >)
                            )
  {
    typedef typename meta::as_real<A0>::type                        r_t;
    typedef typename Tag::type                                      base;
    typedef typename meta::call<base(r_t const&, r_t const&)>::type res_t;
    typedef typename meta::as_dry<res_t>::type                      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      return bitwise_cast<result_type>(all_reduce<base>(bitwise_cast<r_t>(a0)));
    }
  };
} }

#endif

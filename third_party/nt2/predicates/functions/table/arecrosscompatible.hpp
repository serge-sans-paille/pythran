//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ARECROSSCOMPATIBLE_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ARECROSSCOMPATIBLE_HPP_INCLUDED

#include <nt2/predicates/functions/arecrosscompatible.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/include/functions/havesamesize.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arecrosscompatible_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A1& a1, A2 dim) const
    {
      if (dim == 0) return false;

      typedef typename meta::call<tag::extent_(A0 const&)>::type ext1_t;
      ext1_t ex1 = nt2::extent(a0);

      typedef typename meta::call<tag::extent_(A1 const&)>::type ext2_t;
      ext2_t ex2 = nt2::extent(a1);

      if(   (size_t(dim) > ex1.size())
        ||  (size_t(dim) > ex2.size())
        ||  (ex1[dim-1]!= 3) || (ex2[dim-1]!= 3)
        )
        return false;

      return nt2::havesamesize(a0, a1);
    }
  };
} }

#endif

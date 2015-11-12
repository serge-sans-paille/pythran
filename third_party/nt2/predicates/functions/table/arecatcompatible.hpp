//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ARECATCOMPATIBLE_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ARECATCOMPATIBLE_HPP_INCLUDED

#include <nt2/predicates/functions/arecatcompatible.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/include/functions/isvectoralong.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arecatcompatible_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef bool result_type;

    result_type operator()(const A0& a0, const A1& a1, A2 dim) const
    {
      typedef typename meta::call<tag::extent_(A0 const&)>::type ext1_t;
      ext1_t ex1 = nt2::extent(a0);

      typedef typename meta::call<tag::extent_(A1 const&)>::type ext2_t;
      ext2_t ex2 = nt2::extent(a1);

      size_t sz = std::min(ex1.size(), ex2.size());
      size_t d  = dim-1;

      // Concatenating to empty array is always OK
      if(numel(ex1) == 0 || numel(ex2) == 0) return true;

      for(size_t i=0; i < sz; ++i)
      {
        if ((i != d) && (ex1.data()[i]!= ex2.data()[i])) return false;
      }

      sz = std::max(sz, d+1);
      for(size_t i=sz; i < ex1.size(); ++i)
      {
        if ((ex1[i]!= 1)) return false;
      }

      for(size_t i=sz; i < ex2.size(); ++i)
      {
        if ((ex2[i]!= 1)) return false;
      }

      return true;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arecatcompatible_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<unspecified_<A1> >)
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&a0, const A1&, A2 dim) const
    {
      return !numel(a0) || isvectoralong(a0, dim);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arecatcompatible_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&, const A1&a1, A2 dim) const
    {
      return !numel(a1) || isvectoralong(a1, dim);
    }
  };
} }

#endif

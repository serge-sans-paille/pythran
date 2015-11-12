//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_TRANSFORM_HPP_INCLUDED

#include <nt2/core/functions/transform.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/run.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Global version
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, tag::cpu_
                            , (Out)(In)
                            , ((ast_<Out, nt2::container::domain>))
                              ((ast_<In, nt2::container::domain>))
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(Out& out, In& in) const
    {
      nt2::transform(out,in,std::make_pair(0,nt2::numel(out)));
    }
  };

  //============================================================================
  // Partial version - Process sz elements starting at element p
  // Note that p should be properly set beforehand
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, tag::cpu_
                            , (Out)(In)(Range)
                            , ((ast_<Out, nt2::container::domain>))
                              ((ast_<In, nt2::container::domain>))
                              (unspecified_<Range>)
                            )
  {
    typedef void result_type;

    typedef typename Out::value_type                stype;

    BOOST_FORCEINLINE result_type
    operator()(Out& out, In& in, Range range) const
    {
      std::size_t p = range.first;
      std::size_t sz = range.second;
      std::size_t bound = p+sz;
      for(std::size_t i=p; i != bound; ++i)
        nt2::run(out, i, nt2::run(in, i, meta::as_<stype>()));
    }
  };
} }

#endif

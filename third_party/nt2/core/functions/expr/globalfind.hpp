//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_GLOBALFIND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_GLOBALFIND_HPP_INCLUDED

#include <nt2/core/functions/globalfind.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalfind_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call < tag::globalfind_(A0 const&
                                , meta::as_<std::ptrdiff_t>)
                                >::type                       result_type;

    result_type operator()(A0 const& a0) const
    {
      return nt2::globalfind(a0, meta::as_<std::ptrdiff_t>());
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalfind_, tag::cpu_
                            , (A0)(A1)
                            , (unspecified_<A0>)
                              (target_< scalar_< integer_<A1> > >)
                            )
  {
    typedef typename A0::value_type                         stype;
    typedef typename A1::type                               index_type;
    typedef nt2::memory::container<tag::table_,index_type, nt2::_1D>    term;
    typedef boost::dispatch::meta::terminal_of_shared<term> result;
    typedef typename result::type                           result_type;

    result_type operator()(A0 const& a0, A1 const&) const
    {
      result_type ret = result::make();

      std::size_t m = nt2::numel(a0);
      for(std::size_t i=0; i!=m; ++i)
      {
        stype value = nt2::run(a0, i, meta::as_<stype>());
        if(value)
          boost::proto::value(ret).push_back(index_type(i+1));
      }

      return ret;
    }
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_LAST_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_LAST_INDEX_HPP_INCLUDED

#include <nt2/core/functions/last_index.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/core/container/dsl.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <nt2/include/functions/size.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::last_index_,tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (mpl_integral_< scalar_< integer_<A1> > >)
                            )
  {
    typedef std::ptrdiff_t result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return    first_index<A1::value>(a0) - 1
              + result_type(nt2::size(a0,A1::value));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::last_index_,tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef std::ptrdiff_t result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& d) const
    {
      return  first_index(a0,d) - 1 + result_type(nt2::size(a0,d));
    }
  };
} }

#endif

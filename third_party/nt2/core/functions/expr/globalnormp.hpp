//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_GLOBALNORMP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_GLOBALNORMP_HPP_INCLUDED

#include <nt2/include/functions/globalnormp.hpp>
#include <nt2/include/functions/normp.hpp>
#include <nt2/include/functions/global.hpp>
#include <nt2/core/container/dsl.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalnormp_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<arithmetic_<A1> > )
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::normp_>
                                            , const A0&
                                            , const A1&
                                            )>::type              result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
       return global(nt2::functor<tag::normp_>(), a0, a1);
    }
  };
} }


#endif

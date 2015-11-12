//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_ADJFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_ADJFUN_HPP_INCLUDED
#include <nt2/core/functions/adjfun.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::adjfun_, tag::cpu_
                            , (Functor)(A0)
                            , (unspecified_<Functor>)
                              (scalar_<unspecified_<A0> >)
                            )
  {
    typedef container::table<A0,of_size_<0> > result_type;

    BOOST_FORCEINLINE
    result_type operator()(Functor const&, A0 const&) const
    {
      return result_type();
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::adjfun_, tag::cpu_
                            , (Functor)(A0)(Along)
                            , (unspecified_<Functor>)
                              (scalar_<unspecified_<A0> >)
                              (scalar_<integer_<Along> >)
                            )
  {
    typedef container::table<A0, of_size_<0> > result_type;

    BOOST_FORCEINLINE
    result_type operator()(Functor const&, A0 const&, Along const&) const
    {
      return result_type();
    }
  };
} }

#endif

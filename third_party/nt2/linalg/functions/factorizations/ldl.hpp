//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_LDL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_LDL_HPP_INCLUDED

#include <nt2/linalg/functions/lu.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/linalg/functions/details/ldl.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::ldl_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename meta::strip<A0>::type                            base_t;
    typedef typename base_t::value_type                              value_t;
    typedef typename base_t::settings_type                        settings_t;
    typedef details::ldl_result< table<value_t,settings_t> >      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      result_type that(a0);
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::ldl_, tag::cpu_
                            , (A0)(IP)
                            , ((ast_<A0, nt2::container::domain>))
                              (unspecified_< IP >)
                            )
  {
    typedef details::ldl_result<A0&>       result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, IP const&) const
    {
      result_type that(a0);
      return that;
    }
  };
} }

#endif

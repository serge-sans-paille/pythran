//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_RREF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_RREF_HPP_INCLUDED

#include <nt2/linalg/functions/rref.hpp>
#include <nt2/options.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/linalg/functions/details/rref.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::rref_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< floating_<A1> >)
                            )
  {
    typedef typename meta::strip<A0>::type                            base_t;
    typedef typename base_t::value_type                              value_t;
    typedef typename base_t::settings_type                        settings_t;
    typedef details::rref_result< table<value_t,settings_t> >    result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& tol) const
    {
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "??? Error using 'rref' : argument a0 must be matrix."
                      );
      result_type that(a0, tol);
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::rref_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename meta::strip<A0>::type                            base_t;
    typedef typename base_t::value_type                              value_t;
    typedef typename base_t::settings_type                        settings_t;
    typedef details::rref_result< table<value_t,settings_t> >    result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "??? Error using 'rref' : argument a0 must be matrix."
                      );
      result_type that(a0, value_t(-1));
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::rref_, tag::cpu_
                            , (A0)(A1)(IP)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< floating_<A1> >)
                              (unspecified_< IP >)
                            )
  {
    typedef details::rref_result<A0&> result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1 const& tol, IP const&) const
    {
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "??? Error using 'rref' : argument a0 must be matrix."
                      );
      result_type that(a0, tol);
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::rref_, tag::cpu_
                            , (A0)(IP)
                            , ((ast_<A0, nt2::container::domain>))
                              (unspecified_< IP >)
                            )
  {
    typedef details::rref_result<A0&> result_type;
    typedef typename A0::value_type       value_t;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, IP const&) const
    {
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "??? Error using 'rref' : argument a0 must be matrix."
                      );
      result_type that(a0, value_t(-1));
      return that;
    }
  };
} }

#endif

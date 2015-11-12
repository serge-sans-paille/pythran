//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_VANDERMONDE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_VANDERMONDE_HPP_INCLUDED

#include <nt2/gallery/functions/vandermonde.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/colvect.hpp>

namespace nt2 {namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vandermonde_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
    )
  {
    typedef typename A0::value_type                              value_type;
    typedef typename meta::as_real<value_type>::type              real_type;
    typedef typename meta::call<tag::colvect_(A0)>::type  T0;
    typedef typename meta::call<tag::colon_ ( real_type
                                            , real_type
                                            , real_type
                                            )>::type      T1;
    typedef typename meta::call<tag::sx_( tag::pow_
                                        , T0
                                        , T1
                                        )>::type      result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::sx( tag::pow_()
                    , colvect(a0)
                    , colon( real_type(a1-1)
                           , real_type(-1)
                           , real_type(0)
                           )
                    );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vandermonde_, tag::cpu_
                              , (A0)
                              , ((ast_<A0, nt2::container::domain>))
    )
  {
    typedef typename meta::call<tag::numel_(const A0&)>::type                     size_type;
    typedef typename meta::call<tag::vandermonde_( const A0&, size_type)>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::vandermonde(a0, numel(a0));
    }
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_DRAMADAH_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_DRAMADAH_HPP_INCLUDED

#include <nt2/gallery/functions/dramadah.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/toeplitz.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dramadah_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 a0)
                          , ( boost::proto::make_expr
                              <nt2::tag::dramadah_, container::domain>
                              ( a0, std::size_t(1)
                              , meta::as_<double>(), _2D(a0,a0)
                              )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dramadah_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 a0, T const& t)
                          , ( boost::proto::make_expr
                              <nt2::tag::dramadah_, container::domain>
                              ( boost::cref(a0), std::size_t(1), t, _2D(a0,a0) )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dramadah_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 a0, A1 a1)
                          , ( boost::proto::make_expr
                              <nt2::tag::dramadah_, container::domain>
                              ( a0, a1, meta::as_<double>(), _2D(a0,a0) )
                            )
                          );
  };

  //2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dramadah_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 a0, A1 a1, T const& t)
                          , ( boost::proto::make_expr
                              <nt2::tag::dramadah_, container::domain>
                              ( a0, a1, t, _2D(a0,a0) )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1,nt2::tag::dramadah_,N
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&                                                     result_type;
    typedef typename A0::value_type                                         v_t;
    typedef typename nt2::container::table <v_t>                          tab_t;

    result_type operator()(A0& out, const A1& in) const
    {
      size_t n =  boost::proto::child_c<0>(in);
      size_t k =  boost::proto::child_c<1>(in);
      if (n == 0)
      {
        out.resize(nt2::of_size(0, 1));
        return out;
      }

      out.resize(of_size(n, n));
      compute(out, n, k);

      return out;
    }
  private :
    static void compute(A0& out, size_t n,  size_t k)
    {
      if(k == 1)
      {
        // Toeplitz
        tab_t c = nt2::ones(n,1,meta::as_<v_t>());
        for(size_t i=2; i <= n; i+= 4)
        {
          size_t m = nt2::min(size_t(1),n-i);
          c(nt2::_(i,i+m)) = Zero<v_t>();
        }
        tab_t r = zeros(n,1,meta::as_<v_t>());
        r(1) = r(n >= 2 ? 2 : 1) = r(n >= 4 ? 4 : 1) = nt2::One<v_t>();
        out = nt2::toeplitz (c,r);
      }
      else if (k == 2)
      {
        // Upper triangular and Toeplitz
        tab_t c = nt2::zeros(n,1,meta::as_<v_t>());
        c(1) = 1;
        tab_t r =nt2::ones(n,1,meta::as_<v_t>());
        r(nt2::_(size_t(3),size_t(2),n)) = nt2::Zero<v_t>();
        out = nt2::toeplitz (c,r);
      }
      else
      {
        //  Lower Hessenberg.
        tab_t c = nt2::ones(n,1,meta::as_<v_t>());
        c(nt2::_(size_t(2), size_t(2), n)) = nt2::Zero<v_t>();
        tab_t d = nt2::zeros(n,1,meta::as_<v_t>());
        d(1) = d(2) = 1;
        out = nt2::toeplitz(c, d);
      }
    }
  };
} }

#endif

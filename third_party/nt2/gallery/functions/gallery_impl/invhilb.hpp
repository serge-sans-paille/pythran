//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_INVHILB_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_INVHILB_HPP_INCLUDED
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/round2even.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::invhilb_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >
                            )
    )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::invhilb_
                                          , container::domain
                                          , T, _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,T  const& tgt) const
    {
      return  boost::proto::
              make_expr < nt2::tag::invhilb_
                        , container::domain
                        >( tgt, _2D(a0,a0) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::invhilb_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::invhilb_
                                          , container::domain
                                          , meta::as_<double>
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      return  boost::proto::
              make_expr < nt2::tag::invhilb_
                        , container::domain
                        >( meta::as_<double>(), _2D(a0,a0) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::invhilb_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                     result_type;
    typedef typename A0::value_type value_type;

    result_type operator()(A0& out, const A1& in) const
    {
      _2D sz = boost::proto::value(boost::proto::child_c<1>(in));
      out.resize(sz);

      value_type n = sz[0];
      value_type p = n;
      value_type r = nt2::sqr(p);

      out(1, 1) = r;

      for(std::size_t j = 2; j <= n; ++j)
      {
        r =  -((n-j+1)*r*(n+j-1))/nt2::sqr(j-1);
        out(1,j) = r/j;
        out(j,1) = out(1, j);
      }

      for(std::size_t i = 2; i <= n; ++i)
      {
        p = ((n-i+1)*p*(n+i-1))/nt2::sqr(i-1);
        r = nt2::sqr(p);
        out(i,i) = r/(2*i-1);

        for(std::size_t j = i+1; j <= n; ++j)
        {
          r = -((n-j+1)*r*(n+j-1))/nt2::sqr(j-1);
          out(i,j) = r/(i+j-1);
          out(j,i) = out(i, j);
        }
      }

      return out = nt2::round2even(out);
    }
  };
} }


#endif

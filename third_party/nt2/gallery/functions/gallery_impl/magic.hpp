//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_MAGIC_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_MAGIC_HPP_INCLUDED
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/mod.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::magic_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::magic_
                                          , container::domain
                                          , std::size_t, T, _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, T const& tgt) const
    {
      return  boost::proto::
              make_expr<nt2::tag::magic_, container::domain>
              ( std::size_t(a0)
              , tgt
              , _2D(a0,a0)
              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::magic_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::magic_
                                          , container::domain
                                          , std::size_t
                                          , meta::as_<double>
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return  boost::proto::
              make_expr<nt2::tag::magic_, container::domain>
              ( std::size_t(a0)
              , meta::as_<double>()
              , _2D(a0,a0)
              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::magic_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,1>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  boost::dispatch::meta::semantic_of<tmp1_type>::type tmp2_type;
    typedef typename  tmp2_type::type                                    value_type;

    result_type operator()(A0& out, const A1& in) const
    {
      std::size_t n = boost::proto::child_c<0>(in);

      BOOST_ASSERT_MSG(n!= 2, "There is no 2x2 magic matrix");

      out.resize(nt2::of_size(n, n));

      if(n%2 == 1) //Odd order
      {
        oddOrderMagicSquare(out,n);
      }
      else if(n%4 == 0)
      {
        evenx2(out,n);
      }
      else
      {
        evenx1(out,n);
      }
      return out;
    }
  private :
    static void oddOrderMagicSquare(A0& out, std::size_t n)
    {
        value_type nn = n;
        BOOST_AUTO_TPL(pp, nt2::_(value_type(1), nn));
        BOOST_AUTO_TPL(pprim,  nt2::colvect(pp));
        value_type h1 = (n+3) >> 1;
        BOOST_AUTO_TPL(p2, nt2::Two<value_type>()*nt2::minusone(pp));
        BOOST_AUTO_TPL(mm1, nt2::mod(nt2::sx(nt2::tag::plus_(),pprim,pp-h1),nn));
        BOOST_AUTO_TPL(mm2, nt2::mod(nt2::sx(nt2::tag::plus_(),pprim,p2),nn));
        out = nt2::oneplus(nn*mm1+mm2);
    }
    static void evenx2(A0& out, std::size_t n)
    {
      value_type nn = n;
      BOOST_AUTO_TPL(p, nt2::_(value_type(1), nn));
      BOOST_AUTO_TPL(j, nt2::trunc(nt2::mod(p,nt2::Four<value_type>())*nt2::Half<value_type>()));
      BOOST_AUTO_TPL(k, nt2::sx(nt2::tag::is_equal_(), j, nt2::colvect(j)));
      BOOST_AUTO_TPL(p1, colvect(nt2::_(value_type(1), nn, nt2::sqr(nn))));
      out =  nt2::sx(nt2::tag::plus_(),p1,nt2::minusone(p));
      out(k) = nt2::oneplus(sqr(nn)) - out(k);
    }

    static void evenx1(A0& out, std::size_t n)
    {
      std::size_t m = n >> 1;   //m is odd.
      oddOrderMagicSquare(out, m);
      value_type m2 = sqr(m);
      container::table<value_type> t =  nt2::catv(cath(out, out+Two<value_type>()*m2),
                                                  cath(out+Three<value_type>()*m2, out+m2));
      BOOST_AUTO_TPL(i,  colvect(nt2::_(1, m)));
      std::size_t k = (n-2) >> 2;
      BOOST_AUTO_TPL(j, nt2::cath(nt2::_(std::size_t(1), k), nt2::_(n-k+2, n)));
      swap_lines(t, i, i+m, j);
      std::size_t k1 = k+1;
      BOOST_AUTO_TPL(ii, nt2::_(k1, k1));
      BOOST_AUTO_TPL(jj, nt2::_(std::size_t(1), k+1));
      swap_lines(t, ii, ii+m, jj);
      out =  t;
    }

    template < class M, class I1, class I2, class IDX > static
    void swap_lines(M& m, I1 i1, I2 i2, const IDX & j)
    {
      container::table<value_type> tmp = m(i1, j);//buggy if i1 i2 are integers
      m(i1, j) = m(i2, j);
      m(i2, j) = tmp;
    }
  };
} }

#endif

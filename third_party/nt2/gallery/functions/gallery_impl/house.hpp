//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_HOUSE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_HOUSE_HPP_INCLUDED

#include <nt2/gallery/functions/house.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/globalnorm2.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/isreal.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/signnz.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::house_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS( 1
                          , (A0 const& a0)
                          , ( boost::proto::make_expr
                              < nt2::tag::house_
                              , container::domain
                              > ( boost::cref(a0)
                                , std::size_t(0)
                                , _2D(numel(a0),1)
                                )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::house_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::house_
                                          , container::domain
                                          , A0 const&
                                          , std::size_t
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 a1) const
    {
      return  boost::proto::
              make_expr<nt2::tag::house_, container::domain>
              ( boost::cref(a0)
              , std::size_t(a1)
              , _2D(numel(a0),1)
              );
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::house_, tag::cpu_
                            , (A0)(A1)(N1)
                            , ((node_<A0, nt2::tag::house_, boost::mpl::long_<3>, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::strip<child0>::type                              v_t;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type       child1;
    typedef typename v_t::value_type                                    value_t;
    typedef typename meta::as_real<value_t>::type                        real_t;
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      size_t k =  boost::proto::value(boost::proto::child_c<1>(a0));//get(a0, N0());
      BOOST_AUTO_TPL(x, boost::proto::child_c<0>(a0));
      BOOST_ASSERT_MSG(N1::value == 3, "house needs 3 outputs");
      size_t n =  numel(x);

      BOOST_AUTO_TPL(v, boost::proto::child_c<0>(a1));
      value_t& beta =   boost::proto::child_c<1>(a1);
      value_t& s    =   boost::proto::child_c<2>(a1);
      v = nt2::colvect(x);
      real_t nrmx2n = nt2::globalnorm2(v(nt2::_(2, n)));
      real_t nrmx = nt2::hypot(x(1), nrmx2n);
      // Quit if x is the zero vector.
      if (nrmx == 0)
      {
        beta = nt2::Zero<value_t>();
        s = nt2::One<value_t>();
        return;
      }
      s = nrmx*nt2::signnz(x(1));
      if (k == 2)
      {
        if (nt2::isreal(x))
        {
          k = nt2::is_gez(s) ? 1 : 0;
        }
        else
        {
          k = 0;
        }
      }
      if ( k == 0 )
      {
        s = -s;
        v(1) -= s;
      }
      else
      {
        v(1) = -nt2::sqr(nrmx2n)/nt2::conj(x(1)+s);
      }
      if (nt2::is_eqz(v(1))) // special case where v = 0: need h = i.
      {
        beta = One<value_t>();
        return;
      }
      beta = -rec(conj(s)*v(1));
    }
  };
} }

#endif

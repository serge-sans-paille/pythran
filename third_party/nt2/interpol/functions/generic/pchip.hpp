//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_GENERIC_PCHIP_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_GENERIC_PCHIP_HPP_INCLUDED

#include <nt2/interpol/functions/pchip.hpp>
#include <nt2/include/functions/ppval.hpp>
#include <nt2/include/functions/is_nge.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/issorted.hpp>
#include <nt2/include/functions/bsearch.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/globalfind.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/isreal.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/unary_plus.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pchip_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                              (unspecified_<A2> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 &, const A1 &, const A2 &) const

    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return Nan<A0>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pchip_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                              (unspecified_<A2> )
                              (unspecified_<A3> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 & , const A0 & , const A0 & , const A0 & ) const
    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return Nan<A0>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::pchip_,N1,nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::value_type  child1;
    typedef typename boost::proto::result_of::child_c<A1&,2>::value_type  child2;
    typedef typename child0::value_type                               value_type;
    typedef typename meta::as_integer<value_type>::type               index_type;
    typedef table<value_type>                                             vtab_t;
    typedef table<index_type>                                             itab_t;
    typedef A0&                                                      result_type;


    result_type operator()(A0& yi, A1& inputs) const
    {
      yi.resize(inputs.extent());
      const child0 & x   =  boost::proto::child_c<0>(inputs);
      if (numel(x) <=  1)
        BOOST_ASSERT_MSG(numel(x) >  1, "Interpolation requires at least two sample points in each dimension.");
      else
      {
        BOOST_ASSERT_MSG(issorted(x, 'a'), "for 'pchip' interpolation x values must be sorted in ascending order");
        const child1 & y   =  boost::proto::child_c<1>(inputs);
        BOOST_ASSERT_MSG(numel(x) == numel(y), "The grid vectors do not define a grid of points that match the given values.");
        const child2 & xi  =  boost::proto::child_c<2>(inputs);
        bool extrap = false;
        value_type extrapval = Nan<value_type>();
        choices(inputs, extrap, extrapval, N1());
        vtab_t h  =  nt2::diff(x,1,2);
        vtab_t del = nt2::diff(y,1,2)/h;
        pchipslopes(x,y,del, yi);
        ppval <value_type> pp(x,y,yi,h,del);
        yi =pp.eval(xi);
        if (!extrap)
        {
          value_type  b =  value_type(x(begin_));
          value_type  e =  value_type(x(end_));
          yi = nt2::if_else(nt2::logical_or(boost::simd::is_nge(xi, b),
                                            boost::simd::is_nle(xi, e)), extrapval, yi);
        }
      }

       return yi;
    }
  private :
    static void choices(const A1&, bool &,  value_type&, boost::mpl::long_<3> const &)
    { }
    static void choices(const A1& inputs, bool & extrap,  value_type& extrapval, boost::mpl::long_<4> const &)
    {
      typedef typename boost::proto::result_of::child_c<A1&,3>::type             child3;
      typedef typename meta::scalar_of<child3>::type                    cref_param_type;
      typedef typename meta::strip<cref_param_type>::type                    param_type;
      get(inputs, extrap, extrapval, param_type());
    }
    static void get(const A1& inputs, bool & extrap,  value_type&,  const bool &)
    {
      extrap =  boost::proto::child_c<3>(inputs);
    }
    static void get(const A1& inputs, bool &,  value_type& extrapval,  const value_type &)
    {
      extrapval =  boost::proto::child_c<3>(inputs);
    }

    static void pchipslopes(const child0 & x, const child1 & y, const vtab_t &del, A0& d)
    {
      itab_t k;
      size_t n =  length(x);
      if (nt2::numel(x) == 2)
      {
        d =  nt2::repnum(value_type(del(begin_)), 1, width(y)); // del(begin_) is not of value_type !
      }
      else
      {
        d =  nt2::zeros(1, width(y), nt2::meta::as_<value_type>());
        //if (/* nt2::isreal(del)*/ true) //to do proper version for real types
        { // is k 1 based or 0,  I hope 1 here ?
          k = nt2::globalfind(nt2::is_gtz(nt2::multiplies(nt2::sign(del(nt2::_(begin_, begin_+n-3))), nt2::sign(del(nt2::_(begin_+1, begin_+n-2))))), nt2::meta::as_<index_type>());
        }
/*
        else
        {
          k = nt2::globalfind(nt2::logical_and(is_eqz(del(nt2::_(begin_, begin_+n-3))), is_eqz(del(nt2::_(begin_+1,begin_+n-2)))), nt2::meta::as_<index_type>());
        }
*/      }
      itab_t kp1 = oneplus(k);
      itab_t kp2 = oneplus(kp1);
      vtab_t h = nt2::diff(x, 1, 2);
      vtab_t hs = h(1, k)+h(1, kp1);
      vtab_t w1 = (h(1, k)+hs)/(Three<value_type>()*hs);
      vtab_t w2 = (hs+h(1, kp1))/(Three<value_type>()*hs);
      vtab_t dmax = nt2::max(nt2::abs(del(1, k)), nt2::abs(del(1, kp1)));
      vtab_t dmin = nt2::min(nt2::abs(del(1, k)), nt2::abs(del(1, kp1)));
      d(kp1) = dmin/nt2::conj(nt2::multiplies(w1,(del(1, k)/dmax)) + nt2::multiplies(w2, (del(1, kp1)/dmax)));
      //   Slopes at end points.
      //   Set d(0) and d(n-1) via non-centered, shape-preserving three-point formulae.
      d(1) = ((2*h(1)+h(2))*del(1) - h(1)*del(2))/(h(1)+h(2));
      if (/*nt2::isreal(d) && */(nt2::sign(d(nt2::first_index<1>(d))) != nt2::sign(del(1))))
      {
        d(nt2::first_index<2>(d)) = Zero<value_type>();
      }
      else if ((nt2::sign(del(1)) != nt2::sign(del(1))) &&
               (nt2::abs(d(nt2::first_index<1>(d))) > nt2::abs(Three<value_type>()*del(1))))
      {
        d(nt2::first_index<2>(d)) = Three<value_type>()*del(1);
      }
      //      index_type end = n;
      //     NT2_DISPLAY(h);
      d(nt2::last_index<2>(d)) = ((Two<value_type>()*h(n-1)+h(n-2))*del(n-1) - h(n-1)*del(n-2))/(h(n-1)+h(n-2));
      if (/*isreal(d) &&*/ (nt2::sign(d(nt2::last_index<1>(d))) != nt2::sign(del(n-1))))
      {
        d(nt2::last_index<2>(d)) = Zero<value_type>();
      }
      else if ((nt2::sign(del(n-1)) != nt2::sign(del(n-2))) &&
               (nt2::abs(d(nt2::last_index<1>(d))) > nt2::abs(Three<value_type>()*del(n-1))))
      {
        d(nt2::last_index<2>(d)) = 3*del(n-1);
      }
    }
  };
} }


#endif

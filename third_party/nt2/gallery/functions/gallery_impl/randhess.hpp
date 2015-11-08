//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDHESS_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDHESS_HPP_INCLUDED
#include <nt2/gallery/functions/randhess.hpp>
#include <nt2/include/functions/cauchy.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/signnz.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/constants/twopi.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2
{

  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randhess0_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS( 2
                            , (A0 const& n, T const & t)
                            , ( nt2::Twopi<t_t>()
                              * nt2::randhess(nt2::rand(n, 1, t))
                              )
                            )
    };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::randhess_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    result_type operator()(A0& out0, const A1& in) const
    {
      BOOST_AUTO_TPL(x, boost::proto::child_c<0>(in));
      size_t n =  nt2::numel(x); ;
      nt2::table<value_t> out = nt2::eye(n,nt2::meta::as_<value_t>()); // couldn't out be directly the output out0 ? TODO
      out(n,n) = nt2::signnz(x(n));
      nt2::table<value_t> s(extent(x)), c(extent(x));
      nt2::tie(s, c) = nt2::sincos(x);
      for(size_t i=n-1; i >= 1; --i)
      {
        BOOST_AUTO_TPL(idx, nt2::_(i, i+1));
        // Apply Givens rotation through angle x(i-1).
        out(idx,_) = mtimes(nt2::catv(nt2::cath(c(i), s(i)), nt2::cath(-s(i), c(i))), out(idx,_)); //this seems not to work properly if out is out0
      }
      return out0 = out;
    }
  };

}

  meta::call<tag::randhess0_(const ptrdiff_t &, meta::as_<double> const &)>::type
  randhess(ptrdiff_t n)
  {
    return nt2::randhess(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::randhess0_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  randhess(ptrdiff_t n)
  {
    return nt2::randhess(n,  meta::as_<T>());
  }

}


#endif

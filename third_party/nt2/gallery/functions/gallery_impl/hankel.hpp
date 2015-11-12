//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_HANKEL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_HANKEL_HPP_INCLUDED
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ric.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::hankel_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                          result_type;
    typedef typename A0::value_type                                       value_type;
    result_type operator()(A0& out, const A1& in) const
    {
      out.resize(extent(in));
      prepare(out, in, N());
      return out;
    }
  private:
    static void prepare(A0& out, const A1& in,  boost::mpl::long_<1> const &)
    {
      BOOST_AUTO_TPL(c, nt2::colvect(boost::proto::child_c<0>(in)));
      BOOST_AUTO_TPL(r, nt2::zeros(extent(c), meta::as_<value_type>()));
      compute(out, c, r);
    }
    static void prepare(A0& out, const A1& in,  boost::mpl::long_<2> const &)
    {
      BOOST_AUTO_TPL(c,  nt2::colvect(boost::proto::child_c<0>(in)));
      BOOST_AUTO_TPL(r,  nt2::colvect(boost::proto::child_c<1>(in)));
      compute(out, c, r);
    }
    template < class C, class R >
    static void compute(A0& out,const C& c, const R& r)
    {
      size_t nc = numel(c);
      size_t nr = numel(r);
      BOOST_AUTO_TPL(x, nt2::vertcat(c, nt2::colvect(r(nt2::_(2, nr)))));
      out(nt2::_) = x(nt2::cif(of_size(nc, nr), meta::as_<size_t>())+
                      nt2::ric(of_size(nc, nr), meta::as_<size_t>())
        );
    }
  };

} }

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of hankel.hpp
// /////////////////////////////////////////////////////////////////////////////

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_BANDRED_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_BANDRED_HPP_INCLUDED
#include <nt2/gallery/functions/bandred.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/house.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/colon.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tie.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::bandred_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& kl),
                           (nt2::bandred(a0, kl, kl))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::bandred_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    typedef nt2::table<value_t>                                               tab_t;
    result_type operator()(A0& out, const A1& in) const
    {
      out.resize(extent(boost::proto::child_c<0>(in)));
      size_t kl = boost::proto::child_c<1>(in);
      size_t ku = boost::proto::child_c<2>(in);
      bool flip = ku == 0;
      if (flip) std::swap(kl, ku);
      tab_t a;
      if(flip)
        a = nt2::transpose(boost::proto::child_c<0>(in));
      else
        a = boost::proto::child_c<0>(in);
      size_t m = nt2::size(a, 1);
      size_t n = nt2::size(a, 2);
      tab_t v(nt2::of_size(m, n)), temp;
      value_t beta, dum;
      for(size_t j=1; j <= nt2::min( nt2::min(m,n), nt2::max(m-kl-1,n-ku-1)); ++j)
      {
        if (j+kl+1 <= m)
        {
          nt2::tie(v, beta, dum) = nt2::house(a(nt2::_(j+kl, m),j), 0);
          temp = a(nt2::_(j+kl, m),nt2::_(j, n));
          a(nt2::_(j+kl, m),nt2::_(j, n)) = temp - beta*nt2::mtimes(v, nt2::mtimes(nt2::transpose(v), temp));
          a(nt2::_(j+kl+1, m),j) = Zero<value_t>();
        }
        if ( j+ku+1 <= n)
        {
          nt2::tie(v, beta, dum) = nt2::house(nt2::transpose(a(j, nt2::_(j+ku, m))), 0);
          temp = a(nt2::_(j, m), nt2::_(j+ku, n));
          a(nt2::_(j, m), nt2::_(j+ku, n)) = temp - beta*nt2::mtimes(nt2::mtimes(temp, v), nt2::transpose(v));
          a(j, nt2::_(j+ku+1, n)) = Zero<value_t>();
        }
      }
      if (flip)
      {
        out = nt2::transpose(a);
      }
      else
      {
        out = a;
      }
      return out;
    }
  };

}


}


#endif

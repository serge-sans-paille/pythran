//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_POLYVAL_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_POLYVAL_HPP_INCLUDED
#include <nt2/polynom/functions/polyval.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/vandermonde.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/inf.hpp>
#include <nt2/include/functions/trsolve.hpp>
#include <nt2/polynom/category.hpp>
#include <nt2/sdk/meta/fusion.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/sdk/error/warning.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>

namespace nt2 { namespace ext
{
   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyval_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> > )(scalar_<unspecified_<A1> > )
                            )
  {

    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return a0*a1;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyval_, tag::cpu_
                            , (A0)(A1)
                            , (unspecified_<A0>)(scalar_<unspecified_<A1> > )
                            )
  {

    typedef typename A0::value_type value_type;
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      if (isempty(a0)) return Zero<A1>();
      value_type ans = a0(1);
      for(size_t i = 2; i <= numel(a0); ++i)
      {
//       ans = fma(ans, a1, a0(i));
        ans *= a1;
        ans += a0(i);
      }
      return ans;
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyval_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::polyval_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       v_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type       p_type;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type       x_type;
    typedef typename A0::value_type                                  value_type;
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Copy data in output first
      v_type& v = boost::proto::child_c<0>(a1);
      v.resize(a0.extent());
      val(a0, a1, N1(), N0());
    }

  private:
    template < class S,  class T, class U> BOOST_FORCEINLINE
      void compute_val(S p, T x, U v)const
    {
      if (isempty(p))
      {
        v =  nt2::zeros(extent(x), meta::as_<value_type>());
      }
      else
      {
        v = repnum(p(1), size(x));
        for(size_t i = 2; i <= numel(p); ++i)
        {
            //          v = fma(v, x, p(i));
          v*= x;
          v+= p(i);
        }
      }
    }

    template < class S,  class T, class U,  class V> BOOST_FORCEINLINE
      void compute_delta(const S& x, const T& r,
                         const U& df,  const V& normr,
                         const size_t & nc,
                         container::table<value_type>& delta)const
    {
      NT2_WARNING(nt2::is_eqz(value_type(df)), "zero degree of freedom implies infinite error bounds.");
      BOOST_AUTO_TPL(vnd, nt2::vandermonde(x, nc));
      BOOST_AUTO_TPL(err, nt2::trsolve(nt2::trans(r), nt2::trans(vnd),'L') );
      value_type fact =   (normr/nt2::sqrt(value_type(df)));
      delta(nt2::_) =nt2::sqrt(oneplus(sum(sqr(err),1)))*fact;
    }

    template < class T > BOOST_FORCEINLINE
      void val(A0& a0, A1& a1,
               boost::mpl::long_<1> const &, const T&) const
    {
      BOOST_AUTO_TPL(p,  boost::proto::child_c<0>(a0));
      BOOST_AUTO_TPL(x,  boost::proto::child_c<1>(a0));
      BOOST_AUTO_TPL(v,  boost::proto::child_c<0>(a1));
      compute_val(p, x, v);
    }

    BOOST_FORCEINLINE
    void val(A0& a0, A1& a1,
             boost::mpl::long_<1> const &, boost::mpl::long_<3> const &) const
    {
      BOOST_AUTO_TPL(p,  boost::proto::child_c<0>(a0));
      BOOST_AUTO_TPL(x,  boost::proto::child_c<1>(a0));
      BOOST_AUTO_TPL(v,  boost::proto::child_c<0>(a1));
      BOOST_AUTO_TPL(mu,  boost::proto::child_c<2>(a0));
      compute_val(p, (x-mu(1))/mu(2), v);
    }
    BOOST_FORCEINLINE
    void val(A0& a0, A1& a1,
             boost::mpl::long_<1> const &, boost::mpl::long_<6> const &) const
    {
      BOOST_AUTO_TPL(p,  boost::proto::child_c<0>(a0));
      BOOST_AUTO_TPL(x,  boost::proto::child_c<1>(a0));
      BOOST_AUTO_TPL(v,  boost::proto::child_c<0>(a1));
      BOOST_AUTO_TPL(mu,  boost::proto::child_c<5>(a0));
      compute_val(p, (x-mu(1))/mu(2), v);
    }
    BOOST_FORCEINLINE
    void val(A0& a0, A1& a1,
             boost::mpl::long_<2> const &, boost::mpl::long_<5> const &) const
    {
      BOOST_AUTO_TPL(p,  boost::proto::child_c<0>(a0));
      BOOST_AUTO_TPL(x,  boost::proto::child_c<1>(a0));
      BOOST_AUTO_TPL(r,  boost::proto::child_c<2>(a0));
      BOOST_AUTO_TPL(df, boost::proto::child_c<3>(a0));
      BOOST_AUTO_TPL(nr, boost::proto::child_c<4>(a0));
      BOOST_AUTO_TPL(v,  boost::proto::child_c<0>(a1));
      compute_val(p, x, v);
      container::table<value_type> delta(extent(x));
      compute_delta(x, r, df, nr, nt2::numel(p), delta);
      boost::proto::child_c<1>(a1) = delta;
    }
    BOOST_FORCEINLINE
    void val(A0& a0, A1& a1,
             boost::mpl::long_<2> const &, boost::mpl::long_<6> const &) const
    {
      BOOST_AUTO_TPL(p,  boost::proto::child_c<0>(a0));
      BOOST_AUTO_TPL(x,  boost::proto::child_c<1>(a0));
      BOOST_AUTO_TPL(r,  boost::proto::child_c<2>(a0));
      BOOST_AUTO_TPL(df, boost::proto::child_c<3>(a0));
      BOOST_AUTO_TPL(nr, boost::proto::child_c<4>(a0));
      BOOST_AUTO_TPL(v,  boost::proto::child_c<0>(a1));
      BOOST_AUTO_TPL(mu,  boost::proto::child_c<5>(a0));
      BOOST_AUTO_TPL(xred, (x-mu(1))/mu(2));
      compute_val(p, xred, v);
      container::table<value_type> delta(of_size(extent(x)));
      delta.resize(extent(x));
      compute_delta(xred, r, df, nr, nt2::numel(p), delta);
      boost::proto::child_c<1>(a1) = delta;
    }

  };
} }


#endif

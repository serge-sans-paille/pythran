//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_EXPM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_EXPM_HPP_INCLUDED

#include <nt2/linalg/functions/expm.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/isdiagonal.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/half.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/mnorm1.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/isscalar.hpp>
#include <vector>
#include <nt2/core/utility/max_extent.hpp>
namespace nt2
{
  namespace details
  {
    template < class T > struct expm_helper
    {
      typedef table < T >      btab_t;
      typedef table < size_t > itab_t;
      static const itab_t& m_vals(const double&) {
        static const size_t m_vals_[] = {3, 5, 7, 9, 13};
        static const itab_t v( of_size(5, 1), &m_vals_[0], &m_vals_[0]+5);
        return v;
      }
      static const itab_t& m_vals(const float&) {
        static const size_t m_vals_[] = {3, 5, 7};
        static const itab_t v( of_size(3, 1), &m_vals_[0], &m_vals_[0]+3);
        return v;
      }
      static const btab_t& theta(const double&){
        static const double theta_[] = {
          1.495585217958292e-002,//  m_vals = 3
          2.539398330063230e-001,//  m_vals = 5
          9.504178996162932e-001,//  m_vals = 7
          2.097847961257068e+000,//  m_vals = 9
          5.371920351148152e+000 //  m_vals = 13
        };
        static const btab_t v( of_size(5, 1),&theta_[0], &theta_[0]+5);
        return v;
      }
      static const btab_t& theta(const float&){
        static const float theta_[] = {
          4.258730016922831e-001f, //m_vals = 3
          1.880152677804762e+000f, //m_vals = 5
          3.925724783138660e+000f  //m_vals = 7
        };
        static const btab_t v( of_size(3, 1), &theta_[0], &theta_[0]+3);
        return v;
      }

      static btab_t
      getpadecoefficients(const size_t & m)
      {
        //  getpadecoefficients coefficients of numerator p of pade approximant
        //     c = getpadecoefficients returns coefficients of numerator
        //     of [m/m] pade approximant, where m = 3,5,7,9,13.
        const T m3[] = {T(120), T(60), T(12), T(1)};
        const T m5[] = {T(30240), T(15120), T(3360), T(420), T(30), T(1)};
        const T m7[] = {T(17297280), T(8648640), T(1995840), T(277200), T(25200), T(1512), T(56), T(1)};
        const T m9[] = {T(17643225600), T(8821612800), T(2075673600), T(302702400), T(30270240),
                        T(2162160), T(110880), T(3960), T(90), T(1)};
        const T m13[] = {T(64764752532480000), T(32382376266240000), T(7771770303897600),
                         T(1187353796428800),  T(129060195264000),   T(10559470521600),
                         T(670442572800),      T(33522128640),       T(1323241920),
                         T(40840800),          T(960960),            T(16380), T(182),  T(1)};
        static btab_t v;

        switch (m)
        {
        case 3: v = btab_t(of_size(4, 1), &m3[0], &m3[0]+4); return v;
        case 5: v = btab_t(of_size(6, 1), &m5[0], &m5[0]+6); return v;
        case 7: v = btab_t(of_size(8, 1), &m7[0], &m7[0]+8); return v;
        case 9: v = btab_t(of_size(10, 1), &m9[0], &m9[0]+10); return v;
        case 13:v = btab_t(of_size(14, 1), &m13[0], &m13[0]+14); return v;
        }
        v = nt2::zeros(0, 1, meta::as_<T>()); return v;
      }

    };

    template < class xpr, class Out> void
    padeapproximantofdegree(const xpr & a, const size_t & m, Out &f)
    {
      //  padeapproximantofdegree  pade approximant to exponential.
      //     f = padeapproximantofdegree(m) is the degree m diagonal
      //     pade approximant to exp(a), where m = 3, 5, 7, 9 or 13.
      //     series are evaluated in decreasing order of powers, which is
      //     in approx. increasing order of maximum norms of the terms.

      typedef typename xpr::value_type                      value_type;
      typedef typename meta::as_real<value_type>::type          base_t;
      typedef expm_helper<base_t>                                  h_t;
      typedef table <value_type>                                 tab_t;

      size_t n = nt2::length(a);
      tab_t  c = h_t::getpadecoefficients(m);
      std::vector<tab_t> apowers(m/2+1);
      // evaluate pade approximant.
      tab_t  u = nt2::zeros(n, n, meta::as_<value_type>());
      tab_t  v = u, u1;
      switch (m)
      {
      case 3:
      case 5:
      case 7:
      case 9:
        apowers[0] = nt2::eye(n, meta::as_<value_type>());
        apowers[1] = nt2::mtimes(a, a);
        for (size_t j = 2; j < m/2+1; ++j)
        {
          apowers[j] = nt2::mtimes(apowers[j-1], apowers[1]);
        }

        for(ptrdiff_t j=m+1; j >= 2 ; j-= 2)
        {
          u = nt2::fma(c(j),apowers[j/2-1], u);
        }
        u = mtimes(a, u);
        for(ptrdiff_t j=m; j >= 1 ; j-= 2)
        {
          v = nt2::fma(c(j),apowers[(j+1)/2-1], v);
        }
        break;
      case 13:
        // for optimal evaluation need different formula for m >= 12.
        tab_t a2 = nt2::mtimes(a, a);
        tab_t a4 = nt2::mtimes(a2, a2);
        tab_t a6 = nt2::mtimes(a2, a4);
        u = mtimes(a, (mtimes(a6,(c(14)*a6 + c(12)*a4 + c(10)*a2))+
                       c(8)*a6 + c(6)*a4 + nt2::fma(c(4), a2, c(2)*nt2::eye(n, nt2::meta::as_<base_t>()))));
        v = mtimes(a6,c(13)*a6 + c(11)*a4 + c(9)*a2)
          + c(7)*a6 + c(5)*a4 + nt2::fma(c(3), a2, c(1)*nt2::eye(n, nt2::meta::as_<base_t>()));
      }
      f = nt2::linsolve((-u+v), (u+v));
    }
  }

namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::exp(a0);
    }
  };

  // expm tag only used for matrix
  template<class Domain, int N, class Expr>
  struct size_of<tag::expm_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef _2D                                                      result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(e)),
                       "expm needs a square matrix or a scalar");
      return nt2::extent(boost::proto::child_c<0>(e));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::expm_, boost::mpl::long_<1>, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename A1::value_type                                  value_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, const A1& a1) const
    {
      compute_expm(boost::proto::child_c<0>(a1), a0);
    }
  private:
    template < class T >
    BOOST_FORCEINLINE static void compute_expm(const T& a0, A0& f)
    {
      f.resize(extent(a0));
      typedef nt2::table<value_type >                   tab_t;
      typedef typename meta::as_real<value_type>::type base_t;
      typedef typename meta::as_integer<base_t>::type ibase_t;
      typedef nt2::table<base_t>                      btab_t;

      typedef details::expm_helper<base_t>                h_t;
      typedef typename h_t::itab_t                     itab_t;
      const btab_t theta = h_t::theta(base_t());
      const itab_t m_vals = h_t::m_vals(base_t());
      tab_t a = a0;
      base_t norma0 = nt2::mnorm1(a0);
      if(norma0 <= theta(end_))
      {
        // no scaling and squaring is required.
        for(size_t i = 1;  i <= nt2::numel(m_vals); ++i)
        {
          if (norma0 <= theta(i))
          {
            details::padeapproximantofdegree(a, m_vals(i), f);
            break;
          }
        }
      }
      else
      {
        norma0 /= theta(end_);
        ibase_t s;
        base_t t = nt2::frexp(norma0, s);
        s -= (t == Half<base_t>()); // adjust s if norma0/theta(end_) is a power of 2.
        a =  nt2::ldexp(a, -s);
        details::padeapproximantofdegree(a,m_vals(end_), f);
        for(ibase_t i=1; i <= s; ++i)
        {
          f =  mtimes(f, f); // squaring
        }
      }
    }
  };

} }

#endif

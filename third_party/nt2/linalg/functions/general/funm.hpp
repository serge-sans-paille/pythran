//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_FUNM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_FUNM_HPP_INCLUDED

#include <nt2/linalg/functions/funm.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/eyeminus.hpp>
#include <nt2/include/functions/factorial.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/isdiagonal.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/globalmean.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/mnorminf.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <boost/assert.hpp>

// there are many optimisations/ameliorations to be done
// -- passing parameters to functor
// -- fine tuning of types
// -- some code can be shared with logm

namespace nt2
{
  namespace ext
  {
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::funm_, tag::cpu_
                              , (A0)(A1)
                              , (unspecified_<A0>)
                                (scalar_<unspecified_<A1> >)
                              )
    {
      typedef A1 result_type;
      NT2_FUNCTOR_CALL(2)
      {
        return a0(a1, 0);
      }
    };

    // funm tag only used for functor/matrix
    template<class Domain, int N, class Expr>
    struct size_of<tag::funm_,Domain,N,Expr>
    {
      typedef _2D                                                      result_type;
      BOOST_FORCEINLINE result_type operator()(Expr& e) const
      {
        BOOST_ASSERT_MSG( issquare(boost::proto::child_c<1>(e)),
                          "funm needs a functor and scalar or a ");
        return nt2::extent(boost::proto::child_c<1>(e));
      }
    };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::funm_, boost::mpl::long_<2>, nt2::container::domain>))
                            )
  {
      typedef void                                                    result_type;
      typedef typename A0::value_type                                  value_type;
      typedef typename meta::as_real<value_type>::type                     r_type;
      typedef typename meta::as_complex<r_type>::type                   cplx_type;
      typedef typename meta::as_integer<r_type>::type                      i_type;
      typedef nt2::table<value_type >                                       tab_t;
      typedef nt2::table<r_type>                                           btab_t;
      typedef table<cplx_type>                                             ctab_t;
      typedef table<i_type>                                                itab_t;

      BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1) const
      {
        compute_funm(boost::proto::value(boost::proto::child_c<0>(a1)), boost::proto::child_c<1>(a1), a0);
      }
    private:
      template <class F, class T >
      BOOST_FORCEINLINE static void compute_funm(const F& f, const T& a0, A0& res)
      {
         r_type tol = nt2::Eps<r_type>();
         uint32_t maxterms = 250;
         //u, t and r are complex arrays
         res.resize(extent(a0));
         ctab_t u, t;
         nt2::tie(u, t) = schur(a0, nt2::cmplx_);
         if (isdiagonal(t))
         {
           t = nt2::from_diag(f(nt2::diag_of(t), 0));
           BOOST_AUTO_TPL(r, nt2::mtimes(u, nt2::mtimes(t, nt2::trans(nt2::conj(u)))));
           transtype(res, r, typename nt2::meta::is_complex<value_type>::type());
           return;
         }
         else
         {
           ctab_t r = zeros(extent(a0), meta::as_<cplx_type>()); //is it necessary ?
           r_type delta = 0.1;
           itab_t  ord(nt2::of_size(2u, nt2::size(a0,1)));
           blocking(diag_of(t),delta, ord);
           uint32_t lord = nt2::size(ord, 2);
           ctab_t ca0 = a0;

           for(uint32_t col=1; col <= lord ; ++col)
           {
             BOOST_AUTO_TPL(j, nt2::_(ord(1, col), ord(2, col)));

             itab_t terms(nt2::of_size(1, lord));
             uint32_t nj =  length(j);
             ctab_t rj(nt2::of_size(nj, nj));
             terms(col) = funm_atom(f, a0(j, j), tol, maxterms, rj);
             r(j, j) = rj;
             for(uint32_t row=col-1; row >= 1; --row)
             {
               BOOST_AUTO_TPL(i, nt2::_(ord(1, row), ord(2, row)));
               if (length(i) == 1 && length(j) == 1)
               {
                 size_t ii = i(1), jj = j(1);
                 BOOST_AUTO_TPL(k, nt2::_(ii+1, jj-1));
                 cplx_type temp = ca0(ii,jj)*(r(ii,ii) - r(jj,jj));
                 if (!isempty(k)) temp += mtimes(r(ii,k), ca0(k,jj)) - mtimes(ca0(ii,k), r(k,jj));
                 r(ii,jj) = temp/(ca0(ii,ii)-ca0(jj,jj));
               }
               else
               {
                 itab_t k(nt2::of_size(1, 0));
                 for(uint32_t l = row+1; l < col; ++l)
                 {
                   itab_t k1 = horzcat(k, nt2::_(ord(1, l), ord(2, l)));
                   k = k1;
                 }
                 ctab_t rhs =  mtimes(r(i,i), ca0(i,j)) - mtimes(ca0(i,j), r(j,j));
                 if(!isempty(k)) rhs += mtimes(r(i,k), ca0(k,j)) -  mtimes(ca0(i,k), r(k,j));
                 r(i,j) = sylv_tri(ca0(i,i),-ca0(j,j),rhs);
               }
             }
             ctab_t z =  mtimes(mtimes(u, r), trans(conj(u)));
             transtype(res, z, typename nt2::meta::is_complex<value_type>::type());
           }
         }
       }

      template <class F, class X, class N> static inline
        cplx_type feval(const F & f, const X& x,  const N& k)
      {
        ctab_t xx = x;
        return f(xx, k);
      }

      template < class F, class D1, class D2> static inline
      int32_t funm_atom(const F& f, const D1& t,
                        const r_type& tol,
                        const uint32_t& maxterms,
                        D2& rj)
      {
        // Function of triangular matrix with nearly constant diagonal.
        //   n_terms = funm_atom(f, a0, tol, maxterms, fa0)
        //   evaluates function f at the upper triangular matrix t,
        //   where t has nearly constant diagonal.
        //   a taylor series is used, taking at most maxterms terms.
        //   the function represented by f must have a taylor series with an
        //   infinite radius of convergence.
        //   f(x,k) must return the k'th derivative of
        //   the function represented by fun evaluated at the vector x.
        //   tol is a convergence tolerance for the taylor series, defaulting to eps.
        //   if prnt ~= 0 information is printed on the convergence of the
        //   taylor series evaluation.
        //   n_terms is the number of terms taken in the taylor series.
        //   n_terms  = -1 signals lack of convergence.

        uint32_t n = length(t);
        if (n == 1)
        {
          rj = f(t, 0);
          return 1;
        }
        cplx_type lambda = nt2::globalmean(diag_of(t));
        rj = feval(f, lambda,0)*eye(n, meta::as_<cplx_type>());
        btab_t f_deriv_max = zeros(maxterms+n-1,1, meta::as_<r_type>());
        ctab_t nn = t - lambda*eye(n, meta::as_<cplx_type>());
        r_type mu = mnorminf(linsolve(eyeminus(nt2::abs(triu(t,1))), nt2::ones(n,1, meta::as_<r_type>())));
        ctab_t p = nn;
        uint32_t max_d = 1;
        for(uint32_t k = 1; k <= maxterms; ++k)
        {
          cplx_type fval = feval(f, lambda,k);
          BOOST_ASSERT_MSG(is_finite(fval), "funm infinite derivative");
          ctab_t rj_old = rj;
          rj+= p*fval;
          r_type  rel_diff = nt2::mnorminf(rj - rj_old)/(tol+mnorminf(rj_old));
          p = mtimes(p, nn)/r_type(oneplus(k));
          if (rel_diff <= tol)
          {
            // Approximate the maximum of derivatives in convex set containing
            // eigenvalues by maximum of derivatives at eigenvalues.
            for(uint32_t j = max_d; j <=  k+n-1; ++j)
            {
              f_deriv_max(j) = nt2::mnorminf(f(nt2::diag_of(t),j));
            }
            max_d = k+n;
            r_type omega = nt2::Zero<r_type>();
            for(uint32_t j = 0; j <= n-1; ++j)
            {
              omega = nt2::max(omega,f_deriv_max(k+j)/nt2::factorial(j));
            }
            r_type trunc = nt2::mnorminf(p)*mu*omega;
            if (trunc <= tol*mnorminf(rj))
            {
              return k+1;
            }
          }
        }
        return -1;
      }

      template < class T1, class T2 >
      BOOST_FORCEINLINE static void transtype(T1& r, T2& z, boost::mpl::false_ const &)
      {
        r =  real(z);
      }

      template < class T1, class T2 >
        BOOST_FORCEINLINE static void transtype(T1& r, T2& z, boost::mpl::true_ const &)
      {
        r =  z;
      }
      template < class D> static inline void blocking(const D& a0, const r_type& delta, itab_t & ord)
      {
        uint32_t n = nt2::size(a0, 1);
        uint32_t j = 1;
        ord(1, 1) = 1;
        for(uint32_t i=2; i <= n; ++i)
        {
          if (nt2::abs(a0(i-1)-a0(i)) >= delta)
          {
            ord(2, j) = i-1;
            ord(1, ++j) = i;
          }
        }
        ord(2, j) = n;
        ord.resize(nt2::of_size(2u, j));
      }
      template < class T, class U, class B>
        static inline ctab_t sylv_tri(const T& t,const U& u, const B& b)
      {

        // sylv_tri    solve triangular sylvester equation.
        //    x = sylv_tri(t,u,b) solves the sylvester equation
        //  t*x + x*u = b, where t and u are square upper triangular matrices.

        uint32_t m = length(t);
        uint32_t n = length(u);
        ctab_t x = zeros(m,n, nt2::meta::as_<cplx_type>());
        for(uint32_t i = 1;  i <= n; ++i)
        {
          ctab_t bb = b(nt2::_,i);
          BOOST_AUTO_TPL(ii, nt2::_(1u, i-1));
          if(!isempty(ii)) bb -= mtimes(x(nt2::_,ii),u(ii,i));
          x(nt2::_,i) = linsolve(t + u(i,i)*eye(m, meta::as_<cplx_type>()),
                                 bb);
        }
        return x;
     }
    };

  }
}

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_FUNCTIONS_DETAILS_LEV_IMPL_HPP_INCLUDED
#define NT2_OPTIMIZATION_FUNCTIONS_DETAILS_LEV_IMPL_HPP_INCLUDED
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/optimization/options.hpp>

namespace nt2 { namespace details
{
  template<class T,  typename FLOAT = typename T::value_type >
  class lev_impl
  {
    // sum(fvec^2) is minimized.
  public :

    typedef FLOAT                     float_t;
    typedef ptrdiff_t bool_t;
    typedef T                         array_t;
    typedef nt2::container::table<FLOAT>         table_t;
    typedef nt2::container::table<bool_t>       btable_t;
    typedef details::optimization_settings<float_t>   otype;
    lev_impl() : iterdone(0), pa(0), pia(0), opt(0){}
    ~lev_impl() {}

    template < class FUNC>
    void optimize( const FUNC& crit,
                   array_t& aa,           //unkowns init values
                   const btable_t& ba,    //unknows to optimize
                   const otype & o);        //options

    size_t          nbiteration()  const { return iterdone;  }
    float_t         lastchi2()     const { return chisq;     }
    const table_t&  covariance()   const { return covar;     }
    bool            convok()       const { return res;       }

  private :
    template < class FUNC > void mrqcoef(const FUNC& crit, array_t& aa,array_t& al,array_t& be);
    template < class FUNC > void fdjac  (const FUNC& crit, array_t& a);
    template < class FUNC > bool mrqmin (const FUNC& crit);
    void compcov();

    float_t                                   chisq, lambda;
    bool                                                res;
    array_t      fvec,covar,df,sig,alpha,atry,da,beta,oneda;
    size_t                          iterdone,iterindex,mfit;
    array_t*                                             pa;
    const btable_t*                                     pia;
    const otype*                                        opt;
  };

  template<class T, class FLOAT>
  template < class FUNC >
  void lev_impl<T, FLOAT>::fdjac( const FUNC& crit, T& a )
  {
    const float_t eps = Sqrteps<float_t>();
    const size_t nfvec = numel(fvec);
    array_t f( nt2::of_size(nfvec, 1));
    df.resize( nt2::of_size(nfvec, numel(a)));
    for(size_t j = 1; j <= numel(a); ++j)
      {
        if((*pia)(j))
        {
          float_t temp =  a(j);
          float_t h =  eps*nt2::abs(temp);
          if (h == 0.0) h = eps;
          a(j) = temp+h;
          h =  a(j)-temp;
          f = crit(a);
          df(_, j) = (f(_)-fvec(_))/h;
          a(j) = temp;
        }
        else
        {
          df(_, j) = Zero<float_t>();
        }
      }
  }

  template<typename T, typename FLOAT>
  template < class FUNC>
  void lev_impl<T, FLOAT>::optimize( const FUNC& crit, T &aa,
                                     const btable_t & ba,
                                     const otype& o)
  {
    iterindex = 0;
    iterdone = 0;
    opt = &o;
    pa = &aa;
    pia = &ba;
    lambda =  Mone<float_t>();
    mfit =  inbtrue(ba)(1);            // TO FIX
//     mfit = 0;

//     for(size_t i = 0;i < numel(ba); i++)
//       {
//         mfit+= ba(i);
//       }

    atry = zeros(numel(aa), 1, meta::as_<float_t>());
    da =   zeros(numel(aa), 1, meta::as_<float_t>());
    beta = zeros(mfit, 1, meta::as_<float_t>());
    oneda= zeros(mfit, 1, meta::as_<float_t>());
    chisq =  Mone<float_t>();

    fvec = crit(aa);
    for(size_t i = 1; i <= o.maximum_iterations; ++i)
    {
      iterdone = i;
      if(mrqmin(crit))
        break;
      else if(i == o.maximum_iterations)
        BOOST_ASSERT_MSG(false, "levenberg was not convergent");
    }
    lambda =  Zero<float_t>();
    mrqmin(crit);
    fvec = crit(aa);
  }

  template<typename T, typename FLOAT>
  template < class FUNC >
  void lev_impl<T, FLOAT>::mrqcoef( const FUNC & crit, T &a,T & alph,T &bet)
  {
    const btable_t& ia = *pia;
    size_t na = numel(a);
    alph = nt2::zeros(nt2::of_size(na, na), meta::as_<float_t>());
    bet =  zeros(nt2::of_size(na, 1), meta::as_<float_t>());
    chisq =  Zero<float_t>();
    fvec = crit(a);
    fdjac(crit,a);

    for(size_t i = 1; i <= numel(fvec); ++i)
    {
      float_t sig2i =  nt2::numel(sig) ? nt2::rec(nt2::sqr(sig(i))) : One<float_t>();
      float_t dy = fvec(i);
      for(size_t j = 0, l = 1; l <= na ; l++)
      {
        if(ia(l))
        {
          ++j;
          float_t wt = df(i, l)*sig2i;
          for(size_t k = 0, m = 1; m <= l; m++)
          {
            if(ia(m))
            {
              ++k;
              alph(j, k) += wt*df(i, m);
            }
          }
          bet(j)-= dy*wt;
        }
      }
      chisq += nt2::sqr(dy)*sig2i;
    }

    for(size_t j = 2; j <= mfit; ++j)
    {
      for(size_t k = 1; k < j; ++k)
      {
        alph(k, j) = alph(j, k);
      }
    }
  }

  template<class T, typename FLOAT>
  void lev_impl<T, FLOAT>::compcov()
  {
    const btable_t & ia = *pia;
    size_t ma = nt2::numel(ia);
    array_t tmp0 = nt2::expand(covar, ma, ma);
    covar = tmp0; //ALIASING
    for(size_t j = ma, k = mfit; j ; --j)
    {
      if (ia(j))
      {
        float_t tmp;
        for(size_t i = 1; i <= ma; ++i)
        {
          tmp = covar(i, j) ;
          covar(i, j) = covar(i, k);
          covar(i, k) = tmp;
          //        nt2::swap(covar(i, k), covar(i, j)); swapline ?
        }

        for(size_t i = 1; i <= ma; ++i)
        {
          tmp = covar(j, i) ;
          covar(j, i) = covar(k, i);
          covar(k, i) = tmp;
          //        nt2::swap(covar(k, i), covar(j, i)); swapcol ?
        }
        --k;
      }
    }

    float_t fsig =  chisq/(nt2::numel(fvec)-mfit);
    covar *=  fsig;
  }

  template<typename T, typename FLOAT>
  template < class FUNC >
  bool lev_impl<T, FLOAT>::mrqmin( const FUNC & crit )
  {
    static float_t ochisq;
    table_t & a = *pa;
    const btable_t & ia = *pia;
    if (lambda <  float_t(0.0))
    {
      lambda = float_t(0.001);
      mrqcoef(crit,a,alpha,beta);
      ochisq =  chisq;
      atry = a;
    }

    covar = alpha(_(1, mfit),_(1, mfit)) ;
    oneda = beta(_(1, mfit));

    for(size_t j = 1; j <= mfit; j++ ) covar(j, j) *= nt2::oneplus(lambda);
    da = nt2::linsolve(covar, nt2::colvect(oneda));
    if (lambda == float_t(0.0))
    {
      if (numel(fvec) > mfit) compcov();
      return true;
    }
    size_t j = 0;

    for( size_t l = 1; l <= numel(a); l++)
    {
      if (ia(l))
      {
        atry(l) = a(l)+da(++j);
      }
    }

    mrqcoef(crit,atry, covar, da);

    if (chisq <=  ochisq)
    {
      res = (ochisq-chisq <= nt2::sqr(opt->absolute_tolerance)) ||
        (ochisq-chisq <= nt2::sqr(opt->relative_tolerance*chisq));
      lambda *=  Oneo_10<float_t>();
      ochisq = chisq;
      alpha = covar;
      beta = da;
      a =  atry;
      return res;
    }
    else
    {
      lambda *= Ten<float_t>();
      chisq =  ochisq;
      return false;
    }
  }
} }

#endif

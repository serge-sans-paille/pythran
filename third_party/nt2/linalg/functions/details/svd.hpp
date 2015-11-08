//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_DETAILS_SVD_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_DETAILS_SVD_HPP_INCLUDED

#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/lapack/gesvd.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/core/container/table/table.hpp>

// TODO:
// these are the kind of syntaxes to be enforced by nt2::chol
//  svd    Singular value decomposition.
//     [u,s,v] = svd(x) produces a diagonal matrix s, of the same
//     dimension as x and with nonnegative diagonal elements in
//     decreasing order, and unitary matrices u and v so that
//     x = u*s*v'.
// -> [u w v ]

//     s = svd(x) returns a vector containing the singular values.

//     [u,s,v] = svd(x,0) produces the "economy size"
//     decomposition. if x is m-by-n with m > n, then only the
//     first n columns of u are computed and s is n-by-n.
//     for m <= n, svd(x,0) is equivalent to svd(x).
// -> [u w v ] jobu ==  'o', jobvt ==  'a'

//     [u,s,v] = svd(x,'econ') also produces the "economy size"
//     decomposition. if x is m-by-n with m >= n, then it is
//     equivalent to svd(x,0). for m < n, only the first m columns
//     of v are computed and s is m-by-m.
// -> [u w v ] jobu ==  'a' jobvt ==  'o'

////////////////////////////////////////////////////////////////////////////////////////
// The class provides:
// constructor from an expression or matrix a
//
// accesors to u, v, vt and singular also w as a vector
// u returns the left singular vectors
// v returns the right singular vectors
// vt returns the transpose of the right singular vectors
// w returns the diagonal matrix of the singular values
// singular returns the vector of the singular values
// we have u*w*vt = a

///////////////////////////////////////////////////
//
// the class allow to compute
//
// status the plu status from lapack
//
// rank the matrix rank up to epsi
//
//
// Two solvers
// solve and inplace_solve
//
// a matrix pseudo inversion penrose pseudo inverse
// pinv
// if z =  a.pinv(),  one has z*a*z = z and a*z*a = a
//
// null returns orthogonal basis of the kernel of the input up to epsi
// orth returns orthogonal basis of the image  of the input up to epsi
// zerosolve returns the a norm one  vector such that ||a*x|| is minimal
// (zero if a is singular)
//

namespace nt2 { namespace details
{
  template<class T> struct svd_result
  {
    typedef typename meta::strip<T>::type                   source_t;
    typedef typename source_t::value_type                     type_t;
    typedef typename meta::as_integer<type_t, signed>::type  itype_t;
    typedef typename source_t::index_type                    index_t;
    typedef typename meta::as_real<type_t>::type              base_t;
    typedef T                                                 data_t;
    typedef nt2::container::table<type_t,nt2::_2D>             tab_t;
    typedef nt2::container::table<base_t,nt2::_2D>            btab_t;
    typedef nt2::container::table<itype_t,nt2::_2D>           itab_t;
    typedef nt2::details::workspace<type_t>              workspace_t;
    typedef nt2::container::table<nt2_la_int,nt2::_2D>        ibuf_t;
    typedef nt2::container::table<type_t,index_t>        result_type;

    template<class Input>
    svd_result ( Input& xpr, char jobu, char jobvt)
      : jobu_(jobu)
      , jobvt_(jobvt)
      , a_(xpr)
      , aa_(xpr)
      , m_( nt2::height(xpr) )
      , n_( nt2::width(xpr)  )
      , lda_( a_.leading_size() )
      , info_(0)
    {
      BOOST_ASSERT_MSG((jobvt_ != 'O' || jobu_ != 'O'),
                        "jobu and jobvt cannot be 'O' simultaneously");
      ldu_  = (jobu_== 'N') ? 1 : m_;
      ucol_ = (jobu_== 'S'||jobu_== 'O') ? nt2::min(n_, m_) : ((jobu_== 'N') ? 1 : m_);

      vtcol_  = (jobvt_== 'N') ? 1 : n_;
      ldvt_   = (jobvt_== 'S'||jobvt_== 'O') ? nt2::min(n_, m_) : ((jobvt_== 'N') ? 1 : n_);
      u_.resize(of_size(ldu_, ucol_));
      ldu_ = u_.leading_size();
      vt_.resize(of_size(ldvt_, vtcol_));
      ldvt_ = vt_.leading_size();
      w_.resize(of_size(nt2::min(n_, m_), 1));
      nt2::details::gesvd(&jobu_, &jobvt_, &m_, &n_, aa_.raw(), &lda_,
                          w_.raw(), u_.raw(), &ldu_,
                          vt_.raw(), &ldvt_, &info_, wrk_);
    }

    svd_result& operator=(svd_result const& src)
    {
      jobu_   = src.jobu_;
      jobvt_  = src.jobvt_;
      a_      = src.a_;
      aa_     = src.aa_;
      m_      = src.m_;
      n_      = src.n_;
      lda_    = src.lda_;
      info_   = src.info_;
      wrk_    = src.wrk_;
      return *this;
    }


    svd_result(svd_result const& src)
     :jobu_(src.jobu_),jobvt_(src.jobvt_),
      a_(src.a_),aa_(src.aa_),m_(src.m_),n_(src.n_),
      lda_(src.lda_),info_(src.info_),wrk_(src.wrk_)
    {}

    //==========================================================================
    // Return raw values
    //==========================================================================
    data_t values() const { return aa_; }

    //==========================================================================
    // Return u part
    //==========================================================================
    // making jobs static will allow improved return type and no spurious copy
    result_type u() const
    {
      BOOST_ASSERT_MSG(jobu_ != 'N', "please call svd with jobu = 'A', 'S' or 'O'");
      if (jobu_ == 'O')
        return expand(aa_, min(m_, n_), n_);
      else
        return u_;
    }

    //==========================================================================
    // Return v part
    //==========================================================================
    // making jobs static will allow improved return and no spurious copy
    result_type v() const {
      result_type z;
      BOOST_ASSERT_MSG(jobvt_ != 'N', "please call svd with jobvt= 'A', 'S' or 'O'");
      if (jobvt_ == 'O')
        z = trans(expand(aa_, min(m_, n_), n_));
      else
        z = trans(vt_);
      return z;
    }

    //==========================================================================
    // Return vt part
    //==========================================================================
    // making jobs static will allow improved return and no spurious copy
    result_type vt() const {
      BOOST_ASSERT_MSG(jobvt_ != 'N', "please call svd wit jobz = 'A', 'S' or 'O'");
       if (jobvt_ == 'O')
        return expand(aa_, min(m_, n_), n_);
      else
        return vt_;
    }

    //==========================================================================
    // Return singular values as a vector
    //==========================================================================
    const btab_t&      singular()const { return w_; }

    //==========================================================================
    // Return singular values as a diagonal matrix
    //==========================================================================
    typedef typename meta::call < tag::from_diag_(btab_t)>::type                                   u_T0;
    typedef typename meta::call < tag::expand_(u_T0, nt2_la_int, nt2_la_int)>::type            w_result;

    w_result     w()              const
    {
      nt2_la_int h = height(vt_);
      return nt2::expand(from_diag(w_), ucol_, h);
    }

    //==========================================================================
    // Return lapack status
    //==========================================================================
    nt2_la_int  status()         const { return info_; }

    //==========================================================================
    // Return matrix condition number
    //==========================================================================
    base_t     cond()       const
    {
      base_t r =  w_(1)/w_(nt2::min(m_, n_));
      return is_nan(r) ? Inf<base_t>() : r;
    }

    //==========================================================================
    // Return matrix norm
    //==========================================================================
    base_t     norm()       const { return  w_(1); }

    //==========================================================================
    // Return matrix norm
    //==========================================================================
    base_t     norminv()       const { return  nt2::rec(w_(nt2::min(m_, n_))); }

    //==========================================================================
    // Return matrix rank up to epsi
    //==========================================================================
     size_t      rank(base_t epsi = -1) const
    {
      epsi =  (epsi < 0) ?  nt2::max(n_, m_)*nt2::eps(w_(1)): epsi;
//       size_t r = 0;
//       for(int i=1; i <= numel(w_); ++i)
//         {
//           if (w_(i) > epsi)
//             ++r;
//           else
//             return r;
//         }
//       return r;
      return  size_t(sum(if_one_else_zero(gt(w_, epsi))(_)));
    }

    //==========================================================================
    // Solver interface
    // The default solver is not in place
    //==========================================================================
    template<class XPR> void inplace_solve(XPR& b ) const
    {
      b = solve(b);
    }

    template<class XPR> result_type solve(const XPR & b,
                                          base_t epsi = Mone<base_t>() )const{
      epsi =  epsi < 0 ? nt2::eps(w_(1)) : epsi;
      tab_t w1 = nt2::if_else( gt(w_, length(a_)*epsi), nt2::rec(w_), Zero<base_t>());
      return mtimes(trans(vt_), mtimes(from_diag(w1), mtimes(trans(u_), b)));
      }

    //==========================================================================
    // null space basis up to epsi
    //==========================================================================
      tab_t null(base_t epsi = -1 )const
      {
        epsi =  epsi < 0 ? nt2::eps(w_(1)) : epsi;
        int j = numel(w_);
        for(; (j > 0) && (w_(j)<= epsi); j--);
        j++;
        return nt2::fliplr(trans(vt()(_(j, last_index<1>(vt_)), _)));
      }

    //==========================================================================
    // image space basis up to epsi
    //==========================================================================
//     typedef typename meta::call<tag::colon_(size_t, size_t)>::type T1;
//     typedef typename meta::call<tag::function_(tab_t, container::colon_, T1)>::type T2;
      tab_t orth(base_t epsi =  -1)const
      {
        size_t r = rank(epsi);
        return u()(_, _(One<size_t>(), r));
      }

      tab_t zerosolve()const
      {
        return trans(vt()(last_index<1>(vt_), _));
      }

      tab_t pinv(base_t epsi = -1 )const
      {
        epsi = (epsi < 0 ? nt2::eps(w_(1)) : epsi)*length(a_);
        tab_t w1 = nt2::if_else( nt2::gt(w_, epsi), nt2::rec(w_), nt2::Zero<base_t>());
        tab_t pinv__ = mtimes(trans(conj(vt_)), mtimes(from_diag(w1), trans(conj(u_))));
        return pinv__;
      }

  private:
    char                           jobu_;
    char                          jobvt_;
    data_t                            a_;
    tab_t                            aa_;
    tab_t                             u_;
    tab_t                            vt_;
    btab_t                            w_;
    nt2_la_int                     m_,n_;
    nt2_la_int                      lda_;
    nt2_la_int                      ldu_;
    nt2_la_int                     ldvt_;
    nt2_la_int                     ucol_;
    nt2_la_int                    vtcol_;
    nt2_la_int                     info_;
    workspace_t                     wrk_;
  };
} }

#endif

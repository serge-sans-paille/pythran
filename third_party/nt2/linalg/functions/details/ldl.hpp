//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_DETAILS_LDL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_DETAILS_LDL_HPP_INCLUDED

#include <nt2/include/functions/tri1l.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/options.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/lapack/hstrf.hpp>
#include <nt2/core/container/table/table.hpp>

// TODO:
// these are the kind of syntaxes to be enforced by nt2::chol
//  ldl     ldl factorization.
//     [l,u] = ldl(a) stores an upper triangular matrix in u and a
//     "psychologically lower triangular matrix" (i.e. a product of lower
//     triangular and permutation matrices) in l, so that a = l*u. a can be
//     rectangular.
// -> {pl, u]

//     [l,u,p] = ldl(a) returns unit lower triangular matrix l, upper
//     triangular matrix u, and permutation matrix p so that p*a = l*u.
// -> {l, u, p]

//     [l,u,p] = ldl(a,'vector') returns the permutation information as a
//     vector instead of a matrix.  that is, p is a row vector such that
//     a(p,:) = l*u.  similarly, [l,u,p] = ldl(a,'matrix') returns a
//     permutation matrix p.  this is the default behavior.
// -> {l, u, ip]

////////////////////////////////////////////////////////////////////////////////////////
// The class provides:
// constructor from an expression or matrix a
//
// accesors to l, u, p, pl and ip
//
// l is lower unittriangular part of ldl_
// u is upper triangular part of ldl_
// p is a permutation matrix
// pl is l permuted by p
// ip is the permutation index vector defining p
// we have l*u =  p*a
//         pl*u =  a
/////////////////////////////////////////////////// TODO  perhaps l and u could return an expresiion rather than a matrix
//
// the class allow to compute
//
// status the pldl status from lapack
//
// rank the matrix rank
//
// When a is square
// det and absdet determinant and absoldlte valdle of the determinant
// They have two syntaxes
//  1 - d =  f.det()   or d =  f.absdet()
//  2 - m =  f.det(e)  or m =  f.absdet(e)
// In the second case m is a mantissa and e and exponent
// If there is no overflow or undeflow in e the determinant is then equal to ldexp(m, e)
//
// rcond the reciprocal condition number of a
//
// Two solvers
// solve and inplace_solve
//
// a matrix inversion
// inv
// inv() can emit a warning if rcond is bad
// inv(false) never warns
//     please avoid using inv if you need not the inverse coefficients.

namespace nt2 { namespace details
{
  template<class T> struct ldl_result
  {
    typedef typename meta::strip<T>::type                   source_t;
    typedef typename source_t::value_type                     type_t;
    typedef typename meta::as_integer<type_t, signed>::type  itype_t;
    typedef typename source_t::index_type                    index_t;
    typedef typename meta::as_real<type_t>::type              base_t;
    typedef T                                                 data_t;
    typedef nt2::table<type_t,nt2::matlab_index_>              tab_t;
    typedef nt2::table<base_t,nt2::matlab_index_>             btab_t;
    typedef nt2::table<itype_t,nt2::matlab_index_>            itab_t;
    typedef nt2::details::workspace<type_t>              workspace_t;
    typedef nt2::table<nt2_la_int,nt2::matlab_index_>         ibuf_t;
    typedef nt2::table<type_t,index_t>                   result_type;

    template<class Input>
    ldl_result ( char uplo/* = 'U'*/
               , Input& xpr
               , typename boost::
                 disable_if_c<boost::is_same<ldl_result,Input>::value>::type* = 0
      )
      : uplo_(uplo == 'L' ? 'L':'U')
      , a_(xpr)
      , ldl_(xpr)
      , n_( nt2::width(xpr)  )
      , ldldl_( ldl_.leading_size() )
      , ipiv_(nt2::of_size(n_, 1))
      , info_(0)
      , p_(of_size(0, 1))
      , ip_(of_size(0, 1))
      , pl_(of_size(0, 1))
      , invt_(of_size(0, 1))
    {
      nt2::details::hstrf(&uplo_, &n_, ldl_.raw(), &ldldl_, ipiv_.raw(), &info_, w_);
    }

    ldl_result(ldl_result const& src)
      : uplo_(src.uplo_), a_(src.a_) , ldl_(src.ldl_), n_( src.n_ )
      , ldldl_( src.ldldl_ ) , ipiv_(src.ipiv_)
      , info_(src.info_) , w_(src.w_)
      , p_(src.p_), ip_(src.ip_), pl_(src.pl_), invt_(src.invt_)
    {}

    ldl_result& operator=(ldl_result const& src)
    {
      uplo_   = src.uplo;
      a_      = src.a_;
      ldl_    = src.ldl_;
      n_      = src.n_;
      ldldl_  = src.ldldl_;
      ipiv_   = src.ipiv_;
      info_   = src.info_;
      w_      = src.w_;
      p_      = src.p_;
      ip_     = src.ip_;
      pl_     = src.pl_;
      invt_   = src.invt_;
      return *this;
    }

    //==========================================================================
    // Return raw result values
    //==========================================================================
    const tab_t& values() const { return ldl_; }

    //==========================================================================
    // Return raw values
    //==========================================================================
    const tab_t original() const { return a_; }

    //==========================================================================
    // Return ipiv values
    //==========================================================================
    const ibuf_t& ipiv() const { return ipiv_; }
    //==========================================================================
    // Return l values
    //==========================================================================
    typedef typename meta::call < tag::tri1l_(tab_t const &)>::type   u_result;
    const u_result l() const { return nt2::tri1l(ldl_); }

    //==========================================================================
    // Return post-computation status
    //==========================================================================
    nt2_la_int  status() const { return info_; }

  private:
    char                           uplo_;
    data_t                            a_;
    tab_t                           ldl_;
    nt2_la_int                        n_;
    nt2_la_int                    ldldl_;
    ibuf_t                         ipiv_;
    base_t                           rc_;
    nt2_la_int                     info_;
    workspace_t                       w_;
    tab_t                             p_;
    itab_t                           ip_;
    tab_t                            pl_;
    tab_t                          invt_;
  };
} }

#endif

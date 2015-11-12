//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_TOEPLITZ_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_TOEPLITZ_HPP_INCLUDED
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/ric.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/conj.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::toeplitz_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                     result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      out.resize(extent(in));
      prepare(out, in, N());
      return out;
    }
  private:
    static void prepare(A0& out, const A1& in,  boost::mpl::long_<1> const &)
    {
      BOOST_AUTO_TPL(c0, nt2::colvect(boost::proto::child_c<0>(in)));
      BOOST_AUTO_TPL(r,  nt2::catv(nt2::conj(c0(1)), c0(_(2, end_))));
      BOOST_AUTO_TPL(c,  nt2::conj(r));
      compute(out, c, r);
    }
    static void prepare(A0& out, const A1& in,  boost::mpl::long_<2> const &)
    {
      BOOST_AUTO_TPL(c,  nt2::colvect(boost::proto::child_c<0>(in)));
      BOOST_AUTO_TPL(r,  nt2::colvect(boost::proto::child_c<1>(in)));
      compute(out, c, r);
    }
    template < class C, class R > //real toeplitz
    static void compute(A0& out,const C& c, const R& r)
    {
      size_t p = numel(r);
      size_t m = numel(c);
      BOOST_AUTO_TPL(idx, nt2::_(ptrdiff_t(p), ptrdiff_t(-1), ptrdiff_t(2)));
      BOOST_AUTO_TPL(ridx, nt2::colvect(r(idx)));
      BOOST_AUTO_TPL(x, catv(ridx, c)); //build vector of user data
      BOOST_AUTO_TPL(v1, nt2::fliplr(nt2::cif(m, p, meta::as_<ptrdiff_t>())));
      BOOST_AUTO_TPL(v2, nt2::ric(m, p, meta::as_<ptrdiff_t>()));
      out(nt2::_) = x(v1+v2);
    }
  };
//   function t = toeplitz(c,r)
// %TOEPLITZ Toeplitz matrix.
// %   TOEPLITZ(C,R) is a non-symmetric Toeplitz matrix having C as its
// %   first column and R as its first row.
// %
// %   TOEPLITZ(R) is a symmetric Toeplitz matrix for real R.
// %   For a complex vector R with a real first element, T = toeplitz(r)
// %   returns the Hermitian Toeplitz matrix formed from R. When the
// %   first element of R is not real, the resulting matrix is Hermitian
// %   off the main diagonal, i.e., T_{i,j} = conj(T_{j,i}) for i ~= j.
// %
// %   Class support for inputs C,R:
// %      float: double, single
// %
// %   See also HANKEL.

// %   Revised 10-8-92, LS - code from A.K. Booer.
// %   Copyright 1984-2010 The MathWorks, Inc.
// %   $Revision: 5.11.4.5 $  $Date: 2010/11/22 02:46:02 $

// if nargin < 2,
//   c(1) = conj(c(1)); r = c; c = conj(c); % set up for Hermitian Toeplitz
// else
//   if r(1) ~= c(1)
//     warning(message('MATLAB:toeplitz:DiagonalConflict'))
//   end
// end
// %
// r = r(:);                               % force column structure
// p = length(r);
// m = length(c);
// x = [r(p:-1:2) ; c(:)];                 % build vector of user data
// xclass = class(x);
// cidx = (zeros(xclass):m-1)';
// ridx = p:-1:ones(xclass);
// t = cidx(:,ones(p,1)) + ridx(ones(m,1),:);  % Toeplitz subscripts
// t(:) = x(t);                                   % actual data


} }


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of toeplitz.hpp
// /////////////////////////////////////////////////////////////////////////////

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_SPLIT_HPP_INCLUDED
#define NT2_INTEGRATION_SPLIT_HPP_INCLUDED
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/include/functions/findi.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/globalasum1.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/isscalar.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/table.hpp>

namespace nt2
{
  namespace details
  {
    //Put the way points points in increasing split
    // wpts is a row vector of real already sorted
    template < class X, class XX, class L>
    static inline void split(const X& x, size_t minsubs, XX& xx, L & pathlen)
    {
      //  Split subintervals in the interval vector X so that, to working
      //  precision, no subinterval is longer than 1/minsubs times the
      //  total path length. Removes subintervals of zero length, except
      //  that the resulting X will always has at least two elements on
      //  return, i.e., if the total path length is zero, X will be
      //  collapsed into a single interval of zero length.  Also returns
      //  the integration path length.
      typedef typename X::value_type                         itype_t;
      typedef typename container::table<itype_t>              itab_t;
      typedef typename meta::as_real<itype_t>::type          rtype_t;
      typedef typename container::table<rtype_t>              rtab_t;
      typedef typename container::table<ptrdiff_t>            ptab_t;
      rtab_t absdx = nt2::abs(nt2::diff(x));
      pathlen = nt2::globalasum1(absdx);
      xx = x;
      if (pathlen > 0)
      {
        rtype_t udelta = minsubs/pathlen;
        rtab_t tmp_nnew =  nt2::minusone(nt2::ceil(absdx*udelta));
        //BOOST_AUTO_TPL(tmp_nnew, nt2::minusone(nt2::ceil(absdx*udelta)));
        ptab_t idxnew = nt2::rowvect(nt2::find(is_gtz(tmp_nnew)));
        rtab_t nnew = tmp_nnew(idxnew);
        for (size_t j = nt2::numel(idxnew); j >= 1; --j)
        {
          ptrdiff_t k = idxnew(j);
          rtype_t nnj = nnew(j);
          //Calculate new points.
          itab_t  newpts =  x(k)+(nt2::_(One<rtype_t>(), nnj)/oneplus(nnj))*(x(k+1)-x(k));
          //          newpts = newpts+x(k);
          // Insert the new points.
          itab_t xx1 = nt2::cath(nt2::cath(xx(nt2::_(begin_, k)),newpts),xx(nt2::_(k+1, end_)));
          xx =  xx1;
        }
      }
      // Remove useless subintervals.
      itab_t xx1 = xx(nt2::cath(nt2::One<ptrdiff_t>(), nt2::oneplus(nt2::rowvect(nt2::find(nt2::is_nez(nt2::diff(xx)))))));
      if (nt2::isscalar(xx1))
        xx = nt2::repnum(xx(begin_), 2, 1);
      else
        xx =  xx1;
    }
  }
}


#endif

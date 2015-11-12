//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_DETAILS_RREF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_DETAILS_RREF_HPP_INCLUDED

#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/mnorminf.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <nt2/core/container/table/table.hpp>
//  rref   reduced row echelon form.
//     r = rref(a) produces the reduced row echelon form of a.

//     [r,jb] = rref(a) also returns a vector, jb, so that:
//         r = length(jb) is this algorithm's idea of the rank of a,
//         x(jb) are the bound variables in a linear system, ax = b,
//         a(:,jb) is a basis for the range of a,
//         r(1:r,jb) is the r-by-r identity matrix.

//     [r,jb] = rref(a,tol) uses the given tolerance in the rank tests.

//     roundoff errors may cause this algorithm to compute a different
//     value for the rank than rank, orth and null.

namespace nt2 { namespace details
{
  template<class T> struct rref_result
  {
    typedef typename meta::strip<T>::type                   source_t;
    typedef typename source_t::value_type                     type_t;
    typedef typename source_t::index_type                    index_t;
    typedef typename meta::as_real<type_t>::type              base_t;
    typedef T                                                 data_t;
    typedef typename meta::as_integer<base_t, signed>::type  itype_t;
    typedef nt2::container::table<type_t,nt2::matlab_index_>              tab_t;
    typedef nt2::container::table<base_t,nt2::matlab_index_>             btab_t;
    typedef nt2::container::table<itype_t,nt2::matlab_index_>            itab_t;
    typedef nt2::container::table<nt2_la_int,nt2::matlab_index_>         ibuf_t;
    typedef nt2::container::table<type_t,index_t>                   result_type;
    typedef nt2::container::table<base_t,index_t>                  bresult_type;
    typedef nt2::container::table<itype_t,index_t>                 iresult_type;
    //must be dry I think

    template<class Input>
    rref_result ( Input& xpr, base_t tol)
      : tol_(tol)
      , a_(xpr)
      , n_( nt2::height(a_)  )
      , m_( nt2::width(a_)  )
      , jb_(of_size(1, n_))
    {
      BOOST_ASSERT_MSG(ismatrix(a_), "input to rref must be matrix");
      if (tol < Zero<base_t>()) tol = nt2::max(m_,n_)*nt2::Eps<base_t>()*nt2::mnorminf(a_);
      itype_t i = 1, j = 1;
      itype_t k = 0;
      base_t p;
      itype_t cnt = 1;
      while(i <= m_ && j <= n_)
      {
        //          tie(p, k) =  nt2::max(nt2::abs(a_(_(i, m_),j))); //TODO
        p = nt2::globalmax(nt2::abs(a_(_(i, m_),j)));
        for(int l = i; l <= m_; ++l) if (nt2::abs(a_(l, j)) == p) { k = l; break; }
        //k = k+i-1;
        if (p <= tol)
        {
          // the column is negligible, zero it out.
          a_(_(i, m_),j) = nt2::zeros(m_-i+1, 1, meta::as_<type_t>());
          ++j;
        }
        else
        {
          // remember column index
          //jb_ = cath(jb_, j); //TODO
          jb_(cnt) = j; ++cnt;
          // swap i-th and k-th rows.
          tab_t tmp = a_(i, _(j, n_));
          a_(i, _(j, n_)) = a_(k, _(j, n_));
          a_(k, _(j, n_)) = tmp;
          //              a_(cath(i, k),_(j, n)) = a_(cath(k, i),_(j, n));
          // divide the pivot row by the pivot element.
          type_t tmp1 =  a_(i, j);
          a_(i,_(j, n_)) = a_(i,_(j, n_))/tmp1;
          // subtract multiples of the pivot row from all the other rows.
          for (itype_t kk = 1; kk <= m_; ++kk)//[1:i-1 i+1:m]
          {
            if (kk!=i)
            {
              type_t tmp2 = a_(kk,j);
              a_(kk,_(j, n_)) = a_(kk,_(j, n_))- tmp2*a_(i,_(j, n_));
            }
          }
          ++i; ++j;
        }
      }
      jb_ =  nt2::expand(jb_, 1, --cnt);
    }

    rref_result& operator=(rref_result const& src)
    {
      tol_    = src.tol_;
      a_      = src.a_;
      n_      = src.n_;
      m_      = src.m_;
      jb_     = src.jb_;
      return *this;
    }

    rref_result(rref_result const& src)
      : tol_(src.tol_),
        a_(src.a_),
        n_(src.n_),
        m_(src.m_),
        jb_(src.jb_)
    {}

    //==========================================================================
    // Return raw values
    //==========================================================================
    data_t values() const { return a_; }
    data_t rref() const { return a_; }

    //==========================================================================
    // Return permutation
    //==========================================================================
    const itab_t& jb() const
    {
      //typedef typename boost::mpl::at_c<typename index_t::type,0>::type base;
      return jb_; //+ base::value + Mone<itype_t>();
    }

  private:
    btab_t                         tol_;
    data_t                           a_;
    nt2_la_int                       n_;
    nt2_la_int                       m_;
    itab_t                          jb_;
  };
} }



#endif

// /////////////////////////////////////////////////////////////////////////////
// End of rref.hpp
// /////////////////////////////////////////////////////////////////////////////

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_GENERIC_PPVAL_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_GENERIC_PPVAL_HPP_INCLUDED

#include <nt2/include/functions/bsearch.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{

  template < class T > class ppval{
  public:
    typedef T                                                         value_type;
    typedef typename meta::as_integer<value_type>::type               index_type;
    typedef table<value_type>                                             vtab_t;
    typedef table<index_type>                                             itab_t;

    template < class XPR1,  class XPR2 >
    ppval(const XPR1 & breaks_, const XPR2 &coefs_):
      form("pp"){
      breaks = breaks_;
      coefs = coefs_;
      order = coefs.width();
    }

    template < class A0,  class A1, class A2, class A3, class A4>
    ppval(const A0 & x,
          const A1 & y,
          const A2 & s,
          const A3 & dx,
          const A4 & divdif):
      form("pp"),
      breaks(x)
    {
      table<value_type> dzzdx = (divdif-s(nt2::_,nt2::_(begin_, end_-1)))/dx;
      table<value_type> dzdxdx = (s(nt2::_,nt2::_(begin_+1, end_))-divdif)/dx;
      coefs = nt2::trans(nt2::catv(nt2::catv(nt2::catv((dzdxdx-dzzdx)/dx,
                                                       Two<value_type>()*dzzdx-dzdxdx),
                                             s(nt2::_,_(begin_, end_-1))),
                                   y(_, _(begin_, end_-1)))
                         );
      order = nt2::width(coefs);
    }


    const table<value_type>& getbreaks()  const{return breaks; }
    const table<value_type>& getcoefs ()  const{return coefs;  }
    size_t                   getorder()   const{return order;  }
    const std::string &      getform()    const{return form;   }


    template <class XPR> vtab_t eval(const XPR & xxi){
      vtab_t xi =  rowvect(xxi);
      itab_t index = nt2::bsearch (breaks, xi);
      vtab_t val   = coefs(index, 1);
      for(size_t i=2; i <= order; ++i){
        val = mul(colvect(xi-breaks(index)), val) + coefs(index,i);
      }
      val = nt2::reshape(val, size(xxi));
      return val;
    }

  private :
    std::string form;
    nt2::table<value_type> breaks;
    nt2::table<value_type> coefs;
    size_t order;
    size_t pieces;
  };


} }


#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_GENERIC_INTERP1_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_GENERIC_INTERP1_HPP_INCLUDED

#include <nt2/interpol/functions/interp1.hpp>
#include <nt2/include/functions/is_nge.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/bsearch.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/nearest.hpp>
#include <nt2/include/functions/linear.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::interp1_,N1,nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::value_type  child1;
    typedef typename boost::proto::result_of::child_c<A1&,2>::value_type  child2;
    typedef typename child0::value_type                               value_type;
    typedef typename meta::as_integer<value_type>::type               index_type;
    typedef typename A0::value_type                                    sale_type;
    typedef A0&                                                      result_type;

    result_type operator()(A0& yi, A1& inputs) const
    {
       char method =  'l'; // 'n', 'c', 'p', 's'
       choices(inputs, method, N1());
       return compute(yi, inputs, method, N1());
    }
  private :
// perhaps xi is not there
    static void choices(const A1&, char&, boost::mpl::long_<3> const &)
    {
      // all by default
    }
    static void choices(const A1& inputs, char & method, boost::mpl::long_<4> const &)
    {
      //x, y, xi, method
      method =  boost::proto::child_c<3>(inputs);
    }
    static void choices(const A1& inputs, char & method, boost::mpl::long_<5> const &)
    {
      //x, y, xi, method
      method =  boost::proto::child_c<3>(inputs);
    }
    static A0& compute(A0& yi, const A1& inputs, char, boost::mpl::long_<3> const &)
    {
      const child0 & x   =  boost::proto::child_c<0>(inputs);
      const child1 & y   =  boost::proto::child_c<1>(inputs);
      const child2 & xi  =  boost::proto::child_c<2>(inputs);
      yi = nearest(x, y, xi);  return yi;
    }
    static A0& compute(A0& yi, const A1& inputs, char method, boost::mpl::long_<4> const &)
    {
      const child0 & x   =  boost::proto::child_c<0>(inputs);
      const child1 & y   =  boost::proto::child_c<1>(inputs);
      const child2 & xi  =  boost::proto::child_c<2>(inputs);
      switch (method)
      {
        case 'n' : yi = nearest(x, y, xi);  return yi;
          //          case 's' : yi = spline(x, y, xi);return yi;
          //           case 'c' : yi = cubic(x, y, xi);return yi;
          //           case 'p' : yi = pship(x, y, xi);return yi;
        default  : yi = linear(x, y, xi); return yi;
      }
      return yi;
    }
    static A0& compute(A0& yi, A1& inputs, const char method, boost::mpl::long_<5> const &)
    {
      typedef typename boost::proto::result_of::child_c<A1&,4>::value_type        child4;

      const child0 & x   =  boost::proto::child_c<0>(inputs);
      const child1 & y   =  boost::proto::child_c<1>(inputs);
      const child2 & xi  =  boost::proto::child_c<2>(inputs);
      const child4 & ext =  boost::proto::child_c<4>(inputs);
      switch (method)
      {
        case 'n' : yi = nearest(x, y, xi, ext); return yi;
          //           case 's' : yi = spline(x, y, xi, ext);return yi;
          //           case 'c' : yi = cubic(x, y, xi, ext);return yi;
          //           case 'p' : yi = pship(x, y, xi, ext);return yi;
        default  : yi = linear(x, y, xi, ext); return yi;
      }
    }
  };
} }


#endif

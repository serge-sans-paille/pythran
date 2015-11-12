//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BOOLEAN_FUNCTIONS_COMPLEX_GENERIC_IFNOTSUB_HPP_INCLUDED
#define NT2_BOOLEAN_FUNCTIONS_COMPLEX_GENERIC_IFNOTSUB_HPP_INCLUDED

#include <nt2/boolean/functions/ifnotsub.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/minus.hpp>
#include <boost/type_traits/common_type.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ifnotsub_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_< unspecified_<A0> >)
                              (generic_< unspecified_<A1> >)
                              (generic_< unspecified_<A2> >)
                            )
  {
    typedef typename boost::common_type<A1, A2>::type result_type;
    result_type  operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      return a1-nt2::if_zero_else(a0, a2);
    }
  };
} }

#endif

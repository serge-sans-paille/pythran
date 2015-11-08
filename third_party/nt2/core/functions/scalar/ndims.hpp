//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_NDIMS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_NDIMS_HPP_INCLUDED

#include <nt2/core/functions/ndims.hpp>
#include <boost/mpl/size_t.hpp>
#include <algorithm>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ndims_, tag::cpu_
                            , (A0), (scalar_< unspecified_<A0> >)
                            )
  {
    typedef boost::mpl::size_t<2> result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&) const { return result_type(); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ndims_, tag::cpu_
                            , (A0), (fusion_sequence_<A0>)
                            )
  {
    typedef std::size_t result_type;

    static bool local_match(std::size_t i) { return i != 1; }

    result_type operator()(A0& sz) const
    {
      // find the first non-1 from the end
      typename A0::const_reverse_iterator
      b = sz.rbegin(), e = sz.rend(),c;
      c = std::find_if(b,e,local_match);

      return std::distance(c,e);
    }
  };
} }

#endif

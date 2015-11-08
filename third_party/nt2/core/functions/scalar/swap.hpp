//==============================================================================
//         Copyright 2009 - 2014   LRI UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_SWAP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_SWAP_HPP_INCLUDED

#include <nt2/core/functions/swap.hpp>
#include <boost/swap.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::swap_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_< A0 > >)
                              (scalar_<unspecified_< A0 > >)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A0& a1) const
    {
      boost::swap(a0,a1);
    }
  };
} }

#endif

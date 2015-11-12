//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_EXTENT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_EXTENT_HPP_INCLUDED

#include <nt2/core/functions/extent.hpp>
#include <nt2/core/utility/of_size.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::extent_, tag::cpu_
                            , (A0), (unspecified_<A0>)
                            )
  {
    typedef _0D result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&) const { return result_type(); }
  };
} }

#endif

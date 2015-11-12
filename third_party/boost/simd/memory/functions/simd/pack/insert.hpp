//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_INSERT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_INSERT_HPP_INCLUDED

#include <boost/simd/include/functions/insert.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/dsl/functions/terminal.hpp>
#include <boost/simd/sdk/simd/category.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::insert_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (scalar_< unspecified_<A0> >)
                                      ((node_ < A1
                                              , boost::simd::tag::terminal_
                                              , boost::mpl::long_<0>
                                              , boost::simd::domain
                                              >
                                      ))
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1& a1, A2 a2) const
    {
      a1[a2] = a0;
    }
  };
} } }

#endif

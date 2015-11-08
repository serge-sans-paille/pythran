//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_EXTRACT_HPP_INCLUDED

#include <boost/simd/include/functions/extract.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/category.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , ((ast_<A0, boost::simd::domain>))
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef typename A0::value_type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      return extract(evaluate(a0),a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , tag::cpu_
                                    , (A0)(A1)(Tag)
                                    , ((node_ < A0, Tag
                                              , boost::mpl::long_<0>
                                              , boost::simd::domain
                                              >
                                      ))
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef typename A0::value_type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      return a0[a1];
    }
  };
} } }

#endif

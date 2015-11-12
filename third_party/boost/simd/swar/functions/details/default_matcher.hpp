//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_DEFAULT_MATCHER_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_DEFAULT_MATCHER_HPP_INCLUDED

#include <boost/simd/swar/functions/details/permuted.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  struct default_matcher
  {
    // By default, nothing is optimized
    template<typename Permutation>
    struct base_matcher
    {
      template<typename T, typename P>
      static BOOST_FORCEINLINE T process(T const& a0, P const& p)
      {
        return Permutation::call(a0,p);
      }

      template<typename T, typename P>
      static BOOST_FORCEINLINE
      T process(T const& a0, T const& a1, P const& p)
      {
        return Permutation::call(a0,a1,p);
      }
    };

    // This is true for w/e cardinal
    template<int I0, int I1, typename Permutation>
    struct match2 : base_matcher<Permutation>
    {};

    template< int I0, int I1, int I2, int I3
            , typename Permutation
            >
    struct match4 : base_matcher<Permutation>
    {};

    template< int I0, int I1, int I2, int I3
            , int I4, int I5, int I6, int I7
            , typename Permutation
            >
    struct match8 : base_matcher<Permutation>
    {};

    template< int I0 , int I1 , int I2 , int I3
            , int I4 , int I5 , int I6 , int I7
            , int I8 , int I9 , int I10, int I11
            , int I12, int I13, int I14, int I15
            , typename Permutation
            >
    struct match16  : base_matcher<Permutation>
    {};

    template< int I0 , int I1 , int I2 , int I3
            , int I4 , int I5 , int I6 , int I7
            , int I8 , int I9 , int I10, int I11
            , int I12, int I13, int I14, int I15
            , int I16, int I17, int I18, int I19
            , int I20, int I21, int I22, int I23
            , int I24, int I25, int I26, int I27
            , int I28, int I29, int I30, int I31
            , typename Permutation
            >
    struct match32  : base_matcher<Permutation>
    {};
  };
} } }

#endif

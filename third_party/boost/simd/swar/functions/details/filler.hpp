//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_FILLER_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_FILLER_HPP_INCLUDED

#include <boost/simd/swar/functions/details/permuted.hpp>
#include <boost/simd/swar/functions/details/pick.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  template<typename D, typename T, typename P>
  struct unary_filler
  {
    unary_filler(T const& a0_, D& o) : a0(a0_), out(o) {}

    template<int I> BOOST_FORCEINLINE void operator()() const
    {
      out[I] = pick < permuted<P,I,D::static_size>::value
                    , T
                    , D::static_size
                    >::apply(a0);
    }

    T const& a0;
    D&       out;

    private:
    unary_filler& operator=(unary_filler const&);
  };

  template<typename D, typename T, typename P>
  struct binary_filler
  {
    binary_filler ( T const& a0_, T const& a1_, D& o)
                  : a0(a0_), a1(a1_), out(o)
    {}

    template<int I> BOOST_FORCEINLINE void operator()() const
    {
      out[I] = pick < permuted<P,I,D::static_size>::value
                    , T
                    , D::static_size
                    >::apply(a0,a1);
    }

    T const& a0,a1;
    D&       out;

    private:
    binary_filler& operator=(binary_filler const&);
  };
} } }

#endif

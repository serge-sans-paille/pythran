//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_DEFAULT_PERMUTATION_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_DEFAULT_PERMUTATION_HPP_INCLUDED

#include <boost/simd/swar/functions/details/permuted.hpp>
#include <boost/simd/swar/functions/details/topology.hpp>
#include <boost/simd/swar/functions/details/pick.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // default_permutation defines how to perform an arbitrary permutation of a
  // given cardinal using the lowest common denominator between extensions
  //============================================================================
  template<std::size_t Cardinal> struct default_permutation;

  //============================================================================
  // Cardinal 2 permutation unit
  //============================================================================
  template<> struct default_permutation<2>
  {
    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const&)
    {
      return make<T>( pick<permuted<P,0,2>::value,T,2>::apply(a0)
                    , pick<permuted<P,1,2>::value,T,2>::apply(a0)
                    );
    }

    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const&)
    {
      return make<T>( pick<permuted<P,0,2>::value,T,2>::apply(a0,a1)
                    , pick<permuted<P,1,2>::value,T,2>::apply(a0,a1)
                    );
    }
  };

  //============================================================================
  // Cardinal 4 permutation unit
  //============================================================================
  template<> struct default_permutation<4>
  {
    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const&)
    {
      return make<T>( pick<permuted<P,0,4>::value,T,4>::apply(a0)
                    , pick<permuted<P,1,4>::value,T,4>::apply(a0)
                    , pick<permuted<P,2,4>::value,T,4>::apply(a0)
                    , pick<permuted<P,3,4>::value,T,4>::apply(a0)
                    );
    }

    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const&)
    {
      return make<T>( pick<permuted<P,0,4>::value,T,4>::apply(a0,a1)
                    , pick<permuted<P,1,4>::value,T,4>::apply(a0,a1)
                    , pick<permuted<P,2,4>::value,T,4>::apply(a0,a1)
                    , pick<permuted<P,3,4>::value,T,4>::apply(a0,a1)
                    );
    }
  };

  // Cardinal 8 permutation unit
  template<> struct default_permutation<8>
  {
    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const&)
    {
      return make<T>( pick<permuted<P,0,8>::value,T,8>::apply(a0)
                    , pick<permuted<P,1,8>::value,T,8>::apply(a0)
                    , pick<permuted<P,2,8>::value,T,8>::apply(a0)
                    , pick<permuted<P,3,8>::value,T,8>::apply(a0)
                    , pick<permuted<P,4,8>::value,T,8>::apply(a0)
                    , pick<permuted<P,5,8>::value,T,8>::apply(a0)
                    , pick<permuted<P,6,8>::value,T,8>::apply(a0)
                    , pick<permuted<P,7,8>::value,T,8>::apply(a0)
                    );
    }

    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const&)
    {
      return make<T>( pick<permuted<P,0,8>::value,T,8>::apply(a0,a1)
                    , pick<permuted<P,1,8>::value,T,8>::apply(a0,a1)
                    , pick<permuted<P,2,8>::value,T,8>::apply(a0,a1)
                    , pick<permuted<P,3,8>::value,T,8>::apply(a0,a1)
                    , pick<permuted<P,4,8>::value,T,8>::apply(a0,a1)
                    , pick<permuted<P,5,8>::value,T,8>::apply(a0,a1)
                    , pick<permuted<P,6,8>::value,T,8>::apply(a0,a1)
                    , pick<permuted<P,7,8>::value,T,8>::apply(a0,a1)
                    );
    }
  };

  // Cardinal 16 permutation unit
  template<> struct default_permutation<16>
  {
    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const&)
    {
      return make<T>( pick<permuted<P, 0,16>::value,T,16>::apply(a0)
                    , pick<permuted<P, 1,16>::value,T,16>::apply(a0)
                    , pick<permuted<P, 2,16>::value,T,16>::apply(a0)
                    , pick<permuted<P, 3,16>::value,T,16>::apply(a0)
                    , pick<permuted<P, 4,16>::value,T,16>::apply(a0)
                    , pick<permuted<P, 5,16>::value,T,16>::apply(a0)
                    , pick<permuted<P, 6,16>::value,T,16>::apply(a0)
                    , pick<permuted<P, 7,16>::value,T,16>::apply(a0)
                    , pick<permuted<P, 8,16>::value,T,16>::apply(a0)
                    , pick<permuted<P, 9,16>::value,T,16>::apply(a0)
                    , pick<permuted<P,10,16>::value,T,16>::apply(a0)
                    , pick<permuted<P,11,16>::value,T,16>::apply(a0)
                    , pick<permuted<P,12,16>::value,T,16>::apply(a0)
                    , pick<permuted<P,13,16>::value,T,16>::apply(a0)
                    , pick<permuted<P,14,16>::value,T,16>::apply(a0)
                    , pick<permuted<P,15,16>::value,T,16>::apply(a0)
                    );
    }

    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const&)
    {
      return make<T>( pick<permuted<P, 0,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P, 1,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P, 2,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P, 3,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P, 4,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P, 5,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P, 6,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P, 7,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P, 8,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P, 9,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P,10,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P,11,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P,12,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P,13,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P,14,16>::value,T,16>::apply(a0,a1)
                    , pick<permuted<P,15,16>::value,T,16>::apply(a0,a1)
                    );;
    }
  };
} } }

#endif

//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_RROR_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_RROR_HPP_INCLUDED

#include <boost/simd/bitwise/functions/rror.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/unary_minus.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_gtz.hpp>
#include <boost/simd/include/functions/simd/ror.hpp>
#include <boost/simd/include/functions/simd/rol.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/equal_to.hpp>

#ifndef NDEBUG
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/constants/zero.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::rror_, tag::cpu_
                                      , (A0)(A1)(X)
                                      , (boost::mpl::equal_to
                                          < boost::simd::meta::cardinal_of<A0>
                                          , boost::simd::meta::cardinal_of<A1>
                                          >
                                        )
                                      , ((simd_< arithmetic_<A0>, X >))
                                        ((simd_< int_<A1>, X >))
                                      )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      #ifndef NDEBUG
      return bitwise_cast<result_type>( if_else ( is_gtz(a1)
                                                , ror ( bitwise_cast<A1>(a0)
                                                      , max(Zero<A1>(),a1)
                                                      )
                                                , rol ( bitwise_cast<A1>(a0)
                                                      , max(Zero<A1>(),-a1)
                                                      )
                                                )
                                      );
      #else
      return bitwise_cast<result_type>( if_else ( is_gtz(a1)
                                                , ror(bitwise_cast<A1>(a0), a1)
                                                , rol(bitwise_cast<A1>(a0),-a1)
                                                )
                                      );
      #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::rror_, tag::cpu_
                                      , (A0)(A1)(X)
                                      , (boost::mpl::equal_to
                                          < boost::simd::meta::cardinal_of<A0>
                                          , boost::simd::meta::cardinal_of<A1>
                                          >
                                        )
                                      , ((simd_< arithmetic_<A0>, X >))
                                        ((simd_< uint_<A1>, X >))
                                      )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_cast<result_type>( ror( bitwise_cast<A1>(a0), a1 ) );
    }
  };
} } }

#endif

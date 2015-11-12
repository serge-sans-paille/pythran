//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_GENERIC_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_GENERIC_BITWISE_CAST_HPP_INCLUDED

#include <boost/simd/memory/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/dispatch/meta/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/not.hpp>
#include <cstring>

namespace boost { namespace simd { namespace ext
{
#ifdef BOOST_SIMD_NO_STRICT_ALIASING

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::bitwise_cast_, tag::cpu_, (A0)(A1)
                                      , (mpl::not_< is_same<A0, typename A1::type > >)
                                      , (generic_< unspecified_<A0> >)
                                        (target_< generic_< unspecified_<A1> > >)
                                      )
  {
    typedef typename A1::type const& result_type;

    BOOST_MPL_ASSERT_MSG
    ( (sizeof(A0) == sizeof(typename A1::type))
    , BOOST_SIMD_TARGET_IS_NOT_SAME_SIZE_AS_SOURCE_IN_BITWISE_CAST
    , (A0&,typename A1::type&)
    );

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return reinterpret_cast<result_type>(a0);
    }
  };

#else

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::bitwise_cast_, tag::cpu_, (A0)(A1)
                                      , (mpl::not_< is_same<A0, typename A1::type > >)
                                      , (generic_< unspecified_<A0> >)
                                        (target_< generic_< unspecified_<A1> > >)
                                      )
  {
    typedef typename A1::type result_type;

    BOOST_MPL_ASSERT_MSG
    ( (sizeof(A0) == sizeof(typename A1::type))
    , BOOST_SIMD_TARGET_IS_NOT_SAME_SIZE_AS_SOURCE_IN_BITWISE_CAST
    , (A0&,typename A1::type&)
    );

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      result_type that;
      std::memcpy(&that, &a0, sizeof(a0));
      return that;
    }
  };

#endif

  BOOST_DISPATCH_REGISTER_TO_IF((boost)(simd)(ext), boost::simd::tag::bitwise_cast_, tag::cpu_, (A0)(A1)
                               , (is_same<A0, typename A1::type>)
                               , (generic_< unspecified_<A0> >)
                                 (target_< generic_< unspecified_<A1> > >)
                               , dispatch::identity
                               )

} } }
#endif

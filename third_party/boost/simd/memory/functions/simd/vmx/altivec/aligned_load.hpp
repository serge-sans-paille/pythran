//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_ALIGNED_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/memory/functions/aligned_load.hpp>
#include <boost/simd/include/functions/slide.hpp>
#include <boost/simd/memory/functions/details/char_helper.hpp>
#include <boost/simd/memory/functions/details/check_ptr.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>
#include <iterator>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - SIMD load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , boost::simd::tag::vmx_
                                      , (A0)(A2)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type::value_type
                                          >
                                        )
                                      , (iterator_< scalar_< arithmetic_<A0> > >)
                                        ((target_
                                          < simd_ < arithmetic_<A2>
                                                  , boost::simd::tag::vmx_
                                                  >
                                          >
                                        ))
                            )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return vec_ld(0, char_helper(a0));
    }
  };

  /// INTERNAL ONLY - Load with static misalignment without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , boost::simd::tag::vmx_
                                      , (A0)(A2)(A3)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type::value_type
                                          >
                                        )
                                      , (iterator_< scalar_< arithmetic_<A0> > >)
                                        ((target_
                                          < simd_ < arithmetic_<A2>
                                                  , boost::simd::tag::vmx_
                                                  >
                                          >
                                        ))
                                        (mpl_integral_< scalar_< integer_<A3> > >)
                                      )
  {
    typedef typename A2::type result_type;

    typedef typename A3::value_type align_t;
    static const std::size_t cardinal = meta::cardinal_of<result_type>::value;
    static const align_t unalignment  = A3::value % cardinal;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&, const A3&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0-A3::value, sizeof(result_type));
      return eval( a0, boost::mpl::bool_<!unalignment>() );
    }

    // Periodic case - Just load as normal
    BOOST_FORCEINLINE result_type eval( A0 a0, boost::mpl::true_ const&) const
    {
      return boost::simd::aligned_load<result_type>(a0);
    }

    // Non-periodic case
    BOOST_FORCEINLINE result_type eval(A0 a0, boost::mpl::false_ const&) const
    {
      typedef typename meta::scalar_of<result_type>::type scalar_type;

      // Load aligned sources
      result_type a  = simd::aligned_load<result_type>(a0-unalignment);
      result_type b  = simd::aligned_load<result_type>(a0-unalignment,cardinal);

      // Shift everything in place
      return slide<unalignment>(a,b);
    }
  };
} } }

#endif
#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_ALIGNED_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/memory/functions/aligned_load.hpp>
#include <boost/simd/memory/functions/details/check_ptr.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/slide.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/attributes.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4308) // negative integral conversion
#endif

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - Load register of SIMD double without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A2)
                                    , (iterator_< scalar_< double_<A0> > >)
                                      ((target_ < simd_ < double_<A2>
                                                        , boost::simd::tag::sse_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm_load_pd(a0);
    }
  };

  /// INTERNAL ONLY - Load register of SIMD float
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A2)
                                    , (iterator_< scalar_< single_<A0> > >)
                                      ((target_ < simd_ < single_<A2>
                                                        , boost::simd::tag::sse_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm_load_ps(a0);
    }
  };

  /// INTERNAL ONLY - Load register of SIMD integers without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , boost::simd::tag::sse2_
                                      , (A0)(A2)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type::value_type
                                          >
                                        )
                                      , (iterator_< scalar_< integer_<A0> > >)
                                        ((target_ < simd_
                                                    < integer_<A2>
                                                    , boost::simd::tag::sse_
                                                    >
                                                >
                                        ))
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm_load_si128(reinterpret_cast<__m128i const*>(a0));
    }
  };

  /// INTERNAL ONLY - Load with Misalignment without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , boost::simd::tag::sse2_
                                      , (A0)(A2)(A3)
                                      , ( boost::is_same
                                          < typename boost::pointee<A0>::type
                                          , typename A2::type::value_type
                                          >
                                        )
                                      , (iterator_< scalar_< arithmetic_<A0> > >)
                                        ((target_ < simd_
                                                    < arithmetic_<A2>
                                                    , boost::simd::tag::sse_
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

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A2 const&, A3 const& a3) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0-A3::value, sizeof(result_type));
      return eval( a0, a3, boost::mpl::bool_<!unalignment>() );
    }

    // Periodic case - Just load as normal
    BOOST_FORCEINLINE result_type
    eval( A0 a0, A3 const&, boost::mpl::true_ const&) const
    {
      return boost::simd::aligned_load<result_type>(a0);
    }

    // Non-periodic case
    BOOST_FORCEINLINE result_type
    eval(A0 a0, A3 const&, boost::mpl::false_ const&) const
    {
      // Load aligned sources
      result_type a  = aligned_load<result_type>(a0-unalignment);
      result_type b  = aligned_load<result_type>( a0-unalignment
                                                , std::size_t(cardinal)
                                                );
      return slide<unalignment>(a,b);
    }
  };
} } }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
#endif

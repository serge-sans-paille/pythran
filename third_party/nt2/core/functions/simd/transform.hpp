//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIMD_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIMD_TRANSFORM_HPP_INCLUDED
#ifndef BOOST_SIMD_NO_SIMD

#include <nt2/core/functions/transform.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/scalar/numel.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <boost/fusion/include/pop_front.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Partial nD element-wise transform with offset/size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::transform_, boost::simd::tag::simd_
                               , (Out)(In)(Range)
                               , (boost::simd::meta::is_vectorizable<typename Out::value_type, BOOST_SIMD_DEFAULT_EXTENSION>)
                               , ((ast_<Out, nt2::container::domain>))
                                 ((ast_<In, nt2::container::domain>))
                                 (unspecified_<Range>)
                               )
  {
    typedef void result_type;

    typedef typename Out::value_type stype;
    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION> target_type;

    BOOST_FORCEINLINE result_type
    operator()(Out& out, In& in, Range range) const
    {
      std::size_t p (range.first);
      std::size_t sz (range.second);

      static const std::size_t N = boost::simd::meta
                                        ::cardinal_of<target_type>::value;

      std::size_t aligned_sz  = sz & ~(N-1);
      std::size_t it          = p;

      for(std::size_t m=p+aligned_sz; it != m; it+=N)
        nt2::run( out, it, nt2::run(in, it, meta::as_<target_type>()) );

      for(std::size_t m=p+sz; it != m; ++it)
        nt2::run( out, it, nt2::run(in, it, meta::as_<stype>()) );
    }
  };
} }

#endif
#endif

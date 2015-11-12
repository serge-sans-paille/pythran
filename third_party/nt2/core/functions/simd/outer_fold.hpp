//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIMD_OUTER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIMD_OUTER_FOLD_HPP_INCLUDED

#include <nt2/core/functions/outer_fold.hpp>
#include <nt2/core/functions/details/outer_fold_step.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <boost/simd/memory/align_under.hpp>
#include <boost/fusion/include/pop_back.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4702) // unreachable code false positive
#endif

#ifndef BOOST_SIMD_NO_SIMD
namespace nt2 { namespace ext
{
  //============================================================================
  // Partial outer_fold with offset/size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF ( nt2::tag::outer_fold_, boost::simd::tag::simd_
                                , (Out)(In)(Neutral)(Bop)(Uop)
                                , ( boost::simd::meta::
                                    is_vectorizable < typename Out::value_type
                                                    , BOOST_SIMD_DEFAULT_EXTENSION
                                                    >
                                  )
                                , ((ast_< Out, nt2::container::domain>))
                                  ((ast_< In, nt2::container::domain>))
                                  (unspecified_<Neutral>)
                                  (unspecified_<Bop>)
                                  (unspecified_<Uop>)
                                )
  {
    typedef void                                                              result_type;
    typedef typename Out::value_type                                           value_type;
    typedef typename In::extent_type                                          extent_type;
    typedef boost::simd::native<value_type,BOOST_SIMD_DEFAULT_EXTENSION>      target_type;

    BOOST_FORCEINLINE result_type
    operator()( Out& out ,In& in
              , Neutral const& neutral
              , Bop const& bop, Uop const&
              ) const
    {
      extent_type ext = in.extent();
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t obound =  boost::fusion::at_c<2>(ext);
      std::size_t ibound = boost::fusion::at_c<0>(ext);
      std::size_t mbound = boost::fusion::at_c<1>(ext);
      std::size_t iboundxmbound =  ibound * mbound;

      std::size_t cache_line_size = nt2::config::top_cache_line_size(2); // in byte
      std::size_t cache_bound = (cache_line_size / (sizeof(value_type)*N))*N;
      std::size_t iibound =  boost::simd::align_under(ibound, cache_bound);

      for(std::size_t o = 0, oout_ = 0, oin_ = 0;
          o < obound;
          ++o, oout_+=ibound, oin_+= iboundxmbound)
      {
        // vectorized part
        details::outer_fold_step<target_type,Out,In,Neutral,Bop>
        (out, in, neutral, bop, 0, iibound, oout_, oin_);

        // scalar part
        details::outer_fold_step<value_type,Out,In,Neutral,Bop>
        (out, in, neutral, bop, iibound, ibound - iibound, oout_, oin_);

      }
    }
  };
} }

#endif

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

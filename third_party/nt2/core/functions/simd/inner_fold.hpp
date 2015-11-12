//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIMD_INNER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIMD_INNER_FOLD_HPP_INCLUDED

#include <nt2/core/functions/inner_fold.hpp>
#include <nt2/core/functions/details/fold_step.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>


#ifndef BOOST_SIMD_NO_SIMD

namespace nt2 { namespace ext
{
  //============================================================================
  // General inner_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF ( nt2::tag::inner_fold_, boost::simd::tag::simd_
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
    operator()(Out& out, In& in
              , Neutral const& neutral, Bop const& bop, Uop const& uop
              ) const
    {
      extent_type ext = in.extent();
      std::size_t obound = nt2::numel(boost::fusion::pop_front(ext));
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t bound  = boost::fusion::at_c<0>(ext);
      std::size_t nb_vec = (bound/N);
      std::size_t ibound = nb_vec * N;

      for(std::size_t j = 0, k = 0; j != obound; ++j, k+=bound)
      {
        target_type vec_out = details::fold_step(
          neutral(nt2::meta::as_<target_type>()), in, bop, k, nb_vec, N
        );

        value_type s_out = uop( vec_out );
        s_out = details::fold_step(s_out, in, bop, k+ibound, bound-ibound, 1);

        nt2::run(out, j, s_out);
      }
    }
  };
} }

#endif
#endif

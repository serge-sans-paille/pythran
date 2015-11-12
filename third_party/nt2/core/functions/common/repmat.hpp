//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_REPMAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_REPMAT_HPP_INCLUDED

#include <nt2/core/functions/repmat.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/modulo.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_ < A0, nt2::tag::repmat_
                                      , N , nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type               result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typedef typename A0::extent_type                            ext_t;
      typedef typename meta::as_index<result_type>::type          i_t;
      typedef typename result_of::as_subscript<ext_t, i_t>::type  sub_t;

      // TODO: Precompute ?
      ext_t in_sz   = boost::proto::child_c<1>(a0).extent();

      // Current position in the output
      sub_t pos = as_subscript(a0.extent(), nt2::enumerate<i_t>(p));

      // TODO: Unroll this ?
      for(std::size_t i=0; i<sub_t::static_size;i++)
        pos[i] = pos[i] % splat<i_t>(in_sz[i]);

      return nt2::run ( boost::proto::child_c<1>(a0)
                      , as_index(in_sz, pos)
                      , t
                      );
    }
  };
} }

#endif

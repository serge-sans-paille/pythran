//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_RELATIVE_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_RELATIVE_SIZE_HPP_INCLUDED

#include <nt2/core/functions/relative_size.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Compute indexing size using any expression in the non 1D cases
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_size_, tag::cpu_
                            , (Idx)(Size)(Base)
                            , ((ast_<Idx, nt2::container::domain>))
                              (scalar_< unspecified_<Size> >)
                              (scalar_< unspecified_<Base> >)
                            )
  {
    typedef typename meta::call<tag::numel_(Idx const&)>::type  result_type;

    BOOST_FORCEINLINE result_type
    operator()(const Idx& idx, const Size&, const Base& ) const
    {
      return nt2::numel( idx );
    }
  };
} }

#endif

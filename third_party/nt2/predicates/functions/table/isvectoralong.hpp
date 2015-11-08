//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ISVECTORALONG_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ISVECTORALONG_HPP_INCLUDED

#include <nt2/predicates/functions/isvectoralong.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isvectoralong_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0, const A1& dim) const
    {
      typename A0::extent_type  ex  = nt2::extent(a0);
      std::size_t               nz  = nt2::numel(ex);
      size_t                    d   = dim-1;

      if(nz) return ex[d] == nz;
      else
      {
        // TODO: Fix for dim > ex.size()
        for(size_t i=0; i < d; ++i)
          if (ex[i] !=  1u) return false;

        for(size_t i=dim; i < ex.size(); ++i)
          if (ex[i] !=  1u) return false;
      }
      return true;
    }
  };
} }

#endif

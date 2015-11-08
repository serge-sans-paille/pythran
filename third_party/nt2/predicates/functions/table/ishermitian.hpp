//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ISHERMITIAN_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ISHERMITIAN_HPP_INCLUDED

#include <nt2/predicates/functions/ishermitian.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/is_not_equal.hpp>
#include <nt2/include/functions/conj.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ishermitian_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0) const
    {
      if(!issquare(a0)) return false;
      for(std::ptrdiff_t j=first_index<2>(a0); j <= last_index<2>(a0) ; ++j)
      {
        for(std::ptrdiff_t i=j; i <= last_index<1>(a0) ; ++i)
        {
          if( a0(i, j) != conj(a0(j, i)) ) return false;
        }
      }
      return true;
    }
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_DIAG_OF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_DIAG_OF_HPP_INCLUDED

#include <nt2/core/functions/diag_of.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::diag_of_, tag::cpu_
                              , (A0)
                              , (scalar_< arithmetic_<A0> >)
                              )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };

  /// INTERNAL ONLY
  /// TODO: Make lazier
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::offset_diag_of_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_< arithmetic_<A0> >)
                                (scalar_< integer_<A1> >)
                              )
  {
    typedef container::table<A0,nt2::_1D> result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      std::size_t n = (a1 == 0) ? 1u : 0u;
      nt2::_1D sz(n);

      result_type r(sz);
      if(n) r(1) = a0;

      return r;
    }
  };
} }

#endif

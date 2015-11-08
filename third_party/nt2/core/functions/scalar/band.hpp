//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_BAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_BAND_HPP_INCLUDED
#include <nt2/core/functions/band.hpp>
#include <nt2/include/constants/zero.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::band_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef A0  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::band_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 offset) const
    {
      return (offset >= 0) ? a : Zero<result_type>();
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::band_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 sub, A2 super) const
    {
      BOOST_ASSERT_MSG( sub <= super
                      , "Invalid band shape requested"
                      );

      return ((sub <= 0) && (0 <= super)) ? a : Zero<result_type>();
    }
  };

} }

#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_FNMS_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_FNMS_HPP_INCLUDED

#include <nt2/arithmetic/functions/fnms.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/minus.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fnms_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      return a2 - a1 * a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fnms_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<arithmetic_<A2> > )
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      return a2 - a1 * a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fnms_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<arithmetic_<A0> > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
                            )
  {
    typedef A1 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      return a2 - a1 * a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fnms_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<arithmetic_<A0> > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A2 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      return a2 - a1 * a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fnms_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      return a2 - a1 * a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fnms_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<arithmetic_<A0> > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A1 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      return a2 - a1 * a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fnms_, tag::cpu_, (A0)(A1)(A2)
                            , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<complex_<arithmetic_<A2> > > )
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      return a2 - a1 * a0;
    }
  };
} }

#endif

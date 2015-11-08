//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SCALAR_MAXIMUM_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SCALAR_MAXIMUM_HPP_INCLUDED

#include <boost/simd/reduction/functions/maximum.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::maximum_, tag::cpu_
                                    , (A0)
                                    , (scalar_< unspecified_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const & a0) const
    {
      return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::maximum_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< unspecified_<A0> >)
                                      (scalar_< integer_<A1> > )
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const & a0,  A1) const
    {
      return a0;
    }
  };
} } }

#endif

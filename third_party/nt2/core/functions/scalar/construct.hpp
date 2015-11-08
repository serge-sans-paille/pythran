//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_CONSTRUCT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_CONSTRUCT_HPP_INCLUDED

#include <nt2/core/functions/construct.hpp>
#include <nt2/include/functions/scalar/numel.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/meta/fusion.hpp>

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::iterator_;

  //============================================================================
  // Construct a terminal from a size and a Iterator pair
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_< unspecified_<A0> >)
                              (fusion_sequence_<A1>)
                              (iterator_< scalar_< unspecified_<A2> > >)
                              (iterator_< scalar_< unspecified_<A3> > >)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1 const& a1, A2 const& a2, A3 const&) const
    {
      //========================================================================
      // Check we don't copy more than expected
      //========================================================================
      BOOST_ASSERT_MSG
      ( nt2::numel(a1) == 1
      , "Source range is larger than destination container."
      );

      a0 = *a2;
    }
  };

  //============================================================================
  // Assign a container from a pair of iterators
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (unspecified_<A0>)
                              (fusion_sequence_<A1>)
                              (iterator_< scalar_< unspecified_<A2> > >)
                              (iterator_< scalar_< unspecified_<A3> > >)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1 const& a1, A2 const& a2, A3 const& a3) const
    {
      //========================================================================
      // Check we don't copy more than expected
      //========================================================================
      std::size_t range_size = std::distance(a2,a3);

      BOOST_ASSERT_MSG
      ( nt2::numel(a1) >= range_size
      , "Source range is larger than destination container."
      );

      a0.clear();
      a0.insert(a0.begin(), a2, a3);
    }
  };
} }

#endif

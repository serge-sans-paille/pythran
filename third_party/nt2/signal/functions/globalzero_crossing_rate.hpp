//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_GLOBALZERO_CROSSING_RATE_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_GLOBALZERO_CROSSING_RATE_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/zero_crossing_rate.hpp>
#include <nt2/include/functions/global.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the golbalzero_crossing_rate functor
    **/
     struct globalzero_crossing_rate_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    @brief rate of sign changes along a signal

    Computes the rate of sign changes along all elements of a signal

    @par Semantic

    For any table expression and integer:

    @code
    auto r = globalzero_crossing_rate(s, n);
    @endcode

    is equivalent to:

    @code
    auto r = zero_crossing_rate(s(_))(1);
    @endcode

    n default to firstnonsingleton(s)

    @see @funcref{zero_crossing_rate}, @funcref{colon},

    @param a0 Table expression to process

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalzero_crossing_rate_, globalzero_crossing_rate, 1)
  ///  @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalzero_crossing_rate_, globalzcr, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalzero_crossing_rate_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::zero_crossing_rate_>
                                            , const A0&
                                            )>::type                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
       return global(nt2::functor<tag::zero_crossing_rate_>(), a0);
    }
  };
} }

#endif

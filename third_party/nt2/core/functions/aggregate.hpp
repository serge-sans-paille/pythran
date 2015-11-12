//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_AGGREGATE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_AGGREGATE_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the aggregate function
**/

#include <nt2/include/functor.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for aggregate functor
    **/
    struct aggregate_ : ext::elementwise_<aggregate_>
    {
      typedef ext::elementwise_<aggregate_> parent;
    };
  }

  #if defined(DOXYGEN_ONLY)
  /*!
    @brief Agregate values in a single tree

    aggregate turn its parameters in a single blob node usable in a @nt2
    Abstract Syntax Tree. It has few uses in suer code but is required for
    some other higher-order function (like the operator() overloads).

    @param args Variadic list of parameters to glob.

    @return A @nt2 expression containing each parameter as a child.
  **/
  template<class... Args>
  typename boost::dispatch::meta::call<tag::aggregate_(Args const&...)>::type
  aggregate(Args const&...  args);

  #else

  #define M0(z,n,t)                                                           \
  template<BOOST_PP_ENUM_PARAMS(n,class A)> BOOST_FORCEINLINE                 \
  typename boost::dispatch::meta::call<tag::aggregate_                        \
                      (BOOST_PP_ENUM_BINARY_PARAMS( n                         \
                                                  , const A                   \
                                                  , & BOOST_PP_INTERCEPT))    \
                                      >::type                                 \
  aggregate(BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a))                       \
  {                                                                           \
    typename boost::dispatch::make_functor<tag::aggregate_, A0>::type callee; \
    return callee( BOOST_PP_ENUM_PARAMS(n,a) );                               \
  }                                                                           \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_DISPATCH_MAX_META_ARITY,M0,~)

  #undef M0
  #endif
}

namespace nt2 { namespace ext
{
  // INTERNAL ONLY
  struct aggregate_value_ {};

  /// INTERNAL ONLY
  /// Aggregate value type is irrelevant, we just use a placeholder type.
  template<class Domain, int N, class Expr>
  struct value_type<nt2::tag::aggregate_,Domain,N,Expr>
  {
    typedef aggregate_value_ type;
  };

  /// INTERNAL ONLY
  /// Aggregate size is irrelevant, just say it's [1]
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::aggregate_,Domain,N,Expr>
  {
    typedef of_size_<1> result_type;
    BOOST_FORCEINLINE result_type operator()(Expr&) const
    {
      return result_type();
    }
  };
} }

#endif

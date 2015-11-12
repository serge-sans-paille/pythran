//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_FUNCTIONS_ROSENBROCK_HPP_INCLUDED
#define NT2_OPTIMIZATION_FUNCTIONS_ROSENBROCK_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/option/options.hpp>
#include <nt2/optimization/options.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief rosenbrock generic tag

      Represents the rosenbrock function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct rosenbrock_ : ext::unspecified_<rosenbrock_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<rosenbrock_> parent;
    };
  }
  /*!
   * Apply rosenbrock algorithm to find local minimum of a function
   *
   * \param f        Function to optimize
   * \param init     Initial value
   * \param opt      Options pack related to the minimization handling
   *
   * \return  a tuple containing the result of the minimization, the value of the
   *          function at minimum, the number of required iteration and a boolean
   *          notifying success of convergence.
   */

  template<class F, class A, class Xpr>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
  ::call<tag::rosenbrock_( F
                         , A
                         , details::optimization_settings<typename A::value_type> const&
                         )
    >::type
  rosenbrock(F f, A init, nt2::details::option_expr<Xpr> const& opt)
  {
    typename boost::dispatch::make_functor<tag::rosenbrock_, F>::type callee;
    return callee ( f
                  , init
                  , details::optimization_settings<typename A::value_type>(opt)
                  );
  }
  /// @overload
  template<class F, class A> BOOST_FORCEINLINE
  typename boost::dispatch::meta
  ::call<tag::rosenbrock_( F
                         , A
                         , details::optimization_settings<typename A::value_type> const&
                         )
    >::type
  rosenbrock(F f, A init)
  {
    typename boost::dispatch::make_functor<tag::rosenbrock_, F>::type callee;
    return callee ( f
                  , init
                  , details::optimization_settings<typename A::value_type>()
                  );
  }
}



#endif

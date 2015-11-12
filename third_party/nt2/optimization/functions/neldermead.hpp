//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_FUNCTIONS_NELDERMEAD_HPP_INCLUDED
#define NT2_OPTIMIZATION_FUNCTIONS_NELDERMEAD_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/option/options.hpp>
#include <nt2/optimization/options.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief neldermead generic tag

      Represents the neldermead function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct neldermead_ : ext::unspecified_<neldermead_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<neldermead_> parent;
    };
  }
  /*!
    Apply neldermead algorithm to find local minimum of a function

    \param f        Function to optimize
    \param init     Initial value
    \param steps    Which are the unknowns we want to optimize
    \param opt      Options pack related to the minimization handling

    \return  a tuple containing the result of the minimization, the value of the
             function at minimum, the number of required iteration and a boolean
             notifying success of convergence.
       From original FORTRAN77 version by R ONeill.

     Reference:

       John Nelder, Roger Mead,
       A simplex method for function minimization,
       Computer Journal,
       Volume 7, 1965, pages 308-313.

       R ONeill,
       Algorithm AS 47:
       Function Minimization Using a Simplex Procedure,
       Applied Statistics,
       Volume 20, Number 3, 1971, pages 338-345.
     */

  template<class F, class A, class H, class Xpr>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::neldermead_( F
                                  , A, H
                                  , details::optimization_settings<typename A::value_type> const&
                                  )
                      >::type
  neldermead(F f, A init, H steps, nt2::details::option_expr<Xpr> const& opt)
  {
    typename boost::dispatch::make_functor<tag::neldermead_, F>::type callee;
    return callee ( f
                  , init
                  , steps
                  , details::optimization_settings<typename A::value_type>(opt)
                  );
  }
  /// @overload
  template<class F, class A, class H> BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::neldermead_( F
                                  , A, H
                                    , details::optimization_settings<typename A::value_type> const&
                                  )
                      >::type
  neldermead(F f, A init, H steps)
  {
    typename boost::dispatch::make_functor<tag::neldermead_, F>::type callee;
    return callee ( f
                  , init
                  , steps
                  , details::optimization_settings<typename A::value_type>()
                  );
  }
}



#endif

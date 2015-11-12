//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_WHEREIJ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_WHEREIJ_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the whereij function
 **/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for whereij functor
     **/
    struct whereij_ : ext::elementwise_<whereij_>
    {
      typedef ext::elementwise_<whereij_> parent;
    };
  }

  /*!
    @brief Act as : for i for j r(i, j) = f(i, j) ? a(i, j) : b(i, j)
    @param f Binary Polymorphic Function object to apply to 0 based indices
    @param a First expression to process
    @param b Second expression to process

    see @funcref{if_else}
  **/
  template<class Functor, class A0, class A1> BOOST_FORCEINLINE
  typename meta::call<tag::whereij_(Functor const&, A0 const&, A1 const&)>::type
  whereij(Functor const& f, A0 const& a, A1 const& b)
  {
    return typename make_functor<tag::whereij_, A0>::type()(f,a,b);
  }
}

#endif

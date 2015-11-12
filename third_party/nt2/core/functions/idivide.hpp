//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_IDIVIDE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_IDIVIDE_HPP_INCLUDED

/*!
  @file
  @brief Defines the idivide function
 **/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/include/functions/round.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/divfloor.hpp>
#include <nt2/include/functions/divfix.hpp>
#include <nt2/include/functions/divceil.hpp>
#include <nt2/include/functions/divround.hpp>
#include <nt2/include/functions/divround2even.hpp>

namespace nt2
{
  namespace tag
  {
    struct idivide_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief


  **/
  template < class A0,  class A1>
  typename meta::call<tag::divfloor_(A0 const&, A1 const&)>::type
  idivide(A0 const& a, A1 const& b, const tag::floor_)
  {
    return divfloor(a, b);
  }
  template < class A0,  class A1>
  typename meta::call<tag::divceil_(A0 const&, A1 const&)>::type
  idivide(A0 const& a, A1 const& b, const tag::ceil_)
  {
    return divceil(a, b);
  }  template < class A0,  class A1>
  typename meta::call<tag::divfix_(A0 const&, A1 const&)>::type
  idivide(A0 const& a, A1 const& b, const tag::trunc_)
  {
    return divfix(a, b);
  }
  template < class A0,  class A1>
  typename meta::call<tag::divround2even_(A0 const&, A1 const&)>::type
  idivide(A0 const& a, A1 const& b, const tag::round_)
  {
    return divround(a, b);
  }
  template < class A0,  class A1>
  typename meta::call<tag::divround2even_(A0 const&, A1 const&)>::type
  idivide(A0 const& a, A1 const& b, const tag::round2even_)
  {
    return divround2even(a, b);
  }
}

#endif

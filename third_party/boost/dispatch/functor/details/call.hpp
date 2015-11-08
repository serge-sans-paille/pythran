//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_DETAILS_CALL_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_DETAILS_CALL_HPP_INCLUDED

#include <boost/dispatch/functor/forward.hpp>
#include <boost/mpl/assert.hpp>

// Forward declare the unknown_ tag
namespace boost { namespace dispatch { namespace tag { struct unknown_;    } } }

//==========================================================================
/*
 * If you get an error here, you tried to call a function not supported
 * or implemented for values of the given types.
 * Check that you included the proper toolbox or use the correct types in
 * your function call.
 */
//==========================================================================
template<class Call, class Site>
struct BOOST_DISPATCH_UNSUPPORTED_FUNCTION_CALL;

namespace boost { namespace dispatch { namespace meta
{
  // Calls to unknown functions end up as errors or as SFINAE
  template<class Site, class Dummy>
  struct implement<tag::unknown_, Site, Dummy>
  {
    //typedef BOOST_DISPATCH_UNSUPPORTED_FUNCTION_CALL<Dummy, Site> result_type;
    //BOOST_MPL_ASSERT_MSG(0, BOOST_DISPATCH_UNSUPPORTED_FUNCTION_CALL, (Dummy, Site));
  };
} } }

#endif

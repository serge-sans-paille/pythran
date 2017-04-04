//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_PROD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_PROD_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG ( ext, prod_
                            , (boost::dispatch::reduction_<prod_,multiplies_,one_>)
                            );
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, prod_)
  }

  BOOST_DISPATCH_CALLABLE_DEFINITION(tag::prod_,prod);
} }

#endif

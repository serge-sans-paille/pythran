//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_PREPROCESSOR_FUNCTION_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_PREPROCESSOR_FUNCTION_HPP_INCLUDED

#include <boost/dispatch/functor/preprocessor/function.hpp>

#define NT2_FUNCTION_IMPLEMENTATION(TAG,NAME,N)     \
BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(TAG,NAME,N)  \
/**/

#define NT2_FUNCTION_IMPLEMENTATION_TPL(TAG,NAME,ARGS,N)    \
BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(TAG,NAME,ARGS,N) \
/**/

#define NT2_FUNCTION_INTERFACE(TAG,NAME,N)    \
BOOST_DISPATCH_FUNCTION_INTERFACE(TAG,NAME,N) \
/**/

#define NT2_FUNCTION_BODY(TAG,N)    \
BOOST_DISPATCH_FUNCTION_BODY(TAG,N) \
/**/

#define NT2_FUNCTION_IMPLEMENTATION_SELF(TAG,NAME,N)    \
BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF(TAG,NAME,N) \
/**/

#define NT2_FUNCTION_METHOD_SELF(NAME,TAG,SELF)     \
BOOST_DISPATCH_FUNCTION_METHOD_SELF(NAME,TAG,SELF)  \
/**/

#endif

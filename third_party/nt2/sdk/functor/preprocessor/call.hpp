//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_PREPROCESSOR_CALL_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_PREPROCESSOR_CALL_HPP_INCLUDED

#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>

#define NT2_FUNCTOR_CALL(N) BOOST_DISPATCH_CALL(N)
#define NT2_FUNCTOR_CALL_REPEAT(N) BOOST_DISPATCH_CALL_REPEAT(N)

#define NT2_FUNCTOR_IMPLEMENTATION(Tag,Site,Types,Seq)                         \
BOOST_DISPATCH_IMPLEMENT((nt2)(ext),Tag,Site,Types,Seq)

#define NT2_FUNCTOR_IMPLEMENTATION_TPL(Tag,Site,Types,Seq)                     \
BOOST_DISPATCH_IMPLEMENT_TPL((nt2)(ext),Tag,Site,Types,Seq)

#define NT2_FUNCTOR_IMPLEMENTATION_IF(Tag,Site,Types,Cond,Seq)                 \
BOOST_DISPATCH_IMPLEMENT_IF((nt2)(ext),Tag,Site,Types,Cond,Seq)

#endif

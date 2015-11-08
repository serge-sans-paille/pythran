//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED

#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>

#define NT2_REGISTER_DISPATCH(Tag,Site,Types,Seq)                              \
BOOST_DISPATCH_REGISTER((nt2)(ext),Tag,Site,Types,Seq)

#define NT2_REGISTER_DISPATCH_TPL(Tag,Site,Types,Seq)                          \
BOOST_DISPATCH_REGISTER_TPL((nt2)(ext),Tag,Site,Types,Seq)

#define NT2_REGISTER_DISPATCH_TO(Tag,Site,Types,Seq,Ret)                       \
BOOST_DISPATCH_REGISTER_TO((nt2)(ext),Tag,Site,Types,Seq,Ret)

#define NT2_REGISTER_DISPATCH_TO_IF(Tag,Site,Types,Cond,Seq,Ret)               \
BOOST_DISPATCH_REGISTER_TO_IF((nt2)(ext),Tag,Site,Types,Cond,Seq,Ret)

#define NT2_REGISTER_DISPATCH_TO_TPL(Tag,Site,Types,Seq,Ret)                   \
BOOST_DISPATCH_REGISTER_TO_TPL((nt2)(ext),Tag,Site,Types,Seq,Ret)

#define NT2_REGISTER_DISPATCH_IF(Tag,Site,Types,Cond,Seq)                      \
BOOST_DISPATCH_REGISTER_IF((nt2)(ext),Tag,Site,Types,Cond,Seq)

#define NT2_REGISTER_DISPATCH_IF_TPL(Tag,Site,Types,Cond,Seq)                  \
BOOST_DISPATCH_REGISTER_IF_TPL((nt2)(ext),Tag,Site,Types,Cond,Seq)

#endif

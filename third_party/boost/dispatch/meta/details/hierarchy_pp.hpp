//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_HIERARCHY_PP_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_HIERARCHY_PP_HPP_INCLUDED

#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/dispatch/preprocessor/remove_typename.hpp>

//==============================================================================
// Build a simple hierarchy element
//==============================================================================
#define BOOST_DISPATCH_HIERARCHY_CLASS(Name, Parent)  \
struct Name : Parent { typedef Parent  parent; }      \
/**/

//==============================================================================
// Build a template based hierarchy element
//==============================================================================
#define BOOST_DISPATCH_HIERARCHY_CLASS_TPL(Name, Parent)            \
template<class T> struct Name : Parent { typedef Parent  parent; }  \
/**/

//==============================================================================
// Build a template based hierarchy element with a template parent
//==============================================================================
#define BOOST_DISPATCH_HIERARCHY_CLASS_TPL_META(Name, Parent)         \
template<class T> struct Name : BOOST_DISPATCH_PP_STRIP(Parent)::type \
{                                                                     \
  typedef typename BOOST_DISPATCH_PP_STRIP(Parent)::type parent;      \
}                                                                     \
/**/

//==============================================================================
// User level macro to define a new hierarchy element taking advantage of the
// type hierarchy lattice system.
//==============================================================================
#define BOOST_DISPATCH_REGISTER_HIERARCHY_PARENT(Name, Base)                    \
namespace boost { namespace dispatch                                            \
{                                                                               \
  namespace meta                                                                \
  {                                                                             \
    template<class T> struct Name : Name< typename T::parent >                  \
    {                                                                           \
      typedef Name< typename T::parent > parent;                                \
    };                                                                          \
                                                                                \
    template<class T> struct Name< unspecified_<T> > : unspecified_<T>          \
    {                                                                           \
      typedef unspecified_<T> parent;                                           \
    };                                                                          \
    template<class T> struct  Name< unknown_<T> >                               \
                            : BOOST_DISPATCH_PP_REMOVE_TYPENAME(Base)           \
    {                                                                           \
      typedef Base parent;                                                      \
    };                                                                          \
  }                                                                             \
} }                                                                             \
/**/

//==============================================================================
// Defines a classic hierarchy ending up going into unknown_
//==============================================================================
#define BOOST_DISPATCH_REGISTER_HIERARCHY(Name)             \
BOOST_DISPATCH_REGISTER_HIERARCHY_PARENT(Name, unknown_<T>) \
/**/

#endif

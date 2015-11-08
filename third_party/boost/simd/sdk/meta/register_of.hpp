//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_REGISTER_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_REGISTER_OF_HPP_INCLUDED

namespace boost { namespace simd { namespace details
{
  template<typename Type> struct register_of
  {
    typedef Type type;
  };
} } }

namespace boost { namespace simd { namespace meta
{
  template<typename Type>
  struct register_of : details::register_of<Type>
  {};

  template<typename Type>
  struct register_of<Type&> : details::register_of<Type>
  {};

  template<typename Type>
  struct register_of<Type const> : details::register_of<Type>
  {};

  template<typename Type>
  struct register_of<Type const&> : details::register_of<Type>
  {};
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_GENERATIVE_HIERARCHY_HPP_INCLUDED
#define NT2_SDK_META_GENERATIVE_HIERARCHY_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/simd/constant/hierarchy.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //==========================================================================
  // Stateful Constant node hierarchy
  //==========================================================================
  template<class Tag> struct state_constant_ : constant_<Tag>
  {
    typedef constant_<Tag> parent;
  };
} } }

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::constant_;
  using boost::dispatch::meta::pure_constant_;
  using boost::dispatch::meta::state_constant_;
} }

#endif


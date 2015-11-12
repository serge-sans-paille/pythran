//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_GENERATOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_GENERATOR_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/details/generator.hpp>
#include <nt2/core/container/dsl/details/trait_transform.hpp>
#include <boost/proto/traits.hpp>

namespace nt2 { namespace container
{
  //==========================================================================
  /*!
   * proto::transform performing the computation of the type and generation
   * of a nt2::container::expression
   **/
  //==========================================================================
  template<class Domain>
  struct  generator_transform
        : details::trait_transform< details::generator, Domain >
  {
    typedef void proto_use_basic_expr_;
  };
} }

#endif


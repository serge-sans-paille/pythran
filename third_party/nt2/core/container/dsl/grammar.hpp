//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_GRAMMAR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_GRAMMAR_HPP_INCLUDED

#include <boost/proto/matches.hpp>

namespace nt2 { namespace container
{
  /// INTERNAL ONLY
  /// NT2 grammar is matching nothing as we use an external, non grammar
  /// based system of expression validation based on incremental type resolution
  /// This allows us to control how combo of nodes are constructed and make
  /// proto usage restricted to its generic tree structure and transforms.
  typedef boost::proto::not_<boost::proto::_> grammar;
} }

#endif

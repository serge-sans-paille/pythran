//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CONSTRUCT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CONSTRUCT_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the construct function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the construct function
    **/
    struct construct_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  #if defined(DOXYGEN_ONLY)
  /*!
    @brief Extension point for container construction

    For any given  @nt2 container, construct is able to perform its initialization
    from a arbitrary number of parameters. This is called by all container
    terminal in @nt2 and handles variability of parameters through the dispatch
    system.

    @param c    Container to initialize
    @param args Arguments used to initialize said container
  **/
  template<class Container, class... Args>
  void construct(Container& c, Args&&... args);
  #else
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::construct_, construct, 2)
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::construct_, construct, 3)
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::construct_, construct, 4)
  #endif
}

#endif


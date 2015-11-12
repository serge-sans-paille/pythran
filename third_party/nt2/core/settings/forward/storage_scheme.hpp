//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_STORAGE_SCHEME_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_STORAGE_SCHEME_HPP_INCLUDED

namespace nt2
{
  /*!
      @brief Conventional storage option

      Default scheme for storing containers is the contiguous, dense storage
      scheme.
  **/
  struct conventional_;

  /*!
      @brief Packed storage option

      Packed scheme is used for sparse containers. It infers from the container
      Shape which elements to store and which to regenerate. Usually, packed
      storage reduces memory usage and may reduces runtime.
  **/
  struct packed_;

  namespace tag
  {
    /// @brief Option tag for storage_scheme options
    struct storage_scheme_;
  }
}

#endif

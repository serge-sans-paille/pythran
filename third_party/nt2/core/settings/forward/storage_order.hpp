//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_STORAGE_ORDER_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_STORAGE_ORDER_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>

namespace nt2
{
  /// @brief Column major storage option
  struct column_major_
  {
    /// INTERNAL ONLY
    template<class S, class D> struct apply : D {};
  };

  /// @brief Row major storage option
  struct row_major_
  {
    /// INTERNAL ONLY
    template<class S, class D>
    struct apply : boost::mpl::size_t<S::value - 1 - D::value> {};
  };

  typedef column_major_  matlab_order_;
  typedef column_major_  fortran_order_;
  typedef row_major_     C_order_;

  namespace tag
  {
    /// @brief Option tag for the storage order options
    struct storage_order_;
  }
}

#endif

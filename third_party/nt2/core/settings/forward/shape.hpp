//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_SHAPE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_SHAPE_HPP_INCLUDED

namespace nt2
{
  //============================================================================
  /*! The default container shape. Data are laid out in a hypercube
   *  of N dimensions and contains only non-trivial values.
   **/
  //============================================================================

  namespace details
  {
    template<const char C>
    struct shape_impl
    {
      static const char id_value = C;
    };

    template<const char C>
    const char shape_impl<C>::id_value;
  }

  struct rectangular_;
  struct upper_triangular_ : details::shape_impl<'U'> {};
  struct lower_triangular_ : details::shape_impl<'L'> {};

  template<int U, int L> struct band_diagonal_
  {
    static const int ud = U;
    static const int ld = L;
  };
  template<int U, int L>
  const int band_diagonal_<U, L>::ud;
  template<int U, int L>
  const int band_diagonal_<U, L>::ld;

  struct diagonal_            {};
  struct positive_definite_   {};
  struct uhess_               {};
  struct symmetric_           {};

  namespace tag
  {
    /// @brief Option tag for shape options
    struct shape_;
  }
}

#endif



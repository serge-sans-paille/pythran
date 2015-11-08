//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_STORAGE_SCHEME_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_STORAGE_SCHEME_HPP_INCLUDED

#include <nt2/core/settings/shape.hpp>
#include <nt2/core/settings/option.hpp>

namespace nt2
{
  /// INTERNAL ONLY
  /// In conventionnal mode, we store everything in a rectangular shape
  struct conventional_
  {
    template<class Container> struct apply
    {
      typedef typename rectangular_::apply<Container>::type type;

      template<class Size>
      static BOOST_FORCEINLINE std::size_t nnz(Size const& sz)
      {
        return rectangular_::nnz(sz);
      }
    };
  };

  /// INTERNAL ONLY
  /// In packed mode, the shape wraps the buffer and takes care of its behavior
  struct packed_
  {
    template<class Container> struct apply
    {
      typedef typename meta::option<Container, tag::shape_>::type shape_t;
      typedef typename shape_t::template apply<Container>::type   type;

      template<class Size>
      static BOOST_FORCEINLINE std::size_t nnz(Size const& sz)
      {
        return shape_t::nnz(sz);
      }
    };
  };
}

#endif

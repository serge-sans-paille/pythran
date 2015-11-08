//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_SHAPE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_SHAPE_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/buffer.hpp>
#include <nt2/core/functions/scalar/numel.hpp>

namespace nt2
{
  /*!
    @brief rectangular_ shape  option

    @c rectangular_ is used to tag a Container as being dense, i.e. containing
    no non-trivial elements.
  **/
  struct rectangular_
  {
    /*!
      @brief Deduces buffer type from shape information

      For a given @C Container, computes the buffer type required for
      said buffer to store its data.

      @tparam Container Container type used as options source
    **/
    template<typename Container> struct apply
    {
      typedef typename meta::option<Container, tag::buffer_>::type  buffer_t;
      typedef typename details::make_buffer<buffer_t>
                              ::template apply<Container>::type type;
    };

    /*!
      @brief Number of non-trivial elements

      Computes the number of non-trivial elements stored in the current
      Container.

      @param sz Extent of current Container
      @return Number of non-trivial elements to allocate
    **/
    template<typename Size> static
    BOOST_FORCEINLINE std::size_t nnz(Size const& sz)
    {
      return nt2::numel(sz);
    }
  };
}

#endif

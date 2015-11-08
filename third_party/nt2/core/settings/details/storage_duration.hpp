//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_STORAGE_DURATION_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_STORAGE_DURATION_HPP_INCLUDED

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/storage_size.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/allocator.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/array_buffer.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/fold.hpp>

namespace nt2
{
   /*!
    * Default storage duration settings.
   **/
  struct dynamic_
  {
    typedef dynamic_ storage_duration_type;

    template<typename Container, typename Alloc = void> struct apply
    {
      /*
        We build a buffer using Container value_type and a potentially
        adapted allocator
      */
      typedef typename boost::dispatch::meta::value_of<Container>::type value_t;
      typedef typename Alloc::template rebind<value_t>::other       allocator_t;
      typedef memory::buffer<value_t,allocator_t>                          type;
    };

    /// INTERNAL ONLY
    template<typename Container> struct apply<Container>
    {
      // If no allocator is specified, we compute the one from the options
      typedef typename meta::option<Container, tag::allocator_>::type alloc_t;
      typedef typename apply<Container,alloc_t>::type                 type;
    };
  };

  // When using automatic memory, we rely on array_buffer to store our data
  struct automatic_
  {
    typedef automatic_ storage_duration_type;

    template <typename Container, typename D = void>
    struct apply
    {
      typedef typename meta::option<Container, tag::storage_size_>::type size_;
      typedef typename size_::storage_size_type                        stored_;

      //*************************** STATIC ASSERT ****************************//
      //         Automatic storage option have been set for a container       //
      //          with a dynamic size. Check your container settings.         //
      //*************************** STATIC ASSERT ****************************//
      BOOST_MPL_ASSERT_MSG
      ( (stored_::value >= 0)
      , SETTINGS_MISMATCH_AUTOMATIC_STORAGE_REQUESTED_WITH_DYNAMIC_STORAGE_SIZE
      , (size_)
      );

      typedef typename boost::dispatch::meta::value_of<Container>::type value_t;
      typedef memory::array_buffer<value_t,stored_>                        type;
    };
  };
}

#endif

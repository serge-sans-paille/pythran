//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DELETER_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DELETER_HPP_INCLUDED

#include <boost/simd/memory/deallocate.hpp>
#include <boost/simd/preprocessor/parameters.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Deleter function object

    Whenever a pointer allocated using any of the SIMD aware allocation
    function is stored in a std::shared_ptr or similar object, it is necessary
    to pass this custom deleter to this object so the memory deallocation can be
    done using the proper alignment aware deallocation function.

    @tparam T Type of data to delete
    @tparam Allocator Type of allocator used for the allocation. By default, it
            is equal to @c void, meaning no allocator have been used to perform
            the allocation.
  **/
  template< class T
          , class Allocator = void
          >
  struct deleter : Allocator
  {
    typedef void result_type;
    typedef T * argument_type;

    /// Default constructor
    deleter() {}

    /// Constructs a deleter using the proper allocator
    deleter(Allocator const& x) : Allocator(x) {}

    /// Performs the deletion of the pointer @c x
    void operator()(T * x)
    {
      boost::simd::deallocate ( static_cast<Allocator&>(*this), x );
    }
  };

  /// INTERNAL ONLY
  template<class T>
  struct deleter<T>
  {
    typedef void  result_type;
    typedef T*    argument_type;

    void operator()(T * x) const
    {
      boost::simd::deallocate( x );
    }
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DYNARRAY_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DYNARRAY_HPP_INCLUDED

#include <boost/simd/memory/details/new_allocator.hpp>
#include <boost/config.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/assert.hpp>
#include <algorithm>
#include <iterator>
#include <cstddef>

namespace boost { namespace simd
{
  /*!
    @brief Runtime sized array

    Similar to std::vector, but without the ability to change the
    size and without allocators.

    @tparam T     Type of the stored element
  **/
  template<class T>
  struct dynarray
       : boost::iterator_range<T*>
  {
    dynarray(std::size_t n)
    {
      T* ptr = new T[n];
      *static_cast<boost::iterator_range<T*>*>(this) = boost::iterator_range<T*>(ptr, ptr+n);
    }

    dynarray(dynarray const& other)
    {
      void* mem = details::new_array_allocate_impl<T>(other.size()*sizeof(T), 0);
      T* ptr = static_cast<T*>(mem);
      *static_cast<boost::iterator_range<T*>*>(this) = boost::iterator_range<T*>(ptr, ptr+other.size());
      #ifndef BOOST_NO_EXCEPTIONS
      try
      {
      #endif

      #if BOOST_WORKAROUND(BOOST_MSVC, >= 1400) && BOOST_WORKAROUND(BOOST_MSVC, < 1600)
        stdext::unchecked_uninitialized_copy(other.begin(), other.end(), this->begin());
      #elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)
        std::uninitialized_copy(other.begin(), other.end(), stdext::make_unchecked_array_iterator(this->begin()));
      #else
        std::uninitialized_copy(other.begin(), other.end(), this->begin());
      #endif

      #ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
        details::new_array_deallocate_impl<T>(mem);
        throw;
      }
      #endif
    }

    dynarray& operator=(dynarray const& other)
    {
      BOOST_ASSERT_MSG( this->size() == other.size(), "assignment between dynarrays of different sizes" );

    #if BOOST_WORKAROUND(BOOST_MSVC, >= 1400) && BOOST_WORKAROUND(BOOST_MSVC, < 1600)
      stdext::unchecked_copy(other.begin(), other.end(), this->begin());
    #elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)
      std::copy(other.begin(), other.end(), stdext::make_unchecked_array_iterator(this->begin()));
    #else
      std::copy(other.begin(), other.end(), this->begin());
    #endif

      return *this;
    }

    // cast because of boost bug #8061
    std::size_t size() const
    {
      return (std::size_t)static_cast<boost::iterator_range<T*> const*>(this)->size();
    }

    ~dynarray()
    {
      delete[] this->begin();
    }
  };
} }

#endif

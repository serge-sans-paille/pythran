//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_ARRAY_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_ARRAY_HPP_INCLUDED

#include <boost/simd/preprocessor/align_on.hpp>
#include <boost/simd/forward/aligned_array.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>

#include <boost/swap.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/throw_exception.hpp>

#include <iterator>
#include <stdexcept>

namespace boost { namespace simd
{
  #if !defined(DOXYGEN_ONLY)
  template<class T, std::size_t N, std::size_t Align>
  struct aligned_array_data
  {
    BOOST_MPL_ASSERT_MSG( (sizeof(T) == 0)
                        , NON_SUPPORTED_ALIGNMENT_FOR_ARRAY
                        , (aligned_array_data)
                        );
  };

  #define M0(z,n,t)                                                            \
  template<class T, std::size_t N>                                             \
  struct aligned_array_data<T, N, n>                                           \
  {                                                                            \
    T BOOST_SIMD_ALIGN_ON(n) data[N];                                          \
  };                                                                           \
  /**/
  BOOST_SIMD_PP_REPEAT_POWER_OF_2_BIG(M0,~)
  #undef M0

  #endif

  /*!
    @brief Statically sized aligned array

    Defines an object which contains @c N elements of type @c T in a statically
    allocated array which address is aligned on @c Align.

    @usage{memory/aligned_array.cpp}

    @tparam T     Type of the stored element
    @tparam N     Number of elements
    @tparam Align Alignment boundary.
  **/
  template<class T, std::size_t N, std::size_t Align>
  struct aligned_array
  {
    /// INTERNAL ONLY
    aligned_array_data<T, N, Align> data_;

    typedef T              value_type;
    typedef T*             iterator;
    typedef const T*       const_iterator;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    /// Return an iterator to the beginning of the array
    iterator        begin()       { return this->data_.data; }

    /// @overload
    const_iterator  begin() const { return this->data_.data; }

    /// Return an iterator to the end of the array
    iterator        end()       { return this->data_.data+N; }

    /// @overload
    const_iterator  end() const { return this->data_.data+N; }

    /// Return a constant iterator to the beginning of the array
    const_iterator cbegin() const { return this->data_.data; }

    /// Return a constant iterator to the end of the array
    const_iterator cend() const { return this->data_.data+N; }

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    /// Return a reverse_iterator to the end of the array
    reverse_iterator rbegin() { return reverse_iterator(end()); }

    /// @overload
    const_reverse_iterator rbegin()  const { return const_reverse_iterator(end()); }

    /// Return a reverse_iterator to the beginning of the array
    reverse_iterator       rend()       { return reverse_iterator(begin()); }

    /// @overload
    const_reverse_iterator rend()  const { return const_reverse_iterator(begin()); }

    /// Return a constant reverse iterator to the beginning of the array
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }

    /// Return a constant reverse iterator to the end of the array
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    /// Random access to the ith element of the array
    reference operator[](size_type i)
    {
      BOOST_ASSERT_MSG( i < N, "out of range" );
      return this->data_.data[i];
    }

    /// @overload
    const_reference operator[](size_type i) const
    {
      BOOST_ASSERT_MSG( i < N, "out of range" );
      return this->data_.data[i];
    }

    /// Random access to the ith element of the array with out-of-range check.
    reference       at(size_type i)       { rangecheck(i); return this->data_.data[i]; }

    /// @overload
    const_reference at(size_type i) const { rangecheck(i); return this->data_.data[i]; }

    /// Return the first element of the array
    reference       front()       { return this->data_.data[0]; }

    /// @overload
    const_reference front() const { return this->data_.data[0]; }

    /// Return the last element of the array
    reference       back()        { return this->data_.data[N-1]; }

    /// @overload
    const_reference back()  const { return this->data_.data[N-1]; }

    /// Return the number of elements of the array.
    static size_type size()     { return N;     }

    /// Notifies if the array is empty.
    static bool      empty()    { return false; }

    /// Return the maximum number of elements the array can contain.
    static size_type max_size() { return N;     }

    /// Compile-time size of the array
    static const std::size_t static_size = N;

    /// Swap the contents of the current array's elements with another array.
    template<std::size_t A2>
    void swap (aligned_array<T,N,A2>& y)
    {
      for (size_type i = 0; i < N; ++i)
        boost::swap(this->data_.data[i],y.data_.data[i]);
    }

    /// Return a pointer referencing the array's data
    T* c_array() { return this->data_.data; }

    /// Return a pointer referencing the array's data
    T* data()       { return this->data_.data; }

    /// @overload
    const T* data() const { return this->data_.data; }

    /// Assign the contents of another array to the current array
    template <typename T2, std::size_t A2>
    aligned_array<T,N,Align>& operator= (const aligned_array<T2,N,A2>& rhs)
    {
      std::copy(rhs.begin(),rhs.end(), begin());
      return *this;
    }

    /// Assign one value to all elements of the array
    void assign (const T& value) { fill ( value ); }

    /// Assign one value to all elements of the array
    void fill   (const T& value) { std::fill_n(begin(),size(),value); }

    /// INTERNAL ONLY
    #if !defined(BOOST_NO_EXCEPTIONS)
    static void rangecheck(size_type ) {}
    #else
    static void rangecheck(size_type i)
    {
      if (i >= size())
        BOOST_THROW_EXCEPTION(std::out_of_range("array<>: index out of range"));
    }
    #endif
  };

  /// Swap the contents of two aligned arrays
  template<class T, std::size_t N, std::size_t A1, std::size_t A2>
  void swap( aligned_array<T,N,A1>& a1, aligned_array<T,N,A2>& a2 )
  {
    a1.swap(a2);
  }
} }

#endif

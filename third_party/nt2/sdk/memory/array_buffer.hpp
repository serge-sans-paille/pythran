//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_ARRAY_BUFFER_HPP_INCLUDED
#define NT2_SDK_MEMORY_ARRAY_BUFFER_HPP_INCLUDED

#include <nt2/sdk/memory/adapted/array_buffer.hpp>
#include <boost/simd/preprocessor/aligned_type.hpp>
#include <boost/swap.hpp>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/detail/iterator.hpp>
#include <boost/detail/workaround.hpp>
#include <cstddef>
#include <algorithm>

//==============================================================================
// Remove some MSVC warning on some nitpick in array_buffer implementation
//==============================================================================
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4510)
#pragma warning(disable:4610)
#endif

namespace nt2 {  namespace memory
{
  //============================================================================
  /**!
   * @brief array_buffer is a statically-sized sequence using automatic storage.
   *
   * array_buffer design is based on boost::array_buffer except that :
   *  - data are aligned for SIMDization purpose
   *  - its type interface is usable within MPL lambda
   **/
  //============================================================================
  template<class T, class Size> class array_buffer
  {
  private:
    BOOST_SIMD_ALIGNED_TYPE(T) elems[Size::value ? Size::value : 1u];

  public:
    struct allocator_type {};
    typedef T                                     value_type;
    typedef T&                                    reference;
    typedef const T&                              const_reference;
    typedef T*                                    iterator;
    typedef const T*                              const_iterator;
    typedef T*                                    pointer;
    typedef const T*                              const_pointer;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::size_t                           size_type;
    typedef std::ptrdiff_t                        difference_type;

    static const std::size_t static_size = Size::value;

    array_buffer() {}
    array_buffer( allocator_type const& ) {}

    // iterator support
    iterator        begin()       { return elems;             }
    iterator        end()         { return elems+static_size; }

    const_iterator  begin() const { return elems;             }
    const_iterator  end()   const { return elems+static_size; }

    reverse_iterator rbegin()     { return reverse_iterator(end());   }
    reverse_iterator rend()       { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const
    {
      return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const
    {
      return const_reverse_iterator(begin());
    }

    // operator[]
    inline reference operator[](size_type i)
    {
      BOOST_ASSERT_MSG( is_safe(i), "Out of range acces on array_buffer" );
      return elems[i];
    }

    inline const_reference operator[](size_type i) const
    {
      BOOST_ASSERT_MSG( is_safe(i), "Out of range acces on array_buffer" );
      return elems[i];
    }

    static BOOST_FORCEINLINE bool is_safe(size_type p)
    {
      return  (Size::value && p < size()) || !(Size::value || p );
    }


    static void resize( size_type )     {}

    static size_type size()     { return static_size; }
    static bool empty()         { return false;       }
    static size_type max_size() { return static_size; }

    template<typename Buffer> void swap(Buffer& that)
    {
      BOOST_ASSERT_MSG( size() == that.size()
                      , "Incompatible size in swap"
                      );

      for(size_type i=0; i<static_size; ++i)
        boost::swap(elems[i],that[i]);
    }

    const_pointer  raw() const { return elems; }
    pointer        raw()       { return elems; }
  };

  //============================================================================
  /**!
   * Perform the equality comparison of two array_buffer
   **/
  //============================================================================
  template<class T, class S>
  bool operator== (const array_buffer<T,S>& x, const array_buffer<T,S>& y)
  {
    return std::equal(x.begin(), x.end(), y.begin());
  }

  //============================================================================
  /**!
   * Perform the inequality comparison of two array_buffer
   **/
  //============================================================================
  template<class T, class S>
  bool operator!= (const array_buffer<T,S>& x, const array_buffer<T,S>& y)
  {
    return !(x==y);
  }

  //============================================================================
  /**!
   * Perform the lexicographical comparison of two array_buffer
   **/
  //============================================================================
  template<class T, class S>
  bool operator< (const array_buffer<T,S>& x, const array_buffer<T,S>& y)
  {
    return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
  }
  template<class T, class S>
  bool operator> (const array_buffer<T,S>& x, const array_buffer<T,S>& y)
  {
    return y<x;
  }

  template<class T, class S>
  bool operator<= (const array_buffer<T,S>& x, const array_buffer<T,S>& y)
  {
    return !(y<x);
  }

  template<class T, class S>
  bool operator>= (const array_buffer<T,S>& x, const array_buffer<T,S>& y)
  {
    return !(x<y);
  }

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and size
   * \param x First \c array_buffer to swap
   * \param y Second \c array_buffer to swap
   **/
  //============================================================================
  template<class T, class S> inline
  void swap (array_buffer<T,S>& x, array_buffer<T,S>& y)  { x.swap(y); }
} }

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
# pragma warning(pop)
#endif

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_LOCAL_PTR_HPP_INCLUDED
#define NT2_SDK_MEMORY_LOCAL_PTR_HPP_INCLUDED

#include <cstddef>
#include <boost/swap.hpp>
#include <boost/noncopyable.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /**!
   * @brief local_ptr is a lightweight exception safe pointer holder
   **/
  //===========================================================================
  template<class T, class Deleter>
  class local_ptr : boost::noncopyable
  {
    public:
    typedef T* pointer;

    local_ptr(pointer p, Deleter a) : pointee_(p), deleter_(a) {}

    ~local_ptr() { deleter_(pointee_); }

    pointer release()
    {
      pointer p = pointee_;
      pointee_ = 0;

      return p;
    }

    pointer get() const { return pointee_;  }

    void swap(local_ptr& that)
    {
      boost::swap(pointee_, that.pointee_);
      boost::swap(deleter_, that.deleter_);
    }

    private:
    pointer pointee_;
    Deleter deleter_;
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   * \param x First \c pointer_buffer to swap
   * \param y Second \c pointer_buffer to swap
   **/
  //============================================================================
  template<class T, class D> inline
  void swap(local_ptr<T,D>& x, local_ptr<T,D>& y)
  {
    x.swap(y);
  }
} }

#endif

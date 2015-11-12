//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_OUTPUT_ITERATOR_BASE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_OUTPUT_ITERATOR_BASE_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace boost { namespace simd { namespace details
{
  template< typename Iterator
          , std::size_t C, typename Value
          , typename Store
          >
  struct  output_iterator_base
        : boost::iterator_adaptor< output_iterator_base<Iterator,C,Value,Store>
                                 , Iterator
                                 , pack<Value, C>
                                 , std::random_access_iterator_tag
                                 , output_iterator_base<Iterator,C,Value,Store> const
                                 >
  {
    static const typename output_iterator_base::difference_type cardinal = C;
    BOOST_FORCEINLINE output_iterator_base()
                    : output_iterator_base::iterator_adaptor_()
    {}

    BOOST_FORCEINLINE explicit
    output_iterator_base( Iterator p )
                        : output_iterator_base::iterator_adaptor_(p)
    {}

    /*
      SIMD output iterator requires a proxy reference to be returned.
      For performance purpose, the iterator itself acts as its own proxy.
    */
    template<class Expr> BOOST_FORCEINLINE
    output_iterator_base const& operator=(Expr const& right) const
    {
      dispatch::functor<Store> callee;
      callee(right, &*this->base());
      return *this;
    }

    protected:
    friend class boost::iterator_core_access;

    BOOST_FORCEINLINE
    typename output_iterator_base::reference dereference() const
    {
      return *this;
    }

    BOOST_FORCEINLINE  void increment() { this->base_reference() += C; }
    BOOST_FORCEINLINE  void decrement() { this->base_reference() -= C; }

    BOOST_FORCEINLINE
    void advance(typename output_iterator_base::difference_type n)
    {
      this->base_reference() += n*C;
    }

    BOOST_FORCEINLINE typename output_iterator_base::difference_type
    distance_to(output_iterator_base const& other) const
    {
      return (other.base() - this->base()) / cardinal;
    }
  };
} } }

#endif

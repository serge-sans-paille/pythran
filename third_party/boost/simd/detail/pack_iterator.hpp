//==================================================================================================
/*!
  @file

  Defines iterators for pack

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_PACK_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_PACK_ITERATOR_HPP_INCLUDED

#include <boost/iterator/iterator_facade.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <iterator>

namespace boost { namespace simd { namespace detail
{

  namespace {
    template <typename Pack>
    using ref_constness =
      typename std::conditional< !std::is_const<Pack>::value
                               , typename Pack::reference
                               , typename Pack::const_reference
                               >::type;
  }

template <typename Pack>
class pack_iterator
    : public boost::iterator_facade< pack_iterator<Pack>
                                   , typename Pack::value_type
                                   , std::random_access_iterator_tag
                                   , ref_constness<Pack>
                                   >
  {
    private:
    friend Pack;

    explicit BOOST_FORCEINLINE pack_iterator(Pack* pack) BOOST_NOEXCEPT
      : pack_(pack), idx_(0)
    {
    }

    explicit BOOST_FORCEINLINE pack_iterator(Pack* pack, std::size_t idx) BOOST_NOEXCEPT
      : pack_(pack), idx_(idx)
    {
    }

    private:
    friend class boost::iterator_core_access;

    BOOST_FORCEINLINE void increment() BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(idx_+1 <= pack_->size(), "pack_iterator index out of bound (> size)");
      idx_ += 1;
    }

    BOOST_FORCEINLINE void decrement() BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(idx_ != 0, "pack_iterator index out of bound (< 0)");
      idx_ -= 1;
    }

    BOOST_FORCEINLINE bool equal(pack_iterator const& other) const BOOST_NOEXCEPT
    {
      return idx_ == other.idx_;
    }

    BOOST_FORCEINLINE void advance(int n) BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( idx_+n <= pack_->size()
                      , "pack_iterator index out of bound (> size || < 0)"
                      );
      idx_ += n;
    }

    BOOST_FORCEINLINE std::ptrdiff_t distance_to(pack_iterator const& other) const BOOST_NOEXCEPT
    {
      return static_cast<std::ptrdiff_t>(other.idx_ - idx_);
    }

    BOOST_FORCEINLINE ref_constness<Pack> dereference() const
    {
      return (*pack_)[idx_];
    }

    private:
    Pack* pack_;
    std::size_t idx_;
  };
} } }

#endif

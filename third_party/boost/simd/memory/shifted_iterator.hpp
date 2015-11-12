//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_SHIFTED_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_SHIFTED_ITERATOR_HPP_INCLUDED

#include <boost/simd/forward/shifted_iterator.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/memory/align_on.hpp>
#include <boost/simd/meta/region.hpp>
#include <boost/simd/sdk/simd/meta/native_cardinal.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/array.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/int.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Sliding window base SIMD iterator adapter

    shifted_iterator adapts an Iterator

    @tparam Iterator Iterator type to adapt
    @tparam Region   Region of Interest descriptor for the sliding window
    @tparam C        SIMD register cardinal to use
  **/
  template<typename Iterator, typename Region, std::size_t C>
  struct  shifted_iterator
        : public
          boost::iterator_facade< shifted_iterator<Iterator, Region, C>
                                , boost::array
                                  < pack<typename std::iterator_traits<Iterator>::value_type,C>
                                  , Region::width
                                  > const
                               , boost::forward_traversal_tag
                               >
  {
    public:
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    typedef pack<value_type,C>                                  pack_type;
    typedef shifted_iterator<Iterator, Region, C>               derived_type;
    typedef boost::array<pack_type, Region::width>              sequence_type;

    static const std::size_t cardinal = C;

    explicit shifted_iterator(Iterator p) : base(p) { }

    protected:

    /// INTERNAL ONLY - CT-recursive filling of the iterator data
    template<int N> inline void fill(  boost::mpl::int_<N> const& ) const
    {
      seq[N] = aligned_load<pack_type,N+Region::w_min>(&*base+N+Region::w_min);
      fill(boost::mpl::int_<N+1>());
    }

    /// INTERNAL ONLY
    inline void fill(boost::mpl::int_<Region::width> const&) const {}

    /// INTERNAL ONLY
    inline void fill() const { fill( boost::mpl::int_<0>() ); }

    private:
    friend class boost::iterator_core_access;

    /// INTERNAL ONLY - required by iterator_facade
    inline void increment()
    {
      base += C;
    }

    /// INTERNAL ONLY - required by iterator_facade
    inline bool equal(derived_type const& other) const
    {
      return (this->base == other.base);
    }

    /// INTERNAL ONLY - required by iterator_facade
    inline sequence_type const& dereference() const
    {
      fill();
      return seq;
    }

    Iterator              base;
    mutable sequence_type seq;
  };

  /*!
    @brief Adapter for SIMD sliding window iterator

    Convert an existing iterator referencing the beginning of a contiguous
    memory block into a SIMD aware read-only iterator returning a sliding
    window of SIMD registers.

    @usage_output{memory/shifted_iterator.cpp,memory/shifted_iterator.out}

    @tparam C Width of the SIMD register to use as iteration value.

    @param p Iterator to adapt.

    @return An instance of shifted_iterator
  **/
  template<std::size_t C, typename Iterator, typename Region>
  inline shifted_iterator<Iterator, Region, C>
  shifted_begin(Iterator p, Region const& )
  {
    return shifted_iterator<Iterator, Region, C>(p+(Region::width/2)*C);
  }

  /*!
    @brief Adapter for SIMD sliding window iterator

    Convert an existing iterator referencing the end of a contiguous
    memory block into a SIMD aware read-only iterator returning a sliding
    window of SIMD registers.

    @usage_output{memory/shifted_iterator.cpp,memory/shifted_iterator.out}

    @tparam C Width of the SIMD register to use as iteration value.

    @param p Iterator to adapt.

    @return An instance of shifted_iterator
  **/
  template<std::size_t C, typename Iterator, typename Region>
  inline shifted_iterator<Iterator, Region, C>
  shifted_end(Iterator p, Region const& )
  {
    return shifted_iterator<Iterator, Region, C>(p-(Region::width/2)*C);
  }

  /*!
    @brief Adapter for SIMD sliding window iterator

    Convert an existing iterator referencing the beginning of a contiguous
    memory block into a SIMD aware read-only iterator returning a sliding
    window of SIMD registers.

    @usage_output{memory/shifted_iterator.cpp,memory/shifted_iterator.out}

    @param p Iterator to adapt.
    @param r The Region of Interest descriptor of the sliding window.

    @return An instance of shifted_iterator
  **/
  template<typename Iterator, typename Region>
  inline shifted_iterator<Iterator, Region>
  shifted_begin(Iterator p, Region const& r)
  {
    return shifted_begin<shifted_iterator<Iterator, Region>::cardinal>(p,r);
  }

  /*!
    @brief Adapter for SIMD sliding window iterator

    Convert an existing iterator referencing the end of a contiguous
    memory block into a SIMD aware read-only iterator returning a sliding
    window of SIMD registers.

    @usage_output{memory/shifted_iterator.cpp,memory/shifted_iterator.out}

    @param p Iterator to adapt.
    @param r The Region of Interest descriptor of the sliding window.

    @return An instance of shifted_iterator
  **/
  template<typename Iterator, typename Region>
  inline shifted_iterator<Iterator, Region>
  shifted_end(Iterator p, Region const& r)
  {
    return shifted_end<shifted_iterator<Iterator, Region>::cardinal>(p,r);
  }
} }

#endif

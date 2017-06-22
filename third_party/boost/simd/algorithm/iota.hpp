//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_IOTA_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_IOTA_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/function/enumerate.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/as.hpp>
#include <boost/simd/pack.hpp>
#include <iterator>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Fills the range [first, last) with sequentially increasing values,
    starting with seed  and repetitively evaluating value += step.

    @param first  Beginning of the range of elements
    @param last   End of the range of elements
    @param seed   initial value to store
    @param step   value to add (default to 1)

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.

    @par Example:

      @snippet iota.cpp iota

    @par Possible output:

      @snippet iota.txt iota
  **/
  template<typename T,  typename T1,  typename T2>
  void iota(T * first, T * last, T1 seed, T2 step)
  {
    // Scalar seeder
    struct sg
    {
      sg(T1 seed, T2 step) : i_(seed),  step_(step) {}
      T operator()() { auto z = i_; i_+= step_; return z; }
      T i_, step_;
    };

    // SIMD seeder
    struct vg
    {
      using p_t =  pack<T>;
      vg(T1 seed, T2 step) : i_(bs::enumerate<p_t>(seed, step)), step_(step) {}
      p_t operator()() { auto z = i_; i_+=step_*p_t::static_size; return z; }
      p_t i_, step_;
    };

    auto pr = segmented_aligned_range(first,last);

    sg gg0(seed, step);
    std::generate(pr.head.begin(), pr.head.end(), gg0);

    // This lambda wrapping is not useless, it prevent MSVC bitching about passing gg1
    // by value while it stores a pack :| and hence is not aligned for the stack
    seed += std::distance(pr.head.begin(), pr.head.end());
    vg gg1(seed, step);
    std::generate(pr.body.begin(), pr.body.end(), [&gg1](){ return gg1(); } );

    seed += std::distance(pr.body.begin(), pr.body.end())*pack<T>::static_size;
    sg gg2(seed, step);
    std::generate(pr.tail.begin(), pr.tail.end(), gg2);
  }

  /*!
    @ingroup group-algo

    Fills the range [first, last) with sequentially increasing values starting with seed.

    @param first  Beginning of the range of elements
    @param last   End of the range of elements
    @param seed   initial value to store

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.

    @par Example:

      @snippet iota.cpp iota

    @par Possible output:

      @snippet iota.txt iota
  **/
  template<typename T,  typename T1> void iota(T * first, T * last, T1 seed)
  {
    // Scalar seeder
    struct sg
    {
      sg(T1 seed) : i_(seed) {}
      T operator()() { return i_++; }
      T i_;
    };

    // SIMD seeder
    struct vg
    {
      using p_t =  pack<T>;
      vg(T seed) : i_(bs::enumerate<p_t>(seed)) {}
      p_t operator()() { auto z = i_; i_+= p_t::static_size; return z; }
      p_t i_;
    };

    auto pr = segmented_aligned_range(first,last);

    sg gg0(seed);
    std::generate(pr.head.begin(), pr.head.end(), gg0 );

    seed += std::distance(pr.head.begin(), pr.head.end());
    vg gg1(seed);
    std::generate(pr.body.begin(), pr.body.end(), [&gg1](){ return gg1(); });

    seed += std::distance(pr.body.begin(), pr.body.end())*pack<T>::static_size;
    sg gg2(seed);
    std::generate(pr.tail.begin(), pr.tail.end(), gg2 );
  }
} }

#endif

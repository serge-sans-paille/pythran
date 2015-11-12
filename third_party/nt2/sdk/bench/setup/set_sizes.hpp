//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_SETUP_SET_SIZES_HPP_INCLUDED
#define NT2_SDK_BENCH_SETUP_SET_SIZES_HPP_INCLUDED
#include <vector>
namespace nt2 { namespace bench
{
  /*!
    @brief Progress through a vector of user defined sizes

    set_sizes is a function object suitable for initializing experiment
    with a value following a set_sizes progression of step @c s
    between @c mn and @c mx.
  **/
  template <class T>
  struct set_sizes
  {
    /*
      Initialize an set_sizes progression.

      @param s  std::vector<T> of the required steps
    */
    set_sizes( std::vector<T> const& s )
              : step_(s), min_(s[0]), num_iter_(s.size())
    {count=0;}

    /// @brief Type returned by a call to set_sizes
    typedef T result_type;

    /// @brief Current value of the progression
    inline result_type operator()() const { return min_; }

    /// @brief Update progression state
    inline void step()        {++count; min_ = step_[count]; }

    /// @brief Status of the progression
    inline bool done() const  { return count >= num_iter_; }

    private:
    std::vector<T> step_;
    T min_;
    std::size_t count, num_iter_;
  };
} }

#endif

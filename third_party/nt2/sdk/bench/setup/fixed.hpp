//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_SETUP_FIXED_HPP_INCLUDED
#define NT2_SDK_BENCH_SETUP_FIXED_HPP_INCLUDED

namespace nt2 { namespace bench
{
  /*!
    @brief Constant value setup

    fixed_ is a function object suitable for initializing experiment
    with a constant value.

    @tparam Type of the constant
  **/
  template<typename T>
  struct fixed_
  {
    /*!
      Initialize a fixed_ object from a value

      @param v value to use as seed
    **/
    inline fixed_(T const& v) : v_(v) {}

    /// @brief Type returned by a call to fixed_
    typedef T result_type;

    /// @brief Current value of the constant
    inline result_type operator()() const { return v_; }

    /// @brief Update state
    inline void step()        {}

    /// @brief Status of the constant
    inline bool done() const  { return true; }

    private:
    T v_;
  };

  template<typename T> inline fixed_<T> fixed(T const& v)
  {
    return fixed_<T>(v);
  }
} }

#endif

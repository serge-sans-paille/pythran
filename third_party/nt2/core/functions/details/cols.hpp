//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_COLS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_COLS_HPP_INCLUDED

#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace tag { struct cols_; } }

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY
  /// Functor used to generate cols values
  template<class Base> struct constant_<nt2::tag::cols_, Base>
  {
    typedef Base                                          base_type;

    constant_()                   : start_(Base())  {}
    constant_(const Base & start) : start_(start)   {}

    template<class Pos, class Size,class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const& p, Size const& sz, Target const&) const
    {
      typedef typename Target::type               type;
      typedef typename meta::as_index<type>::type i_t;

      return  splat<type>(as_subscript(sz,enumerate<i_t>(p))[1])
            + splat<type>(start_);
    }

    template<class Pos,class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const&, _0D const&, Target const&) const
    {
      typedef typename Target::type               type;
      return splat<type>(start_);
    }

    private :
    Base start_;
  };
} }

#endif

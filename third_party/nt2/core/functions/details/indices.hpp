//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_INDICES_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_INDICES_HPP_INCLUDED

#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace tag { struct indices_; } }

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY
  /// Functor used to generate cif values
  template<class Base> struct constant_<nt2::tag::indices_, Base>
  {
    typedef Base                                          base_type;

    constant_() {}
    constant_(std::size_t d, std::ptrdiff_t b) : dim_(d-1), base_(b)  {}

    template<class Pos, class Size,class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const& p, Size const&sz, Target const&) const
    {
      typedef typename Target::type                                       type;
      typedef typename meta::as_index<type>::type                         i_t;
      typedef typename nt2::result_of::as_subscript<Size,i_t>::type       s_t;

      s_t const pos = as_subscript(sz,nt2::enumerate<i_t>(p));

      return (dim_ >= pos.size()) ? nt2::splat<type>(base_)
                                  : splat<type>(pos[dim_]) + splat<type>(base_);
    }

    private:
    std::size_t     dim_;
    std::ptrdiff_t  base_;
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_REPNUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_REPNUM_HPP_INCLUDED

#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>

namespace nt2 { namespace tag { struct repnum_; }}

namespace nt2 { namespace meta
{
  template<typename Base>
  struct constant_<tag::repnum_,Base>
  {
    typedef Base base_type;

    constant_ () {}
    constant_(const Base& val)  : val_(val) {}

    template<class Pos, class Size, class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const&, Size const&, Target const& ) const
    {
      return nt2::splat<typename Target::type>(val_);
    }

    private:
    Base val_;
  };
} }

#endif

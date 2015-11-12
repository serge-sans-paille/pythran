//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_LOGSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_LOGSPACE_HPP_INCLUDED

#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/exp10.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>

namespace nt2 { namespace tag { struct logspace_; }}

namespace nt2 { namespace meta
{
  template<typename Base> struct constant_<tag::logspace_,Base>
  {
    typedef Base                        base_type;

    constant_() {}
    constant_( Base const& l, Base const& u, std::size_t n )
      : lower_(n != 1?l:u), step_(n != 1?(u-l)/Base(n-1):Base(0))
    {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;
      return nt2::exp10 ( nt2::fma( nt2::enumerate<type>(p)
                                  , nt2::splat<type>(step_)
                                  , nt2::splat<type>(lower_)
                                  )
                        );
    }

    Base lower_, step_;
  };
} }

#endif

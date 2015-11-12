//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_PISPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_PISPACE_HPP_INCLUDED

#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/exp10.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/constants/log10_pi.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>

namespace nt2 { namespace tag { struct pispace_; }}

namespace nt2 { namespace meta
{
  //============================================================================
  // pispace actual functor : precompute step and just iterate over
  //============================================================================
  template<typename Base> struct constant_<tag::pispace_,Base>
  {
    typedef Base                                         base_type;
    constant_ () {}
    constant_ ( Base const& l, std::size_t n )
              : lower_(l), step_((Log10_pi<Base>()-l)/(n-1))
    {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;

      return nt2::exp10(nt2::fma( nt2::enumerate<type>(p)
                                , nt2::splat<type>(step_)
                                , nt2::splat<type>(lower_)
                                ) );
    }

    Base lower_, step_;
  };
} }

#endif

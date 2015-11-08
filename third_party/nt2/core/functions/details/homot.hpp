//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_HOMOT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_HOMOT_HPP_INCLUDED

#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace tag { struct homot_; }}

namespace nt2 { namespace meta
{
  template<typename Base> struct constant_<tag::homot_,Base>
  {
    typedef Base base_type;

    constant_ () {}
    constant_(const Base& val)  : val_(val) {}

    template<class Pos, class Size, class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const&p , Size const& sz, Target const& ) const
    {
      typedef typename Target::type                                        type;
      typedef typename meta::as_index<type>::type                           i_t;
      typedef typename meta::
                       call<nt2::tag::enumerate_(Pos,meta::as_<i_t>)>::type p_t;
      typedef typename nt2::result_of::as_subscript<Size,p_t>::type         s_t;

      // Retrieve 2D position from the linear index
      s_t const pos = as_subscript(sz,nt2::enumerate<i_t>(p));

      // Return a diagonal of val_
      return nt2::if_else_zero(nt2::eq(pos[0],pos[1]), splat<type>(val_));
    }
    template<class Pos,class Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const& p, _1D const&, Target const&) const
    {
      typedef typename Target::type type;
      return nt2::if_else_zero(nt2::is_eqz(p), splat<type>(val_));
    }

    private:
    Base val_;
  };
} }

#endif

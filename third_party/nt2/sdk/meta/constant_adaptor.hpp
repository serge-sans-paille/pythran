//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_CONSTANT_ADAPTOR_HPP_INCLUDED
#define NT2_SDK_META_CONSTANT_ADAPTOR_HPP_INCLUDED

#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>

namespace nt2 { namespace meta
{
  /*!
    @brief Adapt a tag to be a generative-compliant functor

    Generative functions require its embedded functor to have a very specific
    interface:
      * it exposes a default_type that contains the value expected as an output
      * a ternary operator() taking a Position,Size and actual Target that
        computes the actual value to store.

    constant_ acts as a variation point to turn regular constant functor into
    a type generative function can handle.

    @tparam Functor Functor tag to implement
    @tparam Base    Type of the expected output.
   **/
  template<typename Functor, typename Base> struct constant_
  {
    /// INTERNAL ONLY
    typedef typename Functor::default_type                        default_type;

    /// INTERNAL ONLY
    typedef typename meta::call<Functor(meta::as_<Base>)>::type   base_type;

    /// INTERNAL ONLY
    template<typename Pos, typename Size, typename Target>
    BOOST_FORCEINLINE typename Target::type
    operator()(Pos const&, Size const&, Target const& ) const
    {
      // Type casting constants need to recompute their input target or
      // the wrong specialization is called.
      typedef typename boost::dispatch::meta
                             ::factory_of< Target
                                         , typename boost::dispatch::meta
                                                         ::scalar_of<Target>::type
                                         >::type factory_t;

      typedef typename factory_t::template apply<Base>::type target_type;

      typename boost::dispatch::make_functor<Functor,Base>::type callee;
      return callee(target_type());
    }
  };
} }

#endif

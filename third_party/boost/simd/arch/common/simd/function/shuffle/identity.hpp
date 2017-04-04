//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_IDENTITY_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_IDENTITY_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/shuffle.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    // ---------------------------------------------------------------------------------------------
    // Check if pattern is [0 1 ... C-1]
    template<int... Ps>
    struct  is_identity
          : nsm::all< nsm::transform< nsm::range<int,0,sizeof...(Ps)>
                                            , nsm::integral_list<int,Ps...>
                                            , nsm::equal_to<nsm::_1,nsm::_2>
                                            >
                      >
    {};
  }

  // -----------------------------------------------------------------------------------------------
  // Identity pattern hierarchies
  template<typename P> struct identity_ : P
  {
    using parent = P;
  };

  // -----------------------------------------------------------------------------------------------
  // Identity matcher - do nothing but return its argument
  struct identity_shuffle
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, boost::simd::identity_<P> const&)
    {
      return a0;
    }
  };
} }

namespace boost { namespace dispatch { namespace ext
{
  // -----------------------------------------------------------------------------------------------
  // Hierarchize identity patterns
  template<int... Ps,typename Origin>
  struct pattern_hierarchy< boost::simd::detail::pattern_<Ps...>,Origin
                          , typename std::enable_if < simd::detail::is_identity<Ps...>::type::value
                                                    >::type
                          >
  {
    using type = boost::simd::identity_<boost::simd::detail::pattern_<Ps...>>;
  };
} } }

#endif

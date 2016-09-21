//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/arch/x86/ssse3/simd/function/topology.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd  =  boost::dispatch;
  namespace bs  =  boost::simd;
  namespace bsd =  boost::simd::detail;

  // -----------------------------------------------------------------------------------------------
  // Unary SSSE3 shuffle
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::ssse3_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::type64_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == cardinal_of<A0>::value
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::ssse3_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::ssse3_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == cardinal_of<A0>::value
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::ssse3_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::ssse3_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == cardinal_of<A0>::value
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::ssse3_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::ssse3_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::fundamental_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == cardinal_of<A0>::value
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::ssse3_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // Binary SSSE3 shuffle
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::ssse3_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::type64_<A0>, bs::sse_>
                          , bs::pack_<bd::type64_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == cardinal_of<A0>::value
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0, const A0 & a1) const BOOST_NOEXCEPT
    {
      return detail::shuffler<detail::ssse3_shuffle,detail::pattern_<Ps...>>::process(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::ssse3_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == cardinal_of<A0>::value
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0, const A0 & a1) const BOOST_NOEXCEPT
    {
      return detail::shuffler<detail::ssse3_shuffle,detail::pattern_<Ps...>>::process(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::ssse3_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == cardinal_of<A0>::value
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0, const A0 & a1) const BOOST_NOEXCEPT
    {
      return detail::shuffler<detail::ssse3_shuffle,detail::pattern_<Ps...>>::process(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::ssse3_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::fundamental_<A0>, bs::sse_>
                          , bs::pack_<bd::fundamental_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == cardinal_of<A0>::value
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0, const A0 & a1) const BOOST_NOEXCEPT
    {
      return detail::shuffler<detail::ssse3_shuffle,detail::pattern_<Ps...>>::process(a0,a1);
    }
  };
} } }

#endif

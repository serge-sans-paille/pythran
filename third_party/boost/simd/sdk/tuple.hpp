#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_TUPLE_HPP_INCLUDED
#define BOOST_SIMD_SDK_TUPLE_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/identity.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/result_of.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/fusion/support.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/simd/sdk/details/at_iterator.hpp>
#include <boost/simd/sdk/meta/zero_initialize.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct tuple_ {};
  }

  template<class Tag> struct fusion_has_ctors : boost::mpl::false_ {};
  template<> struct fusion_has_ctors<boost::simd::tag::tuple_> : boost::mpl::true_ {};
  template<> struct fusion_has_ctors<boost::fusion::vector_tag> : boost::mpl::true_ {};

  template<BOOST_PP_ENUM_BINARY_PARAMS(BOOST_DISPATCH_MAX_ARITY, class T, = void BOOST_PP_INTERCEPT)>
  struct tuple;

  namespace details
  {
    template<class Seq, class F, class To, int N, bool HasCtors>
    struct as_tuple_to;

    template<class Seq, class F, class To, int N>
    struct as_tuple
         : as_tuple_to<Seq, F, To, N, boost::simd::fusion_has_ctors<typename boost::fusion::traits::tag_of<To>::type>::value>
    {
    };
  }

  namespace meta
  {
    template<class Seq, class F = boost::dispatch::identity, class To = void>
    struct as_tuple
     : details::as_tuple<Seq, F, To, fusion::result_of::size<Seq>::type::value>
    {
    };
  }

  template<class Seq, class F>
  typename meta::as_tuple<Seq const, F const>::type as_tuple(Seq const& seq, F const& f)
  {
    return meta::as_tuple<Seq const, F const>::call(seq, f);
  }

  template<class To, class Seq, class F>
  typename meta::as_tuple<Seq const, F const, To>::type as_tuple(Seq const& seq, F const& f)
  {
    return meta::as_tuple<Seq const, F const, To>::call(seq, f);
  }

  template<class To, class Seq>
  typename meta::as_tuple<Seq const, boost::dispatch::identity const, To>::type as_tuple(Seq const& seq)
  {
    return meta::as_tuple<Seq const, boost::dispatch::identity const, To>::call(seq, boost::dispatch::identity());
  }

} }

namespace boost { namespace fusion { namespace extension
{
  template<>
  struct is_sequence_impl<boost::simd::tag::tuple_>
  {
    template<class Seq>
    struct apply : mpl::true_
    {
    };
  };

  template<>
  struct is_view_impl<boost::simd::tag::tuple_>
  {
    template<class Seq>
    struct apply : mpl::false_
    {
    };
  };

  template<>
  struct size_impl<boost::simd::tag::tuple_>
  {
    template<class Seq>
    struct apply
     : mpl::size_t<Seq::static_tuple_size>
    {
    };
  };

  template<>
  struct at_impl<boost::simd::tag::tuple_>
  {
    template<class Seq, int N>
    struct apply_c;

    template<class Seq, class N>
    struct apply : apply_c<Seq, N::value>
    {
    };
  };

  template<>
  struct value_at_impl<boost::simd::tag::tuple_>
  {
    template<class Seq, int N>
    struct apply_c;

    template<class Seq, class N>
    struct apply : apply_c<Seq, N::value>
    {
    };
  };

  template<>
  struct begin_impl<boost::simd::tag::tuple_>
  {
    template<class Seq>
    struct apply
    {
      typedef boost::simd::at_iterator<Seq, 0> type;
      BOOST_FORCEINLINE static type call(Seq& seq)
      {
        return type(seq);
      }
    };
  };

  template<>
  struct end_impl<boost::simd::tag::tuple_>
  {
    template<class Seq>
    struct apply
    {
      typedef boost::simd::at_iterator<Seq, Seq::static_tuple_size> type;
      BOOST_FORCEINLINE static type call(Seq& seq)
      {
        return type(seq);
      }
    };
  };

} } }

namespace boost { namespace simd
{
  template<class Seq, int N>
  BOOST_FORCEINLINE typename fusion::extension::template at_impl<tag::tuple_>::template apply_c<Seq const, N>::type at_c(Seq const& seq)
  {
    return fusion::extension::template at_impl<tag::tuple_>::template apply_c<Seq const, N>::call(seq);
  }

  template<class Seq, int N>
  BOOST_FORCEINLINE typename fusion::extension::template at_impl<tag::tuple_>::template apply_c<Seq, N>::type at_c(Seq& seq)
  {
    return fusion::extension::template at_impl<tag::tuple_>::template apply_c<Seq, N>::call(seq);
  }
} }

#define BOOST_SIMD_TUPLE_TYPES(z, n, t) typedef T##n m##n##_type;
#define BOOST_SIMD_TUPLE_MEMBERS(z, n, t) T##n m##n;
#define BOOST_SIMD_TUPLE_CTORS(z, n, t) BOOST_FORCEINLINE tuple(BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& a)) : BOOST_PP_ENUM(t, BOOST_SIMD_TUPLE_CTORS_, n) {}
#define BOOST_SIMD_TUPLE_CTORS_(z, n, t) BOOST_PP_IF(BOOST_PP_LESS(n, t), m##n(a##n), m##n(meta::zero_initialize<T##n>::call()))

#define BOOST_SIMD_TUPLE_HEAD <BOOST_PP_ENUM_PARAMS(N, T)>
#define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_PP_DEC(BOOST_DISPATCH_MAX_ARITY), "boost/simd/sdk/tuple.hpp"))
#include BOOST_PP_ITERATE()

#undef BOOST_SIMD_TUPLE_HEAD
#define BOOST_SIMD_TUPLE_HEAD
#define BOOST_PP_ITERATION_PARAMS_1 (3, ( BOOST_DISPATCH_MAX_ARITY, BOOST_DISPATCH_MAX_ARITY, "boost/simd/sdk/tuple.hpp"))
#include BOOST_PP_ITERATE()

#undef BOOST_SIMD_TUPLE_HEAD
#undef BOOST_SIMD_TUPLE_CTORS_
#undef BOOST_SIMD_TUPLE_CTORS
#undef BOOST_SIMD_TUPLE_MEMBERS
#undef BOOST_SIMD_TUPLE_TYPES

#endif

#else /* BOOST_PP_IS_ITERATING */

#define N BOOST_PP_ITERATION()

namespace boost { namespace simd
{
  template<BOOST_PP_ENUM_PARAMS(N, class T)>
  struct tuple BOOST_SIMD_TUPLE_HEAD
  {
    typedef tag::tuple_ fusion_tag;
    static const std::size_t static_tuple_size = N;
    BOOST_PP_REPEAT(N, BOOST_SIMD_TUPLE_TYPES, ~)

    tuple() {}
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(N), BOOST_SIMD_TUPLE_CTORS, N)
    BOOST_PP_REPEAT(N, BOOST_SIMD_TUPLE_MEMBERS, ~)
  };
} }

namespace boost { namespace simd { namespace details
{
  template<class Seq, class F>
  struct as_tuple<Seq, F, void, N>
  {
    #define M0(z, n, t) typename dispatch::meta::result_of<F(typename fusion::result_of::value_at_c<Seq, n>::type)>::type
    typedef tuple<BOOST_PP_ENUM(N, M0, ~)> type;
    #undef M0
    BOOST_FORCEINLINE static type call(Seq& seq, F& f)
    {
    #define M0(z, n, t) f(fusion::at_c<n>(seq))
      return type(BOOST_PP_ENUM(N, M0, ~));
    #undef M0
    }
  };

  template<class Seq, class F, class To>
  struct as_tuple_to<Seq, F, To, N, true>
  {
    typedef To type;
    BOOST_FORCEINLINE static type call(Seq& seq, F& f)
    {
    #define M0(z, n, t) f(fusion::at_c<n>(seq))
      return type(BOOST_PP_ENUM(N, M0, ~));
    #undef M0
    }
  };

  template<class Seq, class F, class To>
  struct as_tuple_to<Seq, F, To, N, false>
  {
    typedef To type;
    BOOST_FORCEINLINE static type call(Seq& seq, F& f)
    {
      type tmp;
    #define M0(z, n, t) fusion::at_c<n>(tmp) = f(fusion::at_c<n>(seq));
      BOOST_PP_REPEAT(N, M0, ~);
    #undef M0
      return tmp;
    }
  };
} } }

namespace boost { namespace fusion { namespace extension
{
  template<class Seq>
  struct value_at_impl<boost::simd::tag::tuple_>
  ::apply_c<Seq, BOOST_PP_DEC(N) >
  {
    typedef typename Seq::BOOST_PP_CAT(BOOST_PP_CAT(m, BOOST_PP_DEC(N)), _type) type;
  };

  template<class Seq>
  struct at_impl<boost::simd::tag::tuple_>
  ::apply_c<Seq, BOOST_PP_DEC(N) >
  {
    typedef typename Seq::BOOST_PP_CAT(BOOST_PP_CAT(m, BOOST_PP_DEC(N)), _type)& type;
    BOOST_FORCEINLINE static type call(Seq& seq)
    {
      return seq.BOOST_PP_CAT(m, BOOST_PP_DEC(N));
    }
  };

  template<class Seq>
  struct at_impl<boost::simd::tag::tuple_>
  ::apply_c<Seq const, BOOST_PP_DEC(N) >
  {
    typedef typename Seq::BOOST_PP_CAT(BOOST_PP_CAT(m, BOOST_PP_DEC(N)), _type) const& type;
    BOOST_FORCEINLINE static type call(Seq const& seq)
    {
      return seq.BOOST_PP_CAT(m, BOOST_PP_DEC(N));
    }
  };
} } }

#undef N

#endif

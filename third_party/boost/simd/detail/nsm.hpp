//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef NSM_HPP_INCLUDED
#define NSM_HPP_INCLUDED

#include <boost/config.hpp>
#include <cstdint>
#include <cstring>
#include <utility>

// Detect stupid ICC/G++ combos
#if defined(BOOST_INTEL_GCC_VERSION) && (BOOST_INTEL_GCC_VERSION < 40600)
#define NSM_ASSUME_INCOMPLETE_STD
#endif

#if defined(NSM_ASSUME_INCOMPLETE_STD)
#include <boost/type_traits.hpp>
namespace nsm {
  namespace type_traits = boost;
}
#else
#include <type_traits>
namespace nsm {
  namespace type_traits = std;
}
#endif

namespace nsm
{
  template <class... T> struct list {};
  template<typename T, T... Values>
  using integral_list = nsm::list< type_traits::integral_constant<T,Values>...>;
  using empty_sequence = nsm::list<>;

  template<typename T, typename R = void > struct has_type
  {
    using type = R;
  };

  template <bool B>
  using bool_ = type_traits::integral_constant<bool, B>;

  template<typename T> struct type_ { using type = T; };
  template<typename T> using type_from = typename T::type;

  template <typename First, typename Second>
  struct pair
  {
      using first_type = First;
      using second_type = Second;
  };

  struct no_such_type_ {};

  namespace lazy
  {
    template <typename M, typename K>
    struct lookup
    : decltype(M::at(type_<K>{}))
    {};
  }

  template <typename M, typename K>
  using lookup = typename lazy::lookup<M,K>::type;

  namespace detail
  {
    template <class... T>
    struct map_impl;
    template <class K, class... T>
    struct map_inserter_impl
    {
        using index_type = typename K::first_type;
        using map_type = map_impl<T...>;
        using find_result = lookup<map_type, index_type>;
        using type = decltype(map_type::template insert_impl<K>(find_result{}));
    };
    template <class... T>
    struct map_inserter
    {
        template <class K, typename U>
        static map_impl<T...> insert_impl(U);
        template <class K>
        static map_impl<T..., K> insert_impl(no_such_type_);
        template <class K>
        static typename map_inserter_impl<K, T...>::type insert(type_<K>);
    };
    template <>
    struct map_impl<>
    {
        template <typename U>
        static type_<no_such_type_> at(U);
        template <class K>
        static map_impl<K> insert(type_<K>);
    };
    template <class... Ts>
    struct map_impl : map_inserter<Ts...>
    {
    private:
        struct Pack : pair<typename Ts::first_type, Ts>... {};
        template<class K, class P>
        static type_<typename P::second_type> at_impl(pair<K,P>*);
    public:
        template<class K>
        static decltype(at_impl<K>(static_cast<Pack*>(nullptr))) at(type_<K>);
        template<class K>
        static type_<no_such_type_> at(K);
    };
    template<class... Ts>
    struct make_map : type_<typename Ts::first_type>... {
      using type = map_impl<Ts...>;
    };
  }

  template<class... Ts>
  using map = typename detail::make_map<Ts...>::type;

  namespace detail
  {
    template<class, class>
    struct dup_append_list;

    template<template<class...> class List, class... Ts, class... Us>
    struct dup_append_list<List<Ts...>, List<Us...>>
    {
      using type = List<Ts..., Ts..., Us...>;
    };

    template<class T, template<class...> class List, std::size_t N>
    struct filled_list_impl
    : dup_append_list<
      typename filled_list_impl<T, List, N/2>::type,
      typename filled_list_impl<T, List, N - N/2*2>::type
    >
    {};

    template<class T, template<class...> class List>
    struct filled_list_impl<T, List, 1>
    {
      using type = List<T>;
    };

    template<class T, template<class...> class List>
    struct filled_list_impl<T, List, 0>
    {
      using type = List<>;
    };
  }

  template<class T, std::size_t N, template<class...> class List = list>
  using filled_list = typename detail::filled_list_impl<T, List, N>::type;

  namespace detail
  {
    template<class T> struct element_at;
    template<class... Ts>
    struct element_at<list<Ts...>>
    {
      template<class T> type_<T> static at(Ts..., type_<T>*, ...);
    };
    template<std::size_t N, typename Seq> struct at_impl;
    template<std::size_t N, template<typename...> class L, class... Ts>
    struct at_impl<N,L<Ts...>>
    : decltype(element_at<nsm::filled_list<void const *, N>>::at(static_cast<type_<Ts>*>(nullptr)...))
    {
    };
  }

  template <class L, std::size_t Index>
  using at_c = typename detail::at_impl<Index, L>::type;

  namespace detail
  {
    template <typename T>
    struct has_at_method
    {
      struct dummy {};
      template <typename C, typename P>
      static auto test(P * p) -> decltype(C::at(*p), type_traits::true_type());
      template <typename, typename>
      static type_traits::false_type test(...);
      static const bool value = std::is_same<type_traits::true_type, decltype(test<T, dummy>(nullptr))>::value;
    };

    template <class L, typename Index, bool>
    struct at_dispatch
    {
        using type = at_c<L, Index::value>;
    };

    template <class L, typename Index>
    struct at_dispatch<L, Index, true>
    {
        using type = lookup<L, Index>;
    };
  }

  template <class Seq, typename K>
  using at = typename detail::at_dispatch<Seq, K, detail::has_at_method<Seq>::value>::type;

  namespace detail
  {
    template<class L> struct front_impl;
    template<template<class...> class L, class T, class... U>
    struct front_impl<L<T, U...>>
    {
      using type = T;
    };
  }

  template <class L>
  using front = typename detail::front_impl<L>::type;

  template<std::size_t Index> struct args
  {
    template<typename... Ts> struct apply
    {
      using type = nsm::at_c<nsm::list<Ts...>,Index>;
    };
  };

  // Limit to 5 placeholders
  using _1 = args<0>;
  using _2 = args<1>;
  using _3 = args<2>;
  using _4 = args<3>;
  using _5 = args<4>;

  // Those are reminder for fold
  using _state    = _1;
  using _element = _2;

  template<typename T> struct is_placeholder : type_traits::false_type {};
  template<std::size_t I>
  struct is_placeholder< nsm::args<I>> : type_traits::true_type {};

  template<typename... T> struct has_placeholders : type_traits::false_type {};
  template<typename T> struct has_placeholders<T> : is_placeholder<T> {};

  template<template<class...>class T,typename... Ts>
  struct has_placeholders<T<Ts...>> : has_placeholders<Ts...> {};

  template<typename F, typename... T> struct bind;
  template<typename F, typename... T>
  struct has_placeholders<bind<F,T...>> : type_traits::false_type {};

  template <bool...> struct checks_ {};
  template<typename T, typename U, typename... Ts>
  struct has_placeholders<T,U,Ts...>
        : bool_ < !std::is_same < checks_ < true
                                          , !has_placeholders<T>::value, !has_placeholders<U>::value
                                          , !has_placeholders<Ts>::value...
                                          >
                                , checks_ < !has_placeholders<T>::value, !has_placeholders<U>::value
                                          , !has_placeholders<Ts>::value...
                                          , true
                                          >
                                >::value
                >
  {};

  namespace detail
  {
    template<typename T, typename List>
    struct substitute_impl
    {
      using type = T;
    };
    template<template<class...> class T, typename... Ts, typename List>
    struct substitute_impl<T<Ts...>,List>
    {
      using type = T<typename substitute_impl<Ts,List>::type...>;
    };
    template<std::size_t Index, typename List>
    struct substitute_impl<args<Index>,List>
    {
      using type = nsm::at_c<List,Index>;
    };
  }

  template<typename T, typename List>
  using substitute = typename detail::substitute_impl<T,List>::type;

  namespace detail
  {
    template<typename T, typename If = void> struct eval_;
    template<typename T> struct recurse { using type = T; };
    template<template<class...> class U, typename... T> struct recurse<U<T...>>
    {
      template<typename X> using get = typename eval_<X>::type;
      using type = U<get<T>...>;
    };
    template<typename T, typename If> struct eval_
    {
      using type = typename recurse<T>::type;
    };
    template<typename T> struct eval_<T,typename has_type<typename T::type>::type>
    {
      using type = typename recurse<T>::type::type;
    };
    template<typename F, typename Xs, typename If = void> struct lambda_impl;
    template<typename F, typename Xs> struct lambda_base;
    template<typename F, typename... Xs> struct lambda_apply;
    template< template<class...> class F, typename... An
            , template<class...> class L, typename... X
            >
    struct lambda_base< F<An...>, L<X...>>
    {
      using type = F<substitute<An,L<X...>>...>;
    };
    template< typename F
            , template<class...> class L, typename... X
            >
    struct lambda_base< F, L<X...>>
    {
      using type = substitute<F,L<X...>>;
    };
    template<typename F, template<class...> class L, typename... X>
    struct lambda_impl< F, L<X...>
                      , typename std::enable_if<has_placeholders<F>::value>::type
                      >
    {
      using base = typename lambda_base<F,L<X...>>::type;
      using type = typename eval_<base>::type;
    };
    template<typename F, typename... X>
    struct lambda_apply
    {
      using type = typename F::template apply<X...>::type;
    };
    template<template<class...> class F, typename... An, typename... X>
    struct lambda_apply<F<An...>,X...>
    {
      using type = typename F<An...>::template apply<X...>::type;
    };
    template<typename F, template<class...> class L, typename... X, typename If>
    struct lambda_impl<F, L<X...>, If>
    {
      using type = typename lambda_apply<F,X...>::type;
    };
  }

  template<typename F> struct lambda
  {
    template<typename... X> struct apply : detail::lambda_impl<F, nsm::list<X...>> {};
  };

  namespace detail
  {
    template<typename Lambda, typename Args> struct apply;
    template<typename Lambda, template<class...> class List, typename... Args>
    struct apply < Lambda, List<Args...> >
    {
      using type = typename Lambda::template apply<Args...>::type;
    };
  }

  template<typename Lambda, typename... Args>
  using apply = typename detail::apply<lambda<Lambda>,nsm::list<Args...>>::type;

  namespace detail
  {
    template <typename Functor, typename Sequence>
    struct unary_transform_impl;

    template< typename Functor
              , template<class...> class Sequence, typename... T
              >
    struct unary_transform_impl<Functor, Sequence<T...>>
    {
      using type = Sequence< nsm::apply<Functor,T>... >;
    };

    template<typename Functor, typename Sequence1, typename Sequence2>
    struct binary_transform_impl;
      template< typename Functor
              , template<class...> class Sequence1, typename... T1
              , template<class...> class Sequence2, typename... T2
              >
    struct binary_transform_impl<Functor, Sequence1<T1...>, Sequence2<T2...>>
    {
      static_assert ( sizeof...(T1) == sizeof...(T2)
                    , "The arguments of transform should be of the same size"
                    );
      using type = Sequence1< nsm::apply<Functor,T1,T2>... >;
    };

    template <std::size_t Selector, typename Sequence1, typename Functor, typename Sequence2 = void>
    struct transform_selector;

    template <typename Sequence1, typename Functor>
    struct transform_selector <0, Sequence1, Functor, void>
    {
      using type = typename unary_transform_impl<Functor, Sequence1>::type;
    };

    template <typename Sequence1, typename Sequence2, typename Functor>
    struct transform_selector<1, Sequence1, Sequence2, Functor>
    {
      using type = typename binary_transform_impl<Functor, Sequence1, Sequence2>::type;
    };
  }

  namespace lazy
  {
    template<typename Sequence1, typename OpSeq1, typename... OpSeq2>
    using transform = typename detail::transform_selector<sizeof...(OpSeq2), Sequence1, OpSeq1, OpSeq2...>;
  }

  template<typename Sequence1, typename OpSeq1, typename... OpSeq2>
  using transform = typename detail::transform_selector<sizeof...(OpSeq2), Sequence1, OpSeq1, OpSeq2...>::type;

  template <typename T>
  struct make_integral : type_traits::integral_constant <typename T::value_type, T::value> {};

  template <typename L>
  using as_integral_list = transform<L, make_integral<nsm::_1>>;

  namespace detail
  {
    template <class A, template<class...> class B> struct wrap_impl;
    template<template<class...> class A, class... T, template<class...> class B>
    struct wrap_impl<A<T...>, B>
    {
      using type = B<T...>;
    };
  }

  template<class A, template<class...> class B>
  using wrap = typename detail::wrap_impl<A, B>::type;

  template<class... T>
  using count = type_traits::integral_constant<std::size_t, sizeof...(T)>;

  template<class L> using size = wrap<L, count>;

  namespace detail
  {
      template <typename L, template <class...> class Sequence>
      struct as_sequence_impl
      {
          using type = wrap<L, Sequence>;
      };
  }

  template <typename L, template <class...> class Sequence>
  using as_sequence = typename detail::as_sequence_impl<L, Sequence>::type;

  template <typename L>
  using as_list = as_sequence<L, nsm::list>;

  template <typename... T>
  struct pair_wrapper_
  {
    static_assert (sizeof...(T) == 2
                  , "as_pair requires a type list of exactly two types"
                  );
    using type = no_such_type_;
  };

  template <typename T, typename U>
  struct pair_wrapper_<T,U>
  {
      using type = std::pair<T,U>;
  };

  template <typename... T>
  using pair_wrapper = typename pair_wrapper_<T...>::type;
  template <typename L>
  using as_pair = wrap<L, pair_wrapper>;

  namespace detail
  {
    struct non_null
    {
      template<typename Args> struct apply : bool_< Args::value != 0> {};
    };

    template <bool...> struct bools_ {};
    template< typename Sequence, typename Predicate, typename... Ts> struct all_impl;
    template<typename P, typename T> using invoked = nsm::apply<P,T>;
    template< template<class...> class Sequence, typename Predicate, typename... Ts>
    struct  all_impl<Sequence<Ts...>,Predicate>
          : std::is_same< bools_<true, invoked<Predicate,Ts>::value...>
                        , bools_<invoked<Predicate,Ts>::value..., true>
                        >
    {};
  }

  namespace detail
  {
    template <typename P, template <class...> class Sequence>
    struct finder
    {
      template <typename T>
      struct Pred : nsm::apply<P, T>
      {
      };
      template <bool C, bool F, typename... Ts>
      struct find
      {
          using type = Sequence<>;
      };
      template <bool F, typename T1, typename... Ts>
      struct find<true, F, T1, Ts...>
      {
          using type = Sequence<T1, Ts...>;
      };
      template <typename T1, typename T2, typename... Ts>
      struct find<false, true, T1, T2, Ts...> : find<Pred<T2>::value, true, T2, Ts...>
      {
      };
      template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
                typename T7, typename T8, typename T9, typename... Ts>
      struct find<false, false, T1, T2, T3, T4, T5, T6, T7, T8, T9, Ts...>
          : find<
                Pred<T9>::value,
                true ,
                T9, Ts...>
      {
      };
      template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
                typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
                typename T13, typename T14, typename T15, typename T16, typename... Ts>
      struct find<false, false, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
                  T16, Ts...>
          : find<Pred<T9>::value,
                 (Pred<T9>::value || Pred<T10>::value || Pred<T11>::value || Pred<T12>::value ||
                  Pred<T13>::value || Pred<T14>::value || Pred<T15>::value || Pred<T16>::value),
                 T9, T10, T11, T12, T13, T14, T15, T16, Ts...>
      {
      };
    };

    template <typename Predicate, class Sequence>
    struct find_if_impl
    {
        using type = Sequence;
    };

    template <typename Predicate, template <class...> class Sequence, typename T1, typename... T>
    struct find_if_impl<Predicate, Sequence<T1, T...>>
        : finder<Predicate, Sequence>::template find<false, false, void, void, void, void, void,
                                                     void, void, void, T1, T...>
    {
    };
  }

  namespace lazy
  {
    template <typename Sequence, typename Predicate = nsm::detail::non_null>
    using find = typename detail::find_if_impl<Predicate, Sequence>;
  }

  template <typename Sequence, typename Predicate = nsm::detail::non_null>
  using find = typename lazy::find<Sequence, Predicate>::type;

  namespace detail
  {
    template <typename Sequence, typename Predicate>
    using find_size = size<nsm::find<Sequence, Predicate>>;

    template <typename Sequence, typename Predicate>
    using empty_find = bool_<find_size<Sequence, Predicate>::value == 0>;

    template <typename Sequence, typename Predicate>
    using non_empty_find = bool_<find_size<Sequence, Predicate>::value != 0>;
}

  // Utility meta-function to check if nothing was found
  template <typename Sequence, typename Predicate = detail::non_null>
  using not_found = typename detail::empty_find<Sequence, Predicate>;

  // Utility meta-function to check if something was found
  template <typename Sequence, typename Predicate = detail::non_null>
  using found = typename detail::non_empty_find<Sequence, Predicate>;

  template<typename Sequence, typename Predicate = detail::non_null>
  using all = typename detail::all_impl<Sequence,Predicate>::type;

  namespace detail
  {
    template<typename Sequence, typename Pred> struct none_impl
    {
      struct nope
      {
        template<typename T> struct apply
        {
          using that = nsm::apply<Pred,T>;
          using type = bool_<!that::value>;
        };
      };
      using type = all<Sequence,nope>;
    };
  }

  template< typename Sequence, typename Predicate = detail::non_null>
  using none = typename detail::none_impl<Sequence,Predicate>::type;

  namespace detail
  {
    template< typename Sequence, typename Predicate >
    struct any_impl : bool_<!none<Sequence,Predicate>::value> {};
  }

  template<typename Sequence, typename Predicate = detail::non_null>
  using any = typename detail::any_impl<Sequence,Predicate>::type;

  namespace detail
  {
    template <typename... Ts>
    struct append_impl
    {
        using type = nsm::empty_sequence;
    };
    template <typename T>
    struct append_impl<T>
    {
        using type = T;
    };
    template <template <typename...> class L1, template <typename...> class L2, typename... T1s,
              typename... T2s, typename... Ts>
    struct append_impl<L1<T1s...>, L2<T2s...>, Ts...> : append_impl<L1<T1s..., T2s...>, Ts...>
    {
    };
    template <template <typename...> class L, template <typename...> class L1,
              template <typename...> class L2, template <typename...> class L3,
              template <typename...> class L4, template <typename...> class L5,
              template <typename...> class L6, template <typename...> class L7,
              template <typename...> class L8, template <typename...> class L9,
              template <typename...> class L10, template <typename...> class L11,
              template <typename...> class L12, template <typename...> class L13,
              template <typename...> class L14, template <typename...> class L15,
              template <typename...> class L16, typename... Ts, typename... T1s, typename... T2s,
              typename... T3s, typename... T4s, typename... T5s, typename... T6s, typename... T7s,
              typename... T8s, typename... T9s, typename... T10s, typename... T11s,
              typename... T12s, typename... T13s, typename... T14s, typename... T15s,
              typename... T16s, typename... Us>
    struct append_impl<L<Ts...>, L1<T1s...>, L2<T2s...>, L3<T3s...>, L4<T4s...>, L5<T5s...>,
                     L6<T6s...>, L7<T7s...>, L8<T8s...>, L9<T9s...>, L10<T10s...>, L11<T11s...>,
                     L12<T12s...>, L13<T13s...>, L14<T14s...>, L15<T15s...>, L16<T16s...>, Us...>
        : append_impl<L<Ts..., T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., T8s...,
                        T9s..., T10s..., T11s..., T12s..., T13s..., T14s..., T15s..., T16s...>,
                      Us...>
    {
    };
}
template <typename... Ts>
using append = typename detail::append_impl<Ts...>::type;
}
namespace nsm
{
namespace detail
{
    template <template<class...> class L, class...>
    struct reverse_elements;
    template <template <class...> class L>
    struct reverse_elements<L>
    {
        using type = L<>;
    };
    template <template <class...> class L, class T0, class... Ts>
    struct reverse_elements<L, T0, Ts...>
    : append_impl<typename reverse_elements<L, Ts...>::type, L<T0>>
    {
    };
    template <template <class...> class L, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class... Ts>
    struct reverse_elements<L, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, Ts...>
    : append_impl<typename reverse_elements<L, Ts...>::type, L<T15, T14, T13, T12, T11, T10, T9, T8, T7, T6, T5, T4, T3, T2, T1, T0>>
    {
    };
    template<class L>
    struct reverse_impl;
    template<template<class...> class L, class... U>
    struct reverse_impl<L<U...>>
    : reverse_elements<L, U...>
    {
    };
}
namespace lazy
{
    template <typename L>
    using reverse = typename detail::reverse_impl<L>;
}
    template <typename L>
    using reverse = typename detail::reverse_impl<L>::type;
}


namespace nsm
{
namespace detail
{
    template <class L>
    struct flatten_impl
    {
        using type = L;
    };
    template <template<class...> class L, class T>
    struct flatten_element_impl
    {
        using type = L<T>;
    };
    template <template<class...> class L, class... Ts>
    struct flatten_element_impl<L, L<Ts...>>
    : append_impl<typename flatten_element_impl<L, Ts>::type...>
    {
    };
    template <template<class...> class L, class... Ts>
    struct flatten_impl<L<Ts...>>
    : flatten_element_impl<L, L<Ts...>>
    {
    };
}
namespace lazy
{
    template <typename Sequence>
    using flatten = typename detail::flatten_impl<Sequence>;
}
template <typename Sequence>
using flatten = typename lazy::flatten<Sequence>::type;
}
namespace nsm { namespace detail
{
  template<class Functor, class State, class Sequence>
  struct fold_impl
  {
      using type = State;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0>
  struct fold_impl<Functor, State, Sequence<T0>>
  {
      using type = nsm::apply<Functor, State, T0>;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1>
  struct fold_impl<Functor, State, Sequence<T0, T1>>
  {
      using type = nsm::apply<Functor,
          nsm::apply<Functor,State, T0>, T1
      >;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2>>
  {
      using type = nsm::apply<Functor,
          nsm::apply<Functor,
              nsm::apply<Functor, State, T0>, T1
          >, T2
      >;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3>>
  {
      using type = nsm::apply<Functor,
          nsm::apply<Functor,
              nsm::apply<Functor,
                  nsm::apply<Functor, State, T0>, T1
              >, T2
          >, T3
      >;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4>>
  {
      using type = nsm::apply<Functor,
          nsm::apply<Functor,
              nsm::apply<Functor,
                  nsm::apply<Functor,
                      nsm::apply<Functor, State, T0>, T1
                  >, T2
              >, T3
          >, T4
      >;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4, class T5>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4, T5>>
  {
      using type = nsm::apply<Functor,
          nsm::apply<Functor,
              nsm::apply<Functor,
                  nsm::apply<Functor,
                      nsm::apply<Functor,
                          nsm::apply<Functor, State, T0>, T1
                      >, T2
                  >, T3
              >, T4
          >, T5
      >;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4, class T5, class T6>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4, T5, T6>>
  {
      using type = nsm::apply<Functor,
          nsm::apply<Functor,
              nsm::apply<Functor,
                  nsm::apply<Functor,
                      nsm::apply<Functor,
                          nsm::apply<Functor,
                              nsm::apply<Functor, State, T0>, T1
                          >, T2
                      >, T3
                  >, T4
              >, T5
          >, T6
      >;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4, T5, T6, T7>>
  {
      using type = nsm::apply<Functor,
          nsm::apply<Functor,
              nsm::apply<Functor,
                  nsm::apply<Functor,
                      nsm::apply<Functor,
                          nsm::apply<Functor,
                              nsm::apply<Functor,
                                  nsm::apply<Functor, State, T0>, T1
                              >, T2
                          >, T3
                      >, T4
                  >, T5
              >, T6
          >, T7
      >;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class... T>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4, T5, T6, T7, T...>>
  : fold_impl<
      Functor,
      nsm::apply<Functor,
          nsm::apply<Functor,
              nsm::apply<Functor,
                  nsm::apply<Functor,
                      nsm::apply<Functor,
                          nsm::apply<Functor,
                              nsm::apply<Functor,
                                  nsm::apply<Functor,
                                      State, T0
                                  >, T1
                              >, T2
                          >, T3
                      >, T4
                  >, T5
              >, T6
          >, T7
      >,
      Sequence<T...>
  >
  {};
} }
namespace nsm
{
namespace lazy
{
    template <class Sequence, class State, class Functor>
    using fold = typename detail::fold_impl<Functor, State, Sequence>;
}
  template <class Sequence, class State, class Functor>
  using fold = typename ::nsm::lazy::fold<Sequence, State, Functor>::type;
}
#include <initializer_list>
#include <functional>
namespace nsm
{
  template<class F, class...Ts> F for_each_args(F f, Ts&&...a)
  {
    return (void)std::initializer_list<int>{((void)std::ref(f)(static_cast<Ts&&>(a)),0)...}, f;
  }

  namespace detail
  {
    template<template<class...> class List, typename... Elements, typename Functor>
    Functor for_each_impl( List<Elements...>&&, Functor f )
    {
      return for_each_args( f, type_<Elements>()... );
    }
  }
  template<typename List, typename Functor> Functor for_each( Functor f )
  {
    return detail::for_each_impl( List{}, f );
  }

  template<typename T, T V>
  using constant = type_traits::integral_constant<T, V>;
  template <std::int8_t V>
  using int8_t = type_traits::integral_constant<std::int8_t, V>;
  template <std::uint8_t V>
  using uint8_t = type_traits::integral_constant<std::uint8_t, V>;
  template <std::int16_t V>
  using int16_t = type_traits::integral_constant<std::int16_t, V>;
  template <std::uint16_t V>
  using uint16_t = type_traits::integral_constant<std::uint16_t, V>;
  template <std::int32_t V>
  using int32_t = type_traits::integral_constant<std::int32_t, V>;
  template <std::uint32_t V>
  using uint32_t = type_traits::integral_constant<std::uint32_t, V>;
  template <std::int64_t V>
  using int64_t = type_traits::integral_constant<std::int64_t, V>;
  template <std::uint64_t V>
  using uint64_t = type_traits::integral_constant<std::uint64_t, V>;
  template<std::size_t V>
  using size_t    = type_traits::integral_constant<std::size_t, V>;
  template<std::ptrdiff_t V>
  using ptrdiff_t = type_traits::integral_constant<std::ptrdiff_t, V>;
}
namespace nsm
{
  namespace detail
  {
    template<class T, class, class, T>
    struct range_cat;
    template<class T, T Start, T Int>
    struct int_plus
    {
      using type = type_traits::integral_constant<T, Start + Int>;
    };
    template<class T, class... Ts, T... Ints, T Start>
    struct range_cat<T, list<Ts...>, list<type_traits::integral_constant<T, Ints>...>, Start>
    {
      using type = list<Ts..., typename int_plus<T, Start, Ints>::type...>;
    };
    template<class T, T Start, std::size_t N>
    struct range_impl
    : range_cat<
      T,
      typename range_impl<T, Start, N/2>::type,
      typename range_impl<T, Start, N - N/2>::type,
      N/2
    >
    {};
    template<class T, T Start>
    struct range_impl<T, Start, 1>
    {
      using type = list<type_traits::integral_constant<T, Start>>;
    };
    template<class T, T Start>
    struct range_impl<T, Start, 0>
    {
      using type = list<>;
    };
    template<class T, class, class, T>
    struct reverse_range_cat;
    template<class T, T Start, T Int>
    struct int_minus
    {
      using type = type_traits::integral_constant<T, Int - Start>;
    };
    template<class T, class... Ts, T... Ints, T Start>
    struct reverse_range_cat<T, list<Ts...>, list<type_traits::integral_constant<T, Ints>...>, Start>
    {
      using type = list<Ts..., typename int_minus<T, Start, Ints>::type...>;
    };
    template<class T, T Start, std::size_t N>
    struct reverse_range_impl
    : reverse_range_cat<
      T,
      typename reverse_range_impl<T, Start, N/2>::type,
      typename reverse_range_impl<T, Start, N - N/2>::type,
      N/2
    >
    {};
    template<class T, T Start>
    struct reverse_range_impl<T, Start, 1>
    {
      using type = list<type_traits::integral_constant<T, Start>>;
    };
    template<class T, T Start>
    struct reverse_range_impl<T, Start, 0>
    {
      using type = list<>;
    };
  }
  template<class T, T Start, T Stop>
  using range = typename detail::range_impl<T, Start, Stop-Start>::type;
  template<class T, T Start, T Stop>
  using reverse_range = typename detail::reverse_range_impl<T, Start, Start-Stop>::type;

  template<class T> struct protect
  {
    using type = T;
  };
  template<class F> struct lambda<protect<F>>
  {
    template<class... X> struct apply { using type = F; };
  };
  template<class T>
  struct has_placeholders<protect<T>>
  : type_traits::false_type
  {};

  template<typename C, typename T, typename F>
  inline typename std::enable_if<C::value,T&&>::type select(T&& t, F&&)
  {
    return std::forward<T>(t);
  }
  template<typename C, typename T, typename F>
  inline typename std::enable_if<!C::value,F&&>::type select(T&&, F&& f)
  {
    return std::forward<F>(f);
  }

  template <typename A, typename B>
  struct less : bool_ < (A::value < B::value) > {};

  namespace detail
  {
    template<class T, class If = void>
    struct quote_impl
    {
      using type = T;
    };
    template<class T>
    struct quote_impl<T, typename has_type<typename T::type>::type>
    {
      using type = typename T::type;
    };
  }

  template<template<class ...> class Metafunction> struct quote
  {
    template<typename... Us> struct apply : detail::quote_impl<Metafunction<Us...>> {};
  };

  template<class T>
  struct identity
  {
    using type = T;
  };

  template <typename A>
  struct next : type_traits::integral_constant < typename A::value_type, A::value + 1 > {};

  template <typename A>
  struct prev : type_traits::integral_constant < typename A::value_type, A::value - 1 > {};

  template <typename A, typename B>
  struct max : type_traits::integral_constant < typename A::value_type
                                      , (A::value < B::value) ? B::value : A::value
                                      >
  {};

  template <typename A, typename B>
  struct min : type_traits::integral_constant < typename A::value_type
                                      , (A::value < B::value) ? A::value : B::value
                                      >
  {};

  template <typename A, typename B>
  struct equal_to : bool_ < (A::value == B::value) > {};

  template <typename A, typename B>
  struct greater : bool_<(A::value > B::value) > {};

  template <typename A, typename B>
  struct greater_equal : bool_ < (A::value >= B::value) > {};

  template <typename A, typename B>
  struct less_equal : bool_ < (A::value <= B::value) > {};

  template <typename A, typename B>
  struct not_equal_to : bool_ < (A::value != B::value) > {};

  template <typename Condition, typename A, typename B>
  struct eval_if
  {
    using type = typename std::conditional<Condition::value, A, B>::type::type;
  };
  template <bool Condition, typename A, typename B>
  struct eval_if_c
  {
    using type = typename std::conditional<Condition, A, B>::type::type;
  };

  template <typename Condition, typename A, typename B>
  struct if_ : std::conditional<Condition::value, A, B> {};
  template <bool Condition, typename A, typename B>
  struct if_c : std::conditional<Condition, A, B> {};

  namespace detail
  {
    template<typename X, typename Us, typename If = void>
    struct bind_impl
    {
      using type = X;
    };
    template<typename X, template<class...> class L, typename... Us>
    struct bind_impl<X,L<Us...>, typename std::enable_if<has_placeholders<X>::value>::type>
    {
      using type = nsm::apply<X,Us...>;
    };
    template<typename X, typename L> using bind_impl_t = typename bind_impl<X,L>::type;
  }
  template<typename MetafunctionClass, typename... Args> struct bind
  {
    template<typename... Us> struct apply
    {
      using type = nsm::apply < detail::bind_impl_t<MetafunctionClass,list<Us...>>
                                  , detail::bind_impl_t<Args,list<Us...>>...
                                  >;
    };
  };

  template<typename Functor> struct unpack {};
  template<class F> struct lambda<unpack<F>>
  {
    template<typename X> struct apply;
    template<template<class...> class List, typename... Types>
    struct apply<List<Types...>> : nsm::apply<F,Types...>
    {};
  };

  template <typename A, typename B>
  struct and_ : type_traits::integral_constant <typename A::value_type, A::value && B::value > {};

  template <typename T>
  struct not_ : type_traits::integral_constant<typename T::value_type, !T::value> {};

  template <typename A, typename B>
  struct or_ : type_traits::integral_constant < typename A::value_type, A::value || B::value > {};

  template <typename A, typename B>
  struct xor_ : type_traits::integral_constant<typename A::value_type, A::value != B::value> {};

  template<class T>
  struct always
  {
    template<typename X> struct apply { using type = T; };
  };

  template<typename T>
  struct sizeof_ : type_traits::integral_constant <std::size_t, sizeof(T)> {};

  namespace detail
  {
    template<class Start, unsigned N, class Next, class... E>
    struct mksq8
    : mksq8<nsm::apply<Next, Start>, N-1, Next, E..., Start>
    {};

    template<class Start, class Next, class... E>
    struct mksq8<Start, 0, Next, E...>
    {
        using type = list<E...>;
    };

    template<class Start, class Next, class... E>
    struct mksq8<Start, 1, Next, E...>
    {
        using type = list<E..., Start>;
    };

    template<class Start, class Next>
    struct mksq8<Start, 8, Next>
    {
      using t1 = nsm::apply<Next, Start>;
      using t2 = nsm::apply<Next, t1>;
      using t3 = nsm::apply<Next, t2>;
      using t4 = nsm::apply<Next, t3>;
      using t5 = nsm::apply<Next, t4>;
      using t6 = nsm::apply<Next, t5>;
      using t7 = nsm::apply<Next, t6>;
      using type = list<Start, t1, t2, t3, t4, t5, t6, t7>;
    };

    template<template<class...> class List, class Start, unsigned N, class Next, bool, class... L>
    struct make_sequence_impl
    : make_sequence_impl<
        List,
        nsm::apply<Next, typename mksq8<Start, 8, Next>::t7>,
        N-8,
        Next,
        (N-8<=8),
        L...,
        typename mksq8<Start, 8, Next>::type
    >
    {};
    template<template<class...> class List, class Start, unsigned N, class Next, class... L>
    struct make_sequence_impl<List, Start, N, Next, true, L...>
    {
        using type = append<List<>, L..., typename mksq8<Start, N, Next>::type>;
    };
  }

  template<class Start, unsigned N, class Next = quote<next>, template<class...> class List = list>
  using make_sequence = typename detail::make_sequence_impl<List, Start, N, Next, (N<=8)>::type;

  template<typename RealType, typename Type, Type Value>
  struct real_ : type_traits::integral_constant<Type,Value>
  {
    using value_type  = RealType;
    using parent      = type_traits::integral_constant<Type,Value>;

    BOOST_FORCEINLINE operator value_type() const
    {
      value_type that;
      std::memcpy(&that, &parent::value, sizeof(value_type));
      return that;
    }
  };

  template<std::uint32_t Value>
  struct single_ : real_<float, std::uint32_t, Value> {};
  template<std::uint64_t Value>
  struct double_ : real_<double, std::uint64_t,Value> {};
}

#endif

/*==================================================================================================
  Copyright (c) 2016 Edouard Alligand and Joel Falcou
  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
=================================================================================================**/
#ifndef BRIGAND_HPP_INCLUDED
#define BRIGAND_HPP_INCLUDED
#include <type_traits>
namespace brigand
{
  template <class... T> struct list {};
  template<typename T, T... Values>
  using integral_list = brigand::list< std::integral_constant<T,Values>...>;
  using empty_sequence = brigand::list<>;
}
namespace brigand
{
  template<typename T, typename R = void > struct has_type
  {
    using type = R;
  };
}
#include <type_traits>
namespace brigand
{
  template <bool B>
  using bool_ = std::integral_constant<bool, B>;
}
#include <type_traits>
namespace brigand
{
  template<typename T> struct type_ { using type = T; };
  template<typename T> using type_from = typename T::type;
}
namespace brigand
{
    template <typename First, typename Second>
    struct pair
    {
        using first_type = First;
        using second_type = Second;
    };
}
namespace brigand
{
    struct no_such_type_ {};
}
namespace brigand
{
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
}
namespace brigand
{
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
}
namespace brigand
{
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
    : decltype(element_at<brigand::filled_list<void const *, N>>::at(static_cast<type_<Ts>*>(nullptr)...))
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
        static auto test(P * p) -> decltype(C::at(*p), std::true_type());
        template <typename, typename>
        static std::false_type test(...);
        static const bool value = std::is_same<std::true_type, decltype(test<T, dummy>(nullptr))>::value;
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
}
namespace brigand
{
  template<std::size_t Index> struct args
  {
    template<typename... Ts> struct apply
    {
      using type = brigand::at_c<brigand::list<Ts...>,Index>;
    };
  };
  using _1 = args<0>;
  using _2 = args<1>;
  using _3 = args<2>;
  using _4 = args<3>;
  using _5 = args<4>;
  using _6 = args<5>;
  using _7 = args<6>;
  using _8 = args<7>;
  using _9 = args<8>;
  using _state = _1;
  using _element = _2;
}
namespace brigand
{
  template<typename T> struct is_placeholder : std::false_type {};
  template<std::size_t I>
  struct is_placeholder< brigand::args<I>> : std::true_type {};
}
namespace brigand
{
	template<typename... T> struct has_placeholders : std::false_type {};
  template<typename T> struct has_placeholders<T> : is_placeholder<T> {};
  template<template<class...>class T,typename... Ts>
  struct has_placeholders<T<Ts...>> : has_placeholders<Ts...> {};
  template<typename F, typename... T> struct bind;
  template<typename F, typename... T>
  struct has_placeholders<bind<F,T...>> : std::false_type {};
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
}
namespace brigand
{
  template<std::size_t Index> struct args;
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
      using type = brigand::at_c<List,Index>;
    };
  }
  template<typename T, typename List>
  using substitute = typename detail::substitute_impl<T,List>::type;
}
namespace brigand
{
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
    template<typename... X> struct apply : detail::lambda_impl<F, brigand::list<X...>> {};
  };
}
namespace brigand
{
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
  using apply = typename detail::apply<lambda<Lambda>,brigand::list<Args...>>::type;
}
namespace brigand
{
  namespace detail
  {
  template <typename Functor, typename Sequence>
  struct unary_transform_impl;
    template< typename Functor
            , template<class...> class Sequence, typename... T
            >
  struct unary_transform_impl<Functor, Sequence<T...>>
    {
      using type = Sequence< brigand::apply<Functor,T>... >;
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
      using type = Sequence1< brigand::apply<Functor,T1,T2>... >;
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
}
namespace brigand
{
    template <typename T>
    struct make_integral : std::integral_constant <typename T::value_type, T::value> {};
    template <typename L>
    using as_integral_list = transform<L, make_integral<brigand::_1>>;
}
namespace brigand
{
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
}
namespace brigand
{
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
using as_list = as_sequence<L, brigand::list>;
}
#include <utility>
namespace brigand
{
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
}
#include <tuple>
namespace brigand
{
  template <typename... T>
  using tuple_wrapper = typename std::tuple<T...>;
  template <typename L>
  using as_tuple = wrap<L, tuple_wrapper>;
}
#if !defined(BRIGAND_NO_BOOST_SUPPORT)
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/deque/deque_fwd.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>
namespace brigand
{
  template <typename... T>
  using fusion_vector_wrapper = boost::fusion::vector<T...>;
  template <typename... T>
  using fusion_list_wrapper = boost::fusion::list<T...>;
  template <typename... T>
  using fusion_deque_wrapper = boost::fusion::deque<T...>;
  template <typename... T>
  using fusion_set_wrapper = boost::fusion::set<T...>;
  template <typename L> using as_fusion_vector = wrap<L, fusion_vector_wrapper>;
  template <typename L> using as_fusion_deque  = wrap<L, fusion_deque_wrapper>;
  template <typename L> using as_fusion_list   = wrap<L, fusion_list_wrapper>;
  template <typename L> using as_fusion_set    = wrap<L, fusion_set_wrapper>;
}
#include <boost/variant.hpp>
namespace brigand
{
  template <typename... T>
  using variant_wrapper = typename boost::variant<T...>;
  template <typename L>
  using as_variant = wrap<L, variant_wrapper>;
}
#endif
namespace brigand { namespace detail
{
  struct non_null
  {
    template<typename Args> struct apply : bool_< Args::value != 0> {};
  };
} }
#include <type_traits>
namespace brigand
{
  namespace detail
  {
    template <bool...> struct bools_ {};
    template< typename Sequence, typename Predicate, typename... Ts> struct all_impl;
    template<typename P, typename T> using invoked = brigand::apply<P,T>;
    template< template<class...> class Sequence, typename Predicate, typename... Ts>
    struct  all_impl<Sequence<Ts...>,Predicate>
          : std::is_same< bools_<true, invoked<Predicate,Ts>::value...>
                        , bools_<invoked<Predicate,Ts>::value..., true>
                        >
    {};
  }
  template<typename Sequence, typename Predicate = detail::non_null>
  using all = typename detail::all_impl<Sequence,Predicate>::type;
}
namespace brigand
{
  namespace detail
  {
    template<typename Sequence, typename Pred> struct none_impl
    {
      struct nope
      {
        template<typename T> struct apply
        {
          using that = brigand::apply<Pred,T>;
          using type = bool_<!that::value>;
        };
      };
      using type = all<Sequence,nope>;
    };
  }
  template< typename Sequence, typename Predicate = detail::non_null>
  using none = typename detail::none_impl<Sequence,Predicate>::type;
}
namespace brigand
{
  namespace detail
  {
    template< typename Sequence, typename Predicate >
    struct any_impl : bool_<!none<Sequence,Predicate>::value> {};
  }
  template<typename Sequence, typename Predicate = detail::non_null>
  using any = typename detail::any_impl<Sequence,Predicate>::type;
}
#include <type_traits>
namespace brigand
{
  template<class... T>
  using count = std::integral_constant<std::size_t, sizeof...(T)>;
}
namespace brigand
{
namespace detail
{
    template <typename P, template <class...> class Sequence>
    struct finder
    {
        template <typename T>
        struct Pred : brigand::apply<P, T>
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
}
namespace brigand
{
namespace detail
{
    template <typename... Ts>
    struct append_impl
    {
        using type = brigand::empty_sequence;
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
namespace brigand
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
namespace brigand
{
  template<class L> using size = wrap<L, count>;
}
namespace brigand
{
namespace lazy
{
    template <typename Sequence, typename Predicate = brigand::detail::non_null>
    using find = typename detail::find_if_impl<Predicate, Sequence>;
}
template <typename Sequence, typename Predicate = brigand::detail::non_null>
using find = typename lazy::find<Sequence, Predicate>::type;
namespace lazy
{
    template <typename Sequence, typename Predicate = detail::non_null>
    using reverse_find =
        ::brigand::lazy::reverse<::brigand::find<brigand::reverse<Sequence>, Predicate>>;
}
template <typename Sequence, typename Predicate = detail::non_null>
using reverse_find = typename ::brigand::lazy::reverse_find<Sequence, Predicate>::type;
namespace detail
{
    template <typename Sequence, typename Predicate>
    using find_size = size<brigand::find<Sequence, Predicate>>;
    template <typename Sequence, typename Predicate>
    using empty_find = bool_<find_size<Sequence, Predicate>::value == 0>;
    template <typename Sequence, typename Predicate>
    using non_empty_find = bool_<find_size<Sequence, Predicate>::value != 0>;
}
template <typename Sequence, typename Predicate = detail::non_null>
using not_found = typename detail::empty_find<Sequence, Predicate>;
template <typename Sequence, typename Predicate = detail::non_null>
using found = typename detail::non_empty_find<Sequence, Predicate>;
}
namespace brigand
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
namespace brigand { namespace detail
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
      using type = brigand::apply<Functor, State, T0>;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1>
  struct fold_impl<Functor, State, Sequence<T0, T1>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor,State, T0>, T1
      >;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor, State, T0>, T1
          >, T2
      >;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor, 
              brigand::apply<Functor,
                  brigand::apply<Functor, State, T0>, T1
              >, T2
          >, T3
      >;
  };
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor,
                  brigand::apply<Functor,
                      brigand::apply<Functor, State, T0>, T1
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
      using type = brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor,
                  brigand::apply<Functor,
                      brigand::apply<Functor,
                          brigand::apply<Functor, State, T0>, T1
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
      using type = brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor,
                  brigand::apply<Functor,
                      brigand::apply<Functor,
                          brigand::apply<Functor,
                              brigand::apply<Functor, State, T0>, T1
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
      using type = brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor,
                  brigand::apply<Functor,
                      brigand::apply<Functor,
                          brigand::apply<Functor,
                              brigand::apply<Functor,
                                  brigand::apply<Functor, State, T0>, T1
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
      brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor,
                  brigand::apply<Functor,
                      brigand::apply<Functor,
                          brigand::apply<Functor,
                              brigand::apply<Functor,
                                  brigand::apply<Functor,
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
namespace brigand
{
namespace lazy
{
    template <class Sequence, class State, class Functor>
    using fold = typename detail::fold_impl<Functor, State, Sequence>;
}
  template <class Sequence, class State, class Functor>
  using fold = typename ::brigand::lazy::fold<Sequence, State, Functor>::type;
}
#include <initializer_list>
#include <functional>
namespace brigand
{
  template<class F, class...Ts> F for_each_args(F f, Ts&&...a)
  {
    return (void)std::initializer_list<int>{((void)std::ref(f)(static_cast<Ts&&>(a)),0)...}, f;
  }
}
namespace brigand
{
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
}
#include <type_traits>
#include <cstdint>
#include <cstddef>
namespace brigand
{
  template <std::int8_t V>
  using int8_t = std::integral_constant<std::int8_t, V>;
  template <std::uint8_t V>
  using uint8_t = std::integral_constant<std::uint8_t, V>;
  template <std::int16_t V>
  using int16_t = std::integral_constant<std::int16_t, V>;
  template <std::uint16_t V>
  using uint16_t = std::integral_constant<std::uint16_t, V>;
  template <std::int32_t V>
  using int32_t = std::integral_constant<std::int32_t, V>;
  template <std::uint32_t V>
  using uint32_t = std::integral_constant<std::uint32_t, V>;
  template <std::int64_t V>
  using int64_t = std::integral_constant<std::int64_t, V>;
  template <std::uint64_t V>
  using uint64_t = std::integral_constant<std::uint64_t, V>;
  template<std::size_t V>
  using size_t    = std::integral_constant<std::size_t, V>;
  template<std::ptrdiff_t V>
  using ptrdiff_t = std::integral_constant<std::ptrdiff_t, V>;
}
namespace brigand
{
namespace detail
{
    template <bool Found, class Sequence, typename Predicate>
    struct index_if_impl
    {
        using type = ::brigand::size_t<size<Sequence>::value -
                                       size<::brigand::find<Sequence, Predicate>>::value>;
    };
    template <class Sequence, typename Predicate>
    struct index_if_impl<false, Sequence, Predicate>
    {
        using type = no_such_type_;
    };
}
template <class Sequence, class Predicate>
using index_if = typename detail::index_if_impl<::brigand::found<Sequence, Predicate>::value,
                                                Sequence, Predicate>::type;
template <class Sequence, typename T>
using index_of = index_if<Sequence, std::is_same<T, ::brigand::_1>>;
}
#include <type_traits>
namespace brigand
{
  namespace detail
  {
    template<class T, class, class, T>
    struct range_cat;
    template<class T, T Start, T Int>
    struct int_plus
    {
      using type = std::integral_constant<T, Start + Int>;
    };
    template<class T, class... Ts, T... Ints, T Start>
    struct range_cat<T, list<Ts...>, list<std::integral_constant<T, Ints>...>, Start>
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
      using type = list<std::integral_constant<T, Start>>;
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
      using type = std::integral_constant<T, Int - Start>;
    };
    template<class T, class... Ts, T... Ints, T Start>
    struct reverse_range_cat<T, list<Ts...>, list<std::integral_constant<T, Ints>...>, Start>
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
      using type = list<std::integral_constant<T, Start>>;
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
}
namespace brigand
{
namespace detail
{
  template<class, class T> struct unique_x_t
  { operator type_<T> (); };
  template<class Ints, class... Ts>
  struct is_set_impl;
  template<>
  struct is_set_impl<list<>>
  {
    using type = std::true_type;
  };
  inline std::true_type true_fn(...);
  template<class... Ints, class... Ts>
  struct is_set_impl<list<Ints...>, Ts...>
  {
    struct Pack : unique_x_t<Ints, Ts>... {};
    template<class... Us>
    static auto is_set(Us...) -> decltype(true_fn(static_cast<Us>(Pack())...));
    static std::false_type is_set(...);
    using type = decltype(is_set(type_<Ts>()...));
  };
}
  template<class... Ts>
  using is_set = typename detail::is_set_impl<range<int, 0, sizeof...(Ts)>, Ts...>::type;
}
namespace brigand
{
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
  : std::false_type
  {};
}
#include <type_traits>
namespace brigand
{
namespace detail
{
  template<class L>
  struct clear_impl;
  template<template<class...> class L, class... Ts>
  struct clear_impl<L<Ts...>>
  {
    using type = L<>;
  };
}
  template<class L>
  using clear = typename detail::clear_impl<L>::type;
}
#include <type_traits>
namespace brigand
{
namespace lazy
{
    template <typename L, typename Pred>
    struct remove_if;
    template <template<class...> class L, typename... Ts, typename Pred>
    struct remove_if<L<Ts...>, Pred>
    : ::brigand::detail::append_impl<L<>, typename std::conditional<lambda<Pred>::template apply<Ts>::type::value, list<>, list<Ts>>::type...>
    {
    };
}
template <typename L, typename Pred>
using remove_if = typename lazy::remove_if<L, Pred>::type;
namespace lazy
{
    template <typename L, typename T>
    struct remove;
    template <template<class...> class L, typename... Ts, typename T>
    struct remove<L<Ts...>, T>
    : ::brigand::detail::append_impl<L<>, typename std::conditional<std::is_same<Ts,T>::value, list<>, list<Ts>>::type...>
    {
    };
}
template <typename L, typename T>
using remove = typename lazy::remove<L, T>::type;
}
namespace brigand
{
  namespace detail
  {
    template<class ProtectedPred>
    struct not_pred
    {
      template<class... Ts>
      class apply
      {
        using bool_type = brigand::apply<typename ProtectedPred::type, Ts...>;
      public:
        using type = bool_<!bool_type::value>;
      };
    };
  }
  template<class Seq, class Pred>
  using partition = pair<remove_if<Seq, detail::not_pred<protect<Pred>>>, remove_if<Seq, Pred>>;
}
#include <type_traits>
namespace brigand
{
namespace detail
{
template <class Sequence, typename Predicate, typename NewType>
struct replace_if_impl
{
    using type = Sequence;
};
template <class Condition, class NewType, class T>
struct condition_test
: std::conditional<Condition::value, NewType, T>
{};
template <template <class...> class Sequence, typename Predicate, typename NewType, typename... T>
struct replace_if_impl<Sequence<T...>, Predicate, NewType>
{
    using type = Sequence<typename condition_test<
        ::brigand::apply<Predicate, T>, NewType, T
    >::type...>;
};
}
}
namespace brigand
{
namespace lazy
{
template <typename Sequence, typename Predicate, typename NewType>
using replace_if = typename detail::replace_if_impl<Sequence, Predicate, NewType>;
template <typename Sequence, typename OldType, typename NewType>
using replace = typename detail::replace_if_impl<Sequence,
                                                 std::is_same<OldType, brigand::_1>,
                                                 NewType>;
}
template <typename Sequence, typename Predicate, typename NewType>
using replace_if = typename ::brigand::lazy::replace_if<Sequence, Predicate, NewType>::type;
template <typename Sequence, typename OldType, typename NewType>
using replace = typename ::brigand::lazy::replace<Sequence, OldType, NewType>::type;
}
#include <type_traits>
#include <utility>
namespace brigand
{
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
}
namespace brigand
{
namespace detail
{
    template<typename TOut, typename TCurrent, typename TDelim, typename... Ts>
    struct split_impl;
    template<template<typename...> class L, typename... Os, typename... Cs, typename TDelim, typename T, typename... Ts>
    struct split_impl<L<Os...>, L<Cs...>, TDelim, T, Ts...> :
        split_impl<L<Os...>, L<Cs..., T>, TDelim, Ts...> {};
    template<template<typename...> class L, typename... Os, typename... Cs, typename TDelim, typename T>
    struct split_impl<L<Os...>, L<Cs...>, TDelim, T> {
        using type = L<Os..., L<Cs..., T>>;
    };
    template<template<typename...> class L, typename... Os, typename... Cs, typename TDelim, typename... Ts>
    struct split_impl<L<Os...>, L<Cs...>, TDelim, TDelim, Ts...> :
        split_impl<L<Os..., L<Cs...>>, L<>, TDelim, Ts...> {};
    template<template<typename...> class L, typename... Os, typename... Cs, typename TDelim>
    struct split_impl<L<Os...>, L<Cs...>, TDelim, TDelim> {
        using type = L<Os..., L<Cs...>>;
    };
    template<template<typename...> class L, typename... Os, typename TDelim, typename... Ts>
    struct split_impl<L<Os...>, L<>, TDelim, TDelim, Ts...> :
        split_impl<L<Os...>, L<>, TDelim, Ts...> {};
    template<template<typename...> class L, typename... Os, typename TDelim>
    struct split_impl<L<Os...>, L<>, TDelim, TDelim> {
        using type = L<Os...>;
    };
    template<template<typename...> class L, typename... Os, typename TDelim>
    struct split_impl<L<Os...>, L<>, TDelim> {
        using type = L<Os...>;
    };
    template<typename TList, typename TDelim>
    struct split_helper;
    template<template<typename...> class L, typename T, typename... Ts, typename TDelim>
    struct split_helper<L<T,Ts...>, TDelim> : split_impl<L<>, L<>, TDelim, T, Ts...>{};
    template<template<typename...> class L, typename... T, typename TDelim>
    struct split_helper<L<T...>, TDelim> {
        using type = L<>;
    };
}
namespace lazy
{
    template<typename TList, typename TDelim>
    using split = detail::split_helper<TList, TDelim>;
}
template<typename TList, typename TDelim>
using split = typename lazy::split<TList, TDelim>::type;
}
namespace brigand
{
namespace detail
{
    template <bool b, typename O, typename L, std::size_t I>
    struct split_at_impl;
    template <template <typename...> class S, typename... Os, typename T, typename... Ts>
    struct split_at_impl<false, S<Os...>, S<T, Ts...>, 0>
    {
        using type = S<S<Os...>, S<T, Ts...>>;
    };
    template <template <typename...> class S, typename... Os, typename... Ts>
    struct split_at_impl<false, S<Os...>, S<Ts...>, 0>
    {
        using type = S<S<Os...>, S<Ts...>>;
    };
    template <template <typename...> class S, typename... Os, typename T, typename... Ts,
              std::size_t I>
    struct split_at_impl<false, S<Os...>, S<T, Ts...>, I>
        : split_at_impl<false, S<Os..., T>, S<Ts...>, (I - 1)>
    {
    };
    template <template <typename...> class S, typename... Os, typename T1, typename T2, typename T3,
              typename T4, typename T5, typename T6, typename T7, typename T8, typename T9,
              typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
              typename T16, typename... Ts, std::size_t I>
    struct split_at_impl<
        true, S<Os...>,
        S<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, Ts...>, I>
        : split_at_impl<((I - 16) > 16), S<Os..., T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
                                           T13, T14, T15, T16>,
                        S<Ts...>, (I - 16)>
    {
    };
    template <typename L, typename I>
    struct call_split_at_impl : split_at_impl<(I::value > 16), brigand::clear<L>, L, I::value>
    {
    };
}
namespace lazy
{
    template <typename L, typename I>
    using split_at = ::brigand::detail::call_split_at_impl<L, I>;
}
template <typename L, typename I>
using split_at = typename ::brigand::lazy::split_at<L, I>::type;
}
namespace brigand
{
  template <typename A, typename B>
  struct less : bool_ < (A::value < B::value) > {};
}
namespace brigand
{
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
}
namespace brigand
{
namespace detail
{
    template <typename P>
    struct S
    {
        template <typename T, typename U>
        struct Pred : brigand::apply<P, T, U>
        {
        };
        template <typename Out, typename In, bool Tag, bool FTag, typename... Ts>
        struct insert;
        template <typename... Os, typename In, typename... Ts>
        struct insert<list<Os...>, list<In>, false, false, Ts...>
        {
            using type = list<Os..., In, Ts...>;
        };
        template <typename... Os, typename... Ins, typename T>
        struct insert<list<Os...>, list<Ins...>, true, false, T>
        {
            using type = list<Os..., T, Ins...>;
        };
        template <typename... Os, typename In1, typename In2, typename... Ins, typename T,
                  typename... Ts>
        struct insert<list<Os...>, list<In1, In2, Ins...>, false, false, T, Ts...>
            : insert<list<Os..., In1>, list<In2, Ins...>, Pred<T, In2>::value, false, T, Ts...>
        {
        };
        template <typename... Os, typename In1, typename In2, typename... Ins, typename T1,
                  typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
                  typename T8, typename... Ts>
        struct insert<list<Os...>, list<In1, In2, Ins...>, false, false, T1, T2, T3, T4, T5, T6, T7,
                      T8, Ts...>
            : insert<list<Os..., In1>, list<In2, Ins...>, Pred<T1, In2>::value,
                     Pred<T8, In2>::value, T1, T2, T3, T4, T5, T6, T7, T8, Ts...>
        {
        };
        template <typename... Os, typename In, typename... Ins, typename T1, typename T2,
                  typename... Ts>
        struct insert<list<Os...>, list<In, Ins...>, true, false, T1, T2, Ts...>
            : insert<list<Os..., T1>, list<In, Ins...>, Pred<T2, In>::value, false, T2, Ts...>
        {
        };
        template <typename... Os, typename In, typename... Ins, typename T1, typename T2,
                  typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        struct insert<list<Os...>, list<In, Ins...>, true, true, T1, T2, T3, T4, T5, T6, T7, T8>
        {
            using type = list<Os..., T1, T2, T3, T4, T5, T6, T7, T8, In, Ins...>;
        };
        template <typename... Os, typename In, typename... Ins, typename T1, typename T2,
                  typename T3, typename T4, typename T5, typename T6, typename T7, typename T8,
                  typename T9, typename... Ts>
        struct insert<list<Os...>, list<In, Ins...>, true, true, T1, T2, T3, T4, T5, T6, T7, T8, T9,
                      Ts...> : insert<list<Os..., T1, T2, T3, T4, T5, T6, T7, T8>, list<In, Ins...>,
                                      Pred<T9, In>::value, false, T9, Ts...>
        {
        };
        template <typename... Os, typename In, typename... Ins, typename T1, typename T2,
                  typename T3, typename T4, typename T5, typename T6, typename T7, typename T8,
                  typename T9, typename T10, typename T11, typename T12, typename T13, typename T14,
                  typename T15, typename T16, typename... Ts>
        struct insert<list<Os...>, list<In, Ins...>, true, true, T1, T2, T3, T4, T5, T6, T7, T8, T9,
                      T10, T11, T12, T13, T14, T15, T16, Ts...>
            : insert<list<Os..., T1, T2, T3, T4, T5, T6, T7, T8>, list<In, Ins...>,
                     Pred<T9, In>::value, Pred<T16, In>::value, T9, T10, T11, T12, T13, T14, T15,
                     T16, Ts...>
        {
        };
        template <typename Out, typename In>
        struct insert_helper;
        template <typename O, typename... Os, typename In, typename... Ins>
        struct insert_helper<list<O, Os...>, list<In, Ins...>>
            : insert<list<>, list<In, Ins...>, Pred<O, In>::value, false, O, Os...>
        {
        };
        template <typename O1, typename O2, typename O3, typename O4, typename O5, typename O6,
                  typename O7, typename O8, typename... Os, typename In, typename... Ins>
        struct insert_helper<list<O1, O2, O3, O4, O5, O6, O7, O8, Os...>, list<In, Ins...>>
            : insert<list<>, list<In, Ins...>, Pred<O1, In>::value, Pred<O8, In>::value, O1, O2, O3,
                     O4, O5, O6, O7, O8, Os...>
        {
        };
        template <typename Out, typename... Ts>
        struct sort_loop
        {
            using type = Out;
        };
        template <typename Out, typename In, typename... Ts>
        struct sort_loop<Out, In, Ts...>
            : sort_loop<typename insert_helper<Out, list<In>>::type, Ts...>
        {
        };
        template <typename Out, typename T1, typename T2, typename T3, typename T4, typename T5,
                  typename T6, typename T7, typename T8, typename T9, typename T10, typename T11,
                  typename T12, typename T13, typename T14, typename T15, typename T16,
                  typename... Ts>
        struct sort_loop<Out, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16,
                         Ts...>
            : sort_loop<typename insert_helper<
                            Out, typename sort_loop<list<T1>, T2, T3, T4, T5, T6, T7, T8, T9, T10,
                                                    T11, T12, T13, T14, T15, T16>::type>::type,
                        Ts...>
        {
        };
    };
    template <typename Seq, typename Comp>
    struct sort_impl;
    template <template <class...> class Seq, typename... T, typename Comp>
    struct sort_impl<Seq<T...>, Comp>
    {
        using type = Seq<T...>;
    };
    template <template <class...> class Seq, typename T, typename Comp>
    struct sort_impl<Seq<T>, Comp>
    {
        using type = Seq<T>;
    };
    template <template <class...> class Seq, typename T, typename U, typename... Ts, typename Comp>
    struct sort_impl<Seq<T, U, Ts...>, Comp>
    {
        using type =
            brigand::wrap<typename S<Comp>::template sort_loop<list<T>, U, Ts...>::type, Seq>;
    };
}
template <typename Seq, typename Comp = quote<less>>
using sort = typename detail::sort_impl<Seq, Comp>::type;
}
#include <type_traits>
namespace brigand
{
  template <typename A>
  struct complement : std::integral_constant< typename A::value_type
                                            , typename A::value_type(~A::value)
                                            > {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct divides : std::integral_constant < typename A::value_type, A::value / B::value > {};
}
namespace brigand
{
  template<class T>
  struct identity
  {
    using type = T;
  };
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct max : std::integral_constant < typename A::value_type
                                      , (A::value < B::value) ? B::value : A::value
                                      >
  {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct min : std::integral_constant < typename A::value_type
                                      , (A::value < B::value) ? A::value : B::value
                                      >
  {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct minus : std::integral_constant < typename A::value_type, A::value - B::value > {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct modulo : std::integral_constant < typename A::value_type, A::value % B::value > {};
}
#include <type_traits>
namespace brigand
{
  template <typename A>
  struct negate : std::integral_constant < typename A::value_type, -A::value > {};
}
#include <type_traits>
namespace brigand
{
  template <typename A>
  struct next : std::integral_constant < typename A::value_type, A::value + 1 > {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct plus : std::integral_constant < typename A::value_type, A::value + B::value > {};
}
#include <type_traits>
namespace brigand
{
  template <typename A>
  struct prev : std::integral_constant < typename A::value_type, A::value - 1 > {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct times : std::integral_constant < typename A::value_type, A::value * B::value > {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct bitand_ : std::integral_constant<typename A::value_type, A::value & B::value> {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct bitor_ : std::integral_constant<typename A::value_type, A::value | B::value> {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct bitxor_ : std::integral_constant<typename A::value_type, A::value ^ B::value> {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct shift_left : std::integral_constant<typename A::value_type, (A::value << B::value)> {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct shift_right : std::integral_constant<typename A::value_type, (A::value >> B::value)> {};
}
namespace brigand
{
  template <typename A, typename B>
  struct equal_to : bool_ < (A::value == B::value) > {};
}
namespace brigand
{
  template <typename A, typename B>
  struct greater : bool_<(A::value > B::value) > {};
}
namespace brigand
{
  template <typename A, typename B>
  struct greater_equal : bool_ < (A::value >= B::value) > {};
}
namespace brigand
{
  template <typename A, typename B>
  struct less_equal : bool_ < (A::value <= B::value) > {};
}
namespace brigand
{
  template <typename A, typename B>
  struct not_equal_to : bool_ < (A::value != B::value) > {};
}
#include <type_traits>
namespace brigand
{
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
}
#include <type_traits>
namespace brigand
{
  template <typename Condition, typename A, typename B>
  struct if_ : std::conditional<Condition::value, A, B> {};
  template <bool Condition, typename A, typename B>
  struct if_c : std::conditional<Condition, A, B> {};
}
#include <type_traits>
namespace brigand
{
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
      using type = brigand::apply<X,Us...>;
    };
    template<typename X, typename L> using bind_impl_t = typename bind_impl<X,L>::type;
  }
  template<typename MetafunctionClass, typename... Args> struct bind
  {
    template<typename... Us> struct apply
    {
      using type = brigand::apply < detail::bind_impl_t<MetafunctionClass,list<Us...>>
                                  , detail::bind_impl_t<Args,list<Us...>>...
                                  >;
    };
  };
}
namespace brigand
{
  template<typename Functor> struct unpack {};
  template<class F> struct lambda<unpack<F>>
  {
    template<typename X> struct apply;
    template<template<class...> class List, typename... Types>
    struct apply<List<Types...>> : brigand::apply<F,Types...>
    {};
  };
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct and_ : std::integral_constant <typename A::value_type, A::value && B::value > {};
}
#include <type_traits>
namespace brigand
{
  template <typename T>
  struct not_ : std::integral_constant<typename T::value_type, !T::value> {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct or_ : std::integral_constant < typename A::value_type, A::value || B::value > {};
}
#include <type_traits>
namespace brigand
{
  template <typename A, typename B>
  struct xor_ : std::integral_constant<typename A::value_type, A::value != B::value> {};
}
namespace brigand
{
  template<class T>
  struct always
  {
    template<typename X> struct apply { using type = T; };
  };
}
namespace brigand
{
namespace detail
{
    template<template<class> class F, unsigned N, class T>
    struct repeat_impl
    : repeat_impl<F, N-7, F<F<F<F<F<F<F<T>>>>>>>>
    {};
    template<template<class> class F, class T>
    struct repeat_impl<F, 7, T>
    {
        using type = F<F<F<F<F<F<F<T>>>>>>>;
    };
    template<template<class> class F, class T>
    struct repeat_impl<F, 6, T>
    {
        using type = F<F<F<F<F<F<T>>>>>>;
    };
    template<template<class> class F, class T>
    struct repeat_impl<F, 5, T>
    {
        using type = F<F<F<F<F<T>>>>>;
    };
    template<template<class> class F, class T>
    struct repeat_impl<F, 4, T>
    {
        using type = F<F<F<F<T>>>>;
    };
    template<template<class> class F, class T>
    struct repeat_impl<F, 3, T>
    {
        using type = F<F<F<T>>>;
    };
    template<template<class> class F, class T>
    struct repeat_impl<F, 2, T>
    {
        using type = F<F<T>>;
    };
    template<template<class> class F, class T>
    struct repeat_impl<F, 1, T>
    {
        using type = F<T>;
    };
    template<template<class> class F, class T>
    struct repeat_impl<F, 0, T>
    {
        using type = T;
    };
}
namespace lazy
{
    template<template<class> class F, class N, class T>
    using repeat = typename detail::repeat_impl<F, N::value, T>;
}
    template<template<class> class F, class N, class T>
    using repeat = typename ::brigand::lazy::repeat<F, N, T>::type;
}
#include <type_traits>
namespace brigand
{
  template<typename T>
  struct sizeof_ : std::integral_constant <std::size_t, sizeof(T)> {};
}
namespace brigand
{
  namespace detail
  {
    template<class L, class... T> struct push_front_impl;
    template<template<class...> class L, class... U, class... T>
    struct push_front_impl<L<U...>, T...>
    {
      using type = L<T..., U...>;
    };
  }
  template<class L, class... T>
  using push_front = typename detail::push_front_impl<L, T...>::type;
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
  namespace detail
  {
    template <class L, std::size_t N> struct pop_front_impl;
    template<template<class...> class L, class T, class... U>
    struct pop_front_impl<L<T, U...>, 1>
    {
      using type = L<U...>;
    };
    template<template<class...> class L, class> struct pop_front_element;
    template<template<class...> class L, class... Ts>
    struct pop_front_element<L, list<Ts...>>
    {
      template<class... Us>
      static L<Us...> impl(Ts..., type_<Us>*...);
    };
    template<template<class...> class L, class... Ts, std::size_t N>
    struct pop_front_impl<L<Ts...>, N>
    {
      using type = decltype(pop_front_element<L, filled_list<
        void const *, N
      >>::impl(static_cast<type_<Ts>*>(nullptr)...));
    };
  }
  template <class L, class N = std::integral_constant<std::size_t, 1>>
  using pop_front = typename detail::pop_front_impl<L, N::value>::type;
}
namespace brigand
{
  namespace detail
  {
    template<class L, class... T> struct push_back_impl;
    template<template<class...> class L, class... U, class... T>
    struct push_back_impl<L<U...>, T...>
    {
        using type = L<U..., T...>;
    };
  }
  template<class L, class... T>
  using push_back = typename detail::push_back_impl<L, T...>::type;
  template <class L>
  using back = at_c<L, size<L>::value-1>;
  template <class L, class N = std::integral_constant<std::size_t, 1>>
  using pop_back = front<split_at<L, std::integral_constant<std::size_t, size<L>::value - N::value>>>;
}
namespace brigand
{
namespace detail
{
    template <template <class...> class L, class First, class... R>
    struct without_last_element
    {
        using type = append<L<First>, typename without_last_element<L, R...>::type>;
    };
    template <template <class...> class L, class Last>
    struct without_last_element<L, Last>
    {
      using type = L<>;
    };
} }
namespace brigand
{
namespace detail
{
    template<class Start, unsigned N, class Next, class... E>
    struct mksq8
    : mksq8<brigand::apply<Next, Start>, N-1, Next, E..., Start>
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
        using t1 = brigand::apply<Next, Start>;
        using t2 = brigand::apply<Next, t1>;
        using t3 = brigand::apply<Next, t2>;
        using t4 = brigand::apply<Next, t3>;
        using t5 = brigand::apply<Next, t4>;
        using t6 = brigand::apply<Next, t5>;
        using t7 = brigand::apply<Next, t6>;
        using type = list<Start, t1, t2, t3, t4, t5, t6, t7>;
    };
    template<template<class...> class List, class Start, unsigned N, class Next, bool, class... L>
    struct make_sequence_impl
    : make_sequence_impl<
        List,
        brigand::apply<Next, typename mksq8<Start, 8, Next>::t7>,
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
}
#include <type_traits>
namespace brigand
{
    template<class L, std::size_t Index>
    using erase_c = append<
        front<split_at<L, size_t<Index>>>,
        pop_front<back<split_at<L, size_t<Index>>>>
    >;
namespace detail
{
    template <class... U>
    struct exact_eraser;
    template <>
    struct exact_eraser<>
    {
        template <typename K>
        static exact_eraser<> erase(type_<K>);
    };
    template <class U0>
    struct exact_eraser<U0>
    {
        static exact_eraser<> erase(type_<U0>);
        template <typename K>
        static exact_eraser<U0> erase(type_<K>);
    };
    template <class U0, class... U>
    struct exact_eraser<U0, U...>
    {
        static exact_eraser<U...> erase(type_<U0>);
        template <typename K>
        using recursive_exact_erase = decltype(exact_eraser<U...>::erase(type_<K>{}));
        template <typename K>
        static append<exact_eraser<U0>, recursive_exact_erase<K>> erase(type_<K>);
    };
    template <class U0, class U1, class... U>
    struct exact_eraser<U0, U1, U...>
    {
        static exact_eraser<U1, U...> erase(type_<U0>);
        static exact_eraser<U0, U...> erase(type_<U1>);
        template <typename K>
        using recursive_exact_erase = decltype(exact_eraser<U...>::erase(type_<K>{}));
        template <typename K>
        static append<exact_eraser<U0, U1>, recursive_exact_erase<K>> erase(type_<K>);
    };
    template <class U0, class U1, class U2, class... U>
    struct exact_eraser<U0, U1, U2, U...>
    {
        static exact_eraser<U1, U2, U...> erase(type_<U0>);
        static exact_eraser<U0, U2, U...> erase(type_<U1>);
        static exact_eraser<U0, U1, U...> erase(type_<U2>);
        template <typename K>
        using recursive_exact_erase = decltype(exact_eraser<U...>::erase(type_<K>{}));
        template <typename K>
        static append<exact_eraser<U0, U1, U2>, recursive_exact_erase<K>> erase(type_<K>);
    };
    template <class U0, class U1, class U2, class U3, class... U>
    struct exact_eraser<U0, U1, U2, U3, U...>
    {
        static exact_eraser<U1, U2, U3, U...> erase(type_<U0>);
        static exact_eraser<U0, U2, U3, U...> erase(type_<U1>);
        static exact_eraser<U0, U1, U3, U...> erase(type_<U2>);
        static exact_eraser<U0, U1, U2, U...> erase(type_<U3>);
        template <typename K>
        using recursive_exact_erase = decltype(exact_eraser<U...>::erase(type_<K>{}));
        template <typename K>
        static append<exact_eraser<U0, U1, U2, U3>, recursive_exact_erase<K>> erase(type_<K>);
    };
    template <class U0, class U1, class U2, class U3, class U4, class... U>
    struct exact_eraser<U0, U1, U2, U3, U4, U...>
    {
        static exact_eraser<U1, U2, U3, U4, U...> erase(type_<U0>);
        static exact_eraser<U0, U2, U3, U4, U...> erase(type_<U1>);
        static exact_eraser<U0, U1, U3, U4, U...> erase(type_<U2>);
        static exact_eraser<U0, U1, U2, U4, U...> erase(type_<U3>);
        static exact_eraser<U0, U1, U2, U3, U...> erase(type_<U4>);
        template <typename K>
        using recursive_exact_erase = decltype(exact_eraser<U...>::erase(type_<K>{}));
        template <typename K>
        static append<exact_eraser<U0, U1, U2, U3, U4>, recursive_exact_erase<K>> erase(type_<K>);
    };
}
namespace detail
{
    template< class L1, template<class> class Pred, class L2 >
    struct erase_if_impl;
    template< class L1, template<class> class Pred, class L2, bool >
    struct erase_if_shortcut;
    template< template<class...> class L1, class T, class... Ts,
            template<class> class Pred,
            template<class...> class L2, class... Us >
    struct erase_if_shortcut<L1<T, Ts...>, Pred, L2<Us...>, true>
    {
        using type = L2<Us..., Ts...>;
    };
    template< template<class...> class L1, class T, class... Ts,
            template<class> class Pred,
            template<class...> class L2, class... Us >
    struct erase_if_shortcut<L1<T, Ts...>, Pred, L2<Us...>, false>
    : erase_if_impl<L1<Ts...>, Pred, L2<Us..., T>>
    {};
    template< template<class...> class L1, class T, class... Ts,
            template<class> class Pred, class L2 >
    struct erase_if_impl<L1<T, Ts...>, Pred, L2>
    : erase_if_shortcut<L1<T, Ts...>, Pred, L2, bool(Pred<T>::value)>
    {};
    template< template<class...> class L1,
            template<class> class Pred,
            class L2 >
    struct erase_if_impl<L1<>, Pred, L2>
    {
        using type = L2;
    };
    template <typename T>
    struct has_erase_method
    {
        struct dummy {};
        template <typename C, typename P>
        static auto test(P * p) -> decltype(C::erase(type_<P>{}), std::true_type());
        template <typename, typename>
        static std::false_type test(...);
        static const bool value = std::is_same<std::true_type, decltype(test<T, dummy>(nullptr))>::value;
    };
    template<class L, class I, bool>
    struct erase_dispatch
    {
        using type = erase_c<L, I::value>;
    };
    template<class C, class K>
    struct erase_dispatch<C, K, true>
    {
        using type = decltype(C::erase(type_<K>{}));
    };
}
    template<class L, class K>
    using erase = typename detail::erase_dispatch<L, K, detail::has_erase_method<L>::value>::type;
}
namespace brigand
{
namespace detail
{
    template <class C, class T>
    struct insert_impl
    {
        using type = decltype(C::insert(type_<T>{}));
    };
}
    template<class L, class T>
    using insert = typename detail::insert_impl<L, T>::type;
}
namespace brigand
{
namespace detail
{
    template <class L, class K>
    struct contains_impl
    {
        using type = decltype(L::contains(type_<K>{}));
    };
}
    template <class L, class K>
    using contains = typename detail::contains_impl<L, K>::type;
}
namespace brigand
{
namespace detail
{
    template<class... Ts>
    struct make_set;
    template<class U, class K>
    struct set_erase_pred_impl
    : std::conditional<std::is_same<U, K>::value, list<>, list<U>>
    {
    };
    template <class... T>
    struct set_impl
    {
        template <typename U, typename = decltype(static_cast<type_<U>>(make_set<T...>()))>
        static std::true_type contains(type_<U>);
        template <typename U>
        static std::false_type contains(U);
    private:
        template <class K>
        struct contains_predicate_impl
        {
            using type = decltype(set_impl<T...>::contains(K{}));
        };
        template <typename K>
        using contains_predicate = typename contains_predicate_impl<K>::type;
    public:
        template <typename U>
        static contains_predicate<type_<U>> has_key(type_<U>);
    public:
        template <class K>
        static append<set_impl<>, typename set_erase_pred_impl<T, K>::type...> erase(type_<K>);
    private:
        template<class K>
        static set_impl<T..., K> insert_impl(std::false_type);
        template<class K>
        static set_impl insert_impl(std::true_type);
    public:
        template<class K>
        static decltype(set_impl<T...>::insert_impl<K>(contains_predicate<type_<K>>())) insert(type_<K>);
    };
    template<class... Ts>
    struct make_set : type_<Ts>...
    {
      using type = set_impl<Ts...>;
    };
}
    template<class... Ts>
    using set = typename detail::make_set<Ts...>::type;
}
namespace brigand
{
  struct empty_base {};
}
namespace brigand
{
  template<typename... Ts> struct inherit;
  template<typename T> struct inherit<T>
  {
    struct type : public T {};
  };
  template<> struct inherit<>
  {
    using type = empty_base;
  };
  template<> struct inherit<empty_base>
  {
    using type = empty_base;
  };
  template<typename T1, typename T2> struct inherit<T1,T2>
  {
    struct type : public T1, T2 {};
  };
  template<typename T1> struct inherit<T1,empty_base>
  {
    using type = T1;
  };
  template<typename T2> struct inherit<empty_base,T2>
  {
    using type = T2;
  };
  template<> struct inherit<empty_base,empty_base>
  {
    using type = empty_base;
  };
  template<typename T1, typename T2, typename T3, typename... Ts>
  struct  inherit<T1, T2, T3, Ts...>
        : inherit<T1, typename inherit<T2,typename inherit<T3, Ts...>::type>::type>
  {};
}
namespace brigand
{
  namespace lazy
  {
    template< typename Types
            , typename Node
            , typename Root = brigand::empty_base
            >
    struct inherit_linearly
    {
      using type = brigand::fold<Types,Root,Node>;
    };
  }
  template< typename Types
            , typename Node
            , typename Root = brigand::empty_base
            >
  using inherit_linearly = typename lazy::inherit_linearly<Types,Node,Root>::type;
}
#include <type_traits>
#include <cstdint>
#include <cstring>
namespace brigand
{
  template<typename RealType, typename Type, Type Value>
  struct real_ : std::integral_constant<Type,Value>
  {
    using value_type  = RealType;
    using parent      = std::integral_constant<Type,Value>;
    inline operator value_type() const
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

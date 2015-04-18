#ifndef PYTHONIC_TYPES_NUMPY_EXPR_HPP
#define PYTHONIC_TYPES_NUMPY_EXPR_HPP

#include "pythonic/utils/meta.hpp"

namespace pythonic {

    namespace types {
        template<class Expr>
            struct is_numexpr_arg;
        template<class Expr, class... Slice>
            struct numpy_gexpr;

        /* Expression template for numpy expressions - binary operators
         */
        template<class Op, class... Args>
            struct numpy_expr {
                using first_arg = typename utils::front<Args...>::type;
                static const bool is_vectorizable = utils::all_of<std::remove_reference<Args>::type::is_vectorizable...>::value
                  and utils::all_of<std::is_same<typename std::remove_cv<typename std::remove_reference<first_arg>::type>::type::dtype,
                                                 typename std::remove_cv<typename std::remove_reference<Args>::type>::type::dtype
                                                >::value...
                                   >::value
                  and types::is_vector_op<Op>::value;
                static const bool is_strided = utils::any_of<std::remove_reference<Args>::type::is_strided...>::value;
                typedef const_nditerator<numpy_expr> iterator;
                static constexpr size_t value = utils::max_element<std::remove_reference<Args>::type::value...>::value;
                typedef decltype(Op()(std::declval<typename std::remove_reference<Args>::type::value_type>()...)) value_type;
                typedef decltype(Op()(std::declval<typename std::remove_reference<Args>::type::dtype>()...)) dtype;

                std::tuple<typename std::remove_reference<Args>::type...> args;
                array<long, value> _shape;

                numpy_expr() {}
                numpy_expr(numpy_expr const&) = default;
                numpy_expr(numpy_expr &&) = default;

                numpy_expr(Args const &...args) : args(args...), _shape(std::get<utils::max_element<Args::value...>::index>(this->args).shape()) {
                }

                iterator begin() const { return iterator(*this, 0); }
                iterator end() const { return iterator(*this, _shape[0]); }

                template<int... I>
                auto _fast(long i, utils::seq<I...>) const -> decltype(Op()(std::get<I-1>(args).fast(i)...)) {
                    return Op()(std::get<I-1>(args).fast(i)...); //FIXME: broadcasting can be achieved here through a modulus, but that's terribly costly
                }
                auto fast(long i) const -> decltype(this->_fast(i, typename utils::gens<1+sizeof...(Args)>::type{})) {
                    return _fast(i, typename utils::gens<1+sizeof...(Args)>::type{});
                }

                auto operator[](long i) const -> decltype(this->fast(i)) {
                    if(i<0) i += _shape[0];
                    return fast(i);
                }
                auto operator()(long i) const -> decltype(this->fast(i)) {
                    if(i<0) i += _shape[0];
                    return fast(i);
                }
                array<long, value> const& shape() const {return _shape;}
#ifdef USE_BOOST_SIMD
                template<int... I>
                auto _load(long i, utils::seq<I...>) const -> decltype(Op()(std::get<I-1>(args).load(i)...)) {
                  return Op()(std::get<I-1>(args).load(i)...);
                }
                template<class I> // template to prevent automatic instantiation when the type is not vectorizable
                auto load(I i) const -> decltype(this->_load(i, typename utils::gens<1+sizeof...(Args)>::type{})) {
                  return _load(i, typename utils::gens<1+sizeof...(Args)>::type{});
                }
#endif
                template<int... I, class... S>
                auto
                _get(utils::seq<I...>, S const&... s) const
                -> decltype(Op{}(std::get<I-1>(args)(s...)...))
                {
                  return Op{}(std::get<I-1>(args)(s...)...);
                }

                template<class S0, class... S>
                auto operator()(S0 const& s0, S const&... s) const
                ->
                typename std::enable_if<not std::is_scalar<S0>::value,
                                        decltype(this->_get(typename utils::gens<1+sizeof...(Args)>::type{}, s0, s...))
                                       >::type
                {
                    return _get(typename utils::gens<1+sizeof...(Args)>::type{}, s0, s...);
                }

                template<class F>
                    typename std::enable_if<is_numexpr_arg<F>::value, numpy_fexpr<numpy_expr, F>>::type
                    fast(F const& filter) const {
                        return numpy_fexpr<numpy_expr, F>(*this, filter);
                    }
                template<class F>
                    typename std::enable_if<is_numexpr_arg<F>::value, numpy_fexpr<numpy_expr, F>>::type
                    operator[](F const& filter) const {
                        return fast(filter);
                    }

                template<int... I>
                long _flat_size(utils::seq<I...>) const {
                  long const sizes[] = {std::get<I-1>(args).flat_size()...};
                  return *std::max_element(std::begin(sizes), std::end(sizes));
                }
                long flat_size() const {
                  return _flat_size(typename utils::gens<1+sizeof...(Args)>::type{}); }
            };

    }


    template<class Op, class... Arg>
        struct assignable<types::numpy_expr<Op, Arg...>>
        {
            typedef typename types::numpy_expr_to_ndarray<types::numpy_expr<Op, Arg...>>::type type;
        };
    template<class Op, class... Arg>
        struct lazy<types::numpy_expr<Op,Arg...>>
        {
            typedef types::numpy_expr<Op,typename lazy<Arg>::type...> type;
        };
}
/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"
template<class Op, class K, class... Args>
struct __combined<pythonic::types::numpy_expr<Op, Args...>, indexable<K>> {
    typedef pythonic::types::numpy_expr<Op, Args...> type;
};

template<class Op, class K, class... Args>
struct __combined<indexable<K>, pythonic::types::numpy_expr<Op, Args...>> {
    typedef pythonic::types::numpy_expr<Op, Args...> type;
};

template<class Op, class K, class V, class... Args>
struct __combined<pythonic::types::numpy_expr<Op, Args...>, indexable_container<K,V>> {
    typedef pythonic::types::numpy_expr<Op, Args...> type;
};

template<class Op, class K, class V, class... Args>
struct __combined<indexable_container<K,V>, pythonic::types::numpy_expr<Op, Args...>> {
    typedef pythonic::types::numpy_expr<Op, Args...> type;
};

template<class Op, class K, class... Args>
struct __combined<container<K>, pythonic::types::numpy_expr<Op, Args...>> {
    typedef pythonic::types::numpy_expr<Op, Args...> type;
};

template<class Op, class K, class... Args>
struct __combined<pythonic::types::numpy_expr<Op, Args...>, container<K>> {
    typedef pythonic::types::numpy_expr<Op, Args...> type;
};

template<class Op, class Op2, class... Args, class... Args2>
struct __combined<pythonic::types::numpy_expr<Op, Args...>, pythonic::types::numpy_expr<Op2, Args2...>> {
    typedef typename pythonic::types::numpy_expr_to_ndarray<pythonic::types::numpy_expr<Op, Args...>>::type type;
};
/*}*/
#endif


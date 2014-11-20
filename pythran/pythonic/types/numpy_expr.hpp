#ifndef PYTHONIC_TYPES_NUMPY_EXPR_HPP
#define PYTHONIC_TYPES_NUMPY_EXPR_HPP

namespace pythonic {

    namespace types {
        template<class Expr>
            struct is_numexpr_arg;
        template<class Expr, class... Slice>
            struct numpy_gexpr;

        /* Expression template for numpy expressions - binary operators
         */
        template<class Op, class Arg0, class Arg1>
            struct numpy_expr {
                static const bool is_vectorizable = std::remove_reference<Arg0>::type::is_vectorizable and std::remove_reference<Arg1>::type::is_vectorizable
                  and std::is_same<typename std::remove_cv<typename std::remove_reference<Arg0>::type>::type::dtype,
                                   typename std::remove_cv<typename std::remove_reference<Arg1>::type>::type::dtype
                                  >::value
                  and types::is_vector_op<Op>::value;
                static const bool is_strided = std::remove_reference<Arg0>::type::is_strided or std::remove_reference<Arg1>::type::is_strided;
                typedef const_ndbiterator<numpy_expr<Op, Arg0, Arg1>> iterator;
                static constexpr size_t value = std::remove_reference<Arg0>::type::value>std::remove_reference<Arg1>::type::value?std::remove_reference<Arg0>::type::value: std::remove_reference<Arg1>::type::value;
                typedef decltype(Op()(std::declval<typename std::remove_reference<Arg0>::type::value_type>(), std::declval<typename std::remove_reference<Arg1>::type::value_type>())) value_type;
                typedef decltype(Op()(std::declval<typename std::remove_reference<Arg0>::type::dtype>(), std::declval<typename std::remove_reference<Arg1>::type::dtype>())) dtype;

                typename std::remove_reference<Arg0>::type arg0;
                typename std::remove_reference<Arg1>::type arg1;
                array<long, value> shape;
                long _size;

                numpy_expr() {}
                numpy_expr(numpy_expr const&) = default;
                numpy_expr(numpy_expr &&) = default;

                numpy_expr(Arg0 const &arg0, Arg1 const &arg1) : arg0(arg0), arg1(arg1) {
                  for(int i=0; i < value; ++i)
                    shape[i] = std::max(arg0.shape[i], arg1.shape[i]);
                  _size = std::accumulate(shape.begin(), shape.end(), 1L, std::multiplies<long>());
                }

                iterator begin() const { return iterator(*this, 0, arg0.shape[0], arg1.shape[0]); }
                iterator end() const { return iterator(*this, shape[0], arg0.shape[0], arg1.shape[0]); }

                auto fast(long i, long j) const -> decltype(Op()(arg0.fast(i), arg1.fast(j))) {
                  return Op()(arg0.fast(i), arg1.fast(j));
                }

                auto fast(long i) const -> decltype(Op()(arg0.fast(i), arg1.fast(i))) {
                  return Op()(arg0.fast(i%arg0.shape[0]), arg1.fast(i % arg1.shape[0])); //FIXME: broadcasting is achieved here through a modulus, but that's terribly costly
                }

                auto operator[](long i) const -> decltype(this->fast(i)) {
                    if(i<0) i += shape[0];
                    return fast(i);
                }
#ifdef USE_BOOST_SIMD
                template<class I> // template to prevent automatic instantiation when the type is not vectorizable
                auto load(I i) const -> decltype(Op()(arg0.load(i), arg1.load(i))) {
                  return Op()(arg0.load(i), arg1.load(i));
                }
#endif

                template<class... S>
                numpy_expr<Op, numpy_gexpr<Arg0, contiguous_slice, S...>, numpy_gexpr<Arg1, contiguous_slice, S...>>
                operator()(contiguous_slice const& s0, S const&... s) const {
                    return numpy_expr<Op, numpy_gexpr<Arg0, contiguous_slice, S...>, numpy_gexpr<Arg1, contiguous_slice, S...>>(
                            arg0(s0, s...),
                            arg1(s0, s...)
                            );
                }
                template<class... S>
                numpy_expr<Op, numpy_gexpr<Arg0, slice, S...>, numpy_gexpr<Arg1, slice, S...>>
                operator()(slice const& s0, S const&... s) const {
                    return numpy_expr<Op, numpy_gexpr<Arg0, slice, S...>, numpy_gexpr<Arg1, slice, S...>>(
                            arg0(s0, s...),
                            arg1(s0, s...)
                            );
                }

                numpy_expr<Op, numpy_gexpr<Arg0, slice>, numpy_gexpr<Arg1, slice>>
                operator[](slice const& s0) const {
                    return numpy_expr<Op, numpy_gexpr<Arg0, slice>, numpy_gexpr<Arg1, slice>>(
                            arg0[s0],
                            arg1[s0]
                            );
                }
                numpy_expr<Op, numpy_gexpr<Arg0, contiguous_slice>, numpy_gexpr<Arg1, contiguous_slice>>
                operator[](contiguous_slice const& s0) const {
                    return numpy_expr<Op, numpy_gexpr<Arg0, contiguous_slice>, numpy_gexpr<Arg1, contiguous_slice>>(
                            arg0[s0],
                            arg1[s0]
                            );
                }

                template<class F>
                    typename std::enable_if<is_numexpr_arg<F>::value, numpy_fexpr<numpy_expr, F>>::type
                    operator[](F const& filter) const {
                        return numpy_fexpr<numpy_expr, F>(*this, filter);
                    }

                long size() const { return _size; }
            };

    }


    template<class Op, class Arg0, class Arg1>
        struct assignable<types::numpy_expr<Op, Arg0, Arg1>>
        {
            typedef typename types::numpy_expr_to_ndarray<types::numpy_expr<Op, Arg0, Arg1>>::type type;
        };
    template<class Op, class Arg0, class Arg1>
        struct lazy<types::numpy_expr<Op,Arg0,Arg1>>
        {
            typedef types::numpy_expr<Op,typename lazy<Arg0>::type, typename lazy<Arg1>::type> type;
        };
}
/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"
template<class Arg0, class Arg1, class Op, class K>
struct __combined<pythonic::types::numpy_expr<Op, Arg0, Arg1>, indexable<K>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<indexable<K>, pythonic::types::numpy_expr<Op, Arg0, Arg1>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Arg1, class Op, class K, class V>
struct __combined<pythonic::types::numpy_expr<Op, Arg0, Arg1>, indexable_container<K,V>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Arg1, class Op, class K, class V>
struct __combined<indexable_container<K,V>, pythonic::types::numpy_expr<Op, Arg0, Arg1>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<container<K>, pythonic::types::numpy_expr<Op, Arg0, Arg1>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<pythonic::types::numpy_expr<Op, Arg0, Arg1>, container<K>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Arg1, class Op, class Op2, class Arg2, class Arg3>
struct __combined<pythonic::types::numpy_expr<Op, Arg0, Arg1>, pythonic::types::numpy_expr<Op2, Arg2, Arg3>> {
    typedef typename pythonic::types::numpy_expr_to_ndarray<pythonic::types::numpy_expr<Op, Arg0, Arg1>>::type type;
};
/*}*/
#endif


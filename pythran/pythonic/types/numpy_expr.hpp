#ifndef PYTHONIC_TYPES_NUMPY_EXPR_HPP
#define PYTHONIC_TYPES_NUMPY_EXPR_HPP

namespace pythonic {

    namespace types {
        template<class Expr>
            struct is_numexpr_arg;
        template<class Expr, class... Slice>
            struct numpy_gexpr;

        template<class Op, class I0, class I1>
            struct const_expr_iterator : public std::iterator<std::random_access_iterator_tag,
                                                              decltype(std::declval<Op>()(std::declval<typename std::iterator_traits<I0>::value_type>(),
                                                                                          std::declval<typename std::iterator_traits<I1>::value_type>()))>
            {
                enum { NO_BROADCAST, BROADCAST_SHAPE0, BROADCAST_SHAPE1} const mode;
                I0 index0, beg0, end0;
                I1 index1, beg1, end1;

                const_expr_iterator(I0 const& index0, I0 const& end0, I1 const& index1, I1 const& end1) :
                  mode{(end1 - index1) == (end0 - index0) ? NO_BROADCAST : (end1 - index1) > (end0 - index0) ? BROADCAST_SHAPE0 : BROADCAST_SHAPE1},
                  index0{index0}, beg0{index0}, end0{end0}, index1{index1}, beg1{index1}, end1{end1}
                {
                }


                // TODO: This "auto" is different than E::value_type, which is weird (if not wrong)
                auto operator*() const -> decltype(Op{}(*index0, *index1)) {
                  return Op{}(*index0, *index1);
                }
                const_expr_iterator& operator++() {
                  ++index0; ++index1;
                  if(mode == NO_BROADCAST);
                  else if(mode == BROADCAST_SHAPE0) {if(index0==end0) index0=beg0;}
                  else if(mode == BROADCAST_SHAPE1) {if(index1==end1) index1=beg1;}
                  return *this;
                }
                long operator-(const_expr_iterator const &other) const {
                  return std::max(index0 - other.index0, index1 - other.index1);
                }
                bool operator!=(const_expr_iterator const& other) const {
                    return mode == BROADCAST_SHAPE1 ? index0 != other.index0 : index1 != other.index1;
                }
                bool operator==(const_expr_iterator const& other) const {
                    return mode == BROADCAST_SHAPE1 ? index0 == other.index0 : index1 == other.index1;
                }
                bool operator<(const_expr_iterator const& other) const {
                    return mode == BROADCAST_SHAPE1 ? index0 < other.index0 : index1 < other.index1;
                }
                const_expr_iterator& operator=(const_expr_iterator const& that) {
                  assert(that.beg0 == beg0);
                  assert(that.end0 == end0);
                  assert(that.beg1 == beg1);
                  assert(that.end1 == end1);
                  assert(that.mode == mode);
                  index0 = that.index0;
                  index1 = that.index1;
                  return *this;
                }
            };

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
                typedef const_expr_iterator<Op, typename Arg0::const_iterator, typename Arg1::const_iterator> const_iterator;
                static constexpr size_t value = (std::remove_reference<Arg0>::type::value > std::remove_reference<Arg1>::type::value)
                                               ?(std::remove_reference<Arg0>::type::value)
                                               :(std::remove_reference<Arg1>::type::value);
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
                  for(size_t i=0; i < value; ++i) {
                    // handle shape broadcasting here
                    if(i < std::remove_reference<Arg0>::type::value and i < std::remove_reference<Arg1>::type::value)
                      shape[i] = std::max(arg0.shape[i], arg1.shape[i]);
                    else if(i < std::remove_reference<Arg0>::type::value)
                      shape[i] = arg0.shape[i];
                    else if(i < std::remove_reference<Arg1>::type::value)
                      shape[i] = arg1.shape[i];
                    else
                      assert(false);
                  }
                  _size = std::accumulate(shape.begin(), shape.end(), 1L, std::multiplies<long>());
                }

                const_iterator begin() const { return const_iterator(arg0.begin(), arg0.end(), arg1.begin(), arg1.end()); }
                const_iterator end() const { return const_iterator(arg0.end(), arg0.end(), arg1.end(), arg1.end()); }

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


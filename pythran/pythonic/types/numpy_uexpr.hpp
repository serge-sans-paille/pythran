#ifndef PYTHONIC_TYPES_NUMPY_UEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_UEXPR_HPP

namespace pythonic {

    namespace types {
        template<class Op, class I>
            struct const_uexpr_iterator : public std::iterator<std::random_access_iterator_tag,
                                                               decltype(std::declval<Op>()(std::declval<typename std::iterator_traits<I>::value_type>()))>
            {
                I index;
                const_uexpr_iterator(I const& index) : index(index) {
                }


                // TODO: This "auto" is different than E::value_type, which is weird (if not wrong)
                auto operator*() const -> decltype(Op{}(*index)) { return Op{}(*index); }
                const_uexpr_iterator& operator++() { ++index; return *this;}
                long operator-(const_uexpr_iterator const& other) const {
                    return index - other.index;
                }
                bool operator!=(const_uexpr_iterator const& other) const {
                    return index != other.index;
                }
                bool operator==(const_uexpr_iterator const& other) const {
                    return index == other.index;
                }
                bool operator<(const_uexpr_iterator const& other) const {
                    return  index <  other.index;
                }
                const_uexpr_iterator& operator=(const_uexpr_iterator const& other) { index = other.index; return *this;}
                const_uexpr_iterator& operator-=(size_t n) { index -= n; return *this;}
            };
        /* Expression template for numpy expressions - unary operators
         */
        template<class Op, class Arg>
            struct numpy_uexpr {
                static const bool is_vectorizable = std::remove_reference<Arg>::type::is_vectorizable
                                                    and types::is_vector_op<Op>::value;
                static const bool is_strided = std::remove_reference<Arg>::type::is_strided;
                typedef const_uexpr_iterator<Op, typename std::remove_reference<Arg>::type::const_iterator> const_iterator;
                static constexpr size_t value = std::remove_reference<Arg>::type::value;
                typedef decltype(Op()(std::declval<typename std::remove_reference<Arg>::type::value_type>())) value_type;
                typedef decltype(Op()(std::declval<typename std::remove_reference<Arg>::type::dtype>())) dtype;

                Arg arg;
                long const *shape;

                numpy_uexpr() {}
                numpy_uexpr(numpy_uexpr const &) =default;
                numpy_uexpr(numpy_uexpr &&) = default;

                numpy_uexpr(Arg const &arg) : arg(arg), shape(arg.shape) {}

                const_iterator begin() const { return const_iterator(arg.begin()); }
                const_iterator end() const { return const_iterator(arg.end()); }

                auto fast(long i) const -> decltype(Op()(arg.fast(i))) {
                    return Op()(arg.fast(i));
                }
#ifdef USE_BOOST_SIMD
                template<class I> // template to prevent automatic instantiation
                auto load(I i) const -> decltype(Op()(arg.load(i))) {
                  return Op()(arg.load(i));
                }
#endif
                auto operator[](long i) const -> decltype(this->fast(i)) {
                    if(i<0) i += *shape;
                    return fast(i);
                }
                template<class F>
                    typename std::enable_if<is_numexpr_arg<F>::value, numpy_fexpr<numpy_uexpr, F>>::type
                    operator[](F const& filter) const {
                        return numpy_fexpr<numpy_uexpr, F>(*this, filter);
                    }

                long size() const { return arg.size(); }
            };
    }

    template<class Op, class Arg>
        struct assignable<types::numpy_uexpr<Op, Arg>>
        {
            typedef typename types::numpy_expr_to_ndarray<types::numpy_uexpr<Op, Arg>>::type type;
        };
    template<class Op, class Arg>
        struct lazy<types::numpy_uexpr<Op,Arg>>
        {
            typedef types::numpy_uexpr<Op,typename lazy<Arg>::type> type;
        };
}

/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"
template<class Arg, class Op, class K>
struct __combined<pythonic::types::numpy_uexpr<Op, Arg>, indexable<K>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg> type;
};

template<class Arg, class Op, class K>
struct __combined<indexable<K>, pythonic::types::numpy_uexpr<Op, Arg>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg> type;
};

template<class Arg, class Op, class K, class V>
struct __combined<pythonic::types::numpy_uexpr<Op, Arg>, indexable_container<K,V>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg> type;
};

template<class Arg, class Op, class K, class V>
struct __combined<indexable_container<K,V>, pythonic::types::numpy_uexpr<Op, Arg>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg> type;
};

template<class Arg, class Op, class K>
struct __combined<container<K>, pythonic::types::numpy_uexpr<Op, Arg>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg> type;
};

template<class Arg, class Op, class K>
struct __combined<pythonic::types::numpy_uexpr<Op, Arg>, container<K>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg> type;
};

template<class Arg, class Op, class Op1, class Arg1>
struct __combined<pythonic::types::numpy_uexpr<Op, Arg>, pythonic::types::numpy_uexpr<Op1, Arg1>> {
    typedef typename pythonic::types::numpy_expr_to_ndarray<pythonic::types::numpy_uexpr<Op, Arg>>::type type;
};
/*}*/

#endif


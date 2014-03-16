#ifndef PYTHONIC_TYPES_NUMPY_EXPR_HPP
#define PYTHONIC_TYPES_NUMPY_EXPR_HPP

namespace pythonic {

    namespace types {
        template<class Expr>
            struct is_numexpr_arg;

        /* utility to pick the right shape */
        template<class U, class V, size_t N>
            typename std::enable_if<U::value!=0 and U::value == N, array<long, U::value>>::type select_shape(U const& u, V const&, utils::int_<N> ) {
                return u.shape;
            }
        template<class U, class V, size_t N>
            typename std::enable_if<U::value!=0 and U::value != N, array<long, V::value>>::type select_shape(U const& , V const& v, utils::int_<N> ) {
                return v.shape;
            }
        template<class U, class V, size_t N>
            typename std::enable_if<U::value==0 and V::value!=0, array<long, V::value>>::type select_shape(U const& , V const&v, utils::int_<N> ) {
                return v.shape;
            }
        template<class U, class V>
            array<long, 0> select_shape(U const& u, V const&, utils::int_<0> ) {
                return array<long, 0>();
            }

        /* Expression template for numpy expressions - binary operators
         */
        template<class Op, class Arg0, class Arg1>
            struct numpy_expr {
                typedef const_nditerator<numpy_expr<Op, Arg0, Arg1>> iterator;
                static constexpr size_t value = std::remove_reference<Arg0>::type::value>std::remove_reference<Arg1>::type::value?std::remove_reference<Arg0>::type::value: std::remove_reference<Arg1>::type::value;
                typedef decltype(Op()(std::declval<typename std::remove_reference<Arg0>::type::value_type>(), std::declval<typename std::remove_reference<Arg1>::type::value_type>())) value_type;
                typedef decltype(Op()(std::declval<typename std::remove_reference<Arg0>::type::dtype>(), std::declval<typename std::remove_reference<Arg1>::type::dtype>())) dtype;

                typename std::remove_reference<Arg0>::type arg0;
                typename std::remove_reference<Arg1>::type arg1;
                array<long, value> shape;

                numpy_expr() {}
                numpy_expr(numpy_expr const&) = default;
                numpy_expr(numpy_expr &&) = default;

                numpy_expr(Arg0 const &arg0, Arg1 const &arg1) : arg0(arg0), arg1(arg1), shape(select_shape(arg0,arg1, utils::int_<value>())) {}

                iterator begin() const { return iterator(*this, 0); }
                iterator end() const { return iterator(*this, shape[0]); }

                auto fast(long i) const -> decltype(Op()(arg0[i], arg1[i])) {
                    return Op()(arg0[i], arg1[i]);
                }
                auto operator[](long i) const -> decltype(this->fast(i)) {
                    if(i<0) i += shape[0];
                    return fast(i);
                }

                template<class F>
                    typename std::enable_if<is_numexpr_arg<F>::value, numpy_fexpr<numpy_expr, F>>::type
                    operator[](F const& filter) const {
                        return numpy_fexpr<numpy_expr, F>(*this, filter);
                    }

                long size() const { return std::max(arg0.size(), arg1.size()); }
            };

    }

}
#endif


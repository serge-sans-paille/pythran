#ifndef PYTHONIC_TYPES_NUMPY_UEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_UEXPR_HPP

namespace pythonic {

    namespace types {
        /* Expression template for numpy expressions - unary operators
         */
        template<class Op, class Arg>
            struct numpy_uexpr {
                typedef const_nditerator<numpy_uexpr<Op, Arg>> iterator;
                static constexpr size_t value = std::remove_reference<Arg>::type::value;
                typedef decltype(Op()(std::declval<typename std::remove_reference<Arg>::type::value_type>())) value_type;
                typedef decltype(Op()(std::declval<typename std::remove_reference<Arg>::type::dtype>())) dtype;

                Arg arg;
                array<long, value> shape;

                numpy_uexpr() {}
                numpy_uexpr(numpy_uexpr const &) =default;
                numpy_uexpr(numpy_uexpr &&) = default;

                numpy_uexpr(Arg const &arg) : arg(arg), shape(arg.shape) {}

                iterator begin() const { return iterator(*this, 0); }
                iterator end() const { return iterator(*this, shape[0]); }

                auto fast(long i) const -> decltype(Op()(arg.fast(i))) {
                    return Op()(arg.fast(i));
                }
                auto operator[](long i) const -> decltype(this->fast(i)) {
                    if(i<0) i += shape[0];
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

#endif


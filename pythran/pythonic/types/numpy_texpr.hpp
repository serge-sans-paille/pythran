#ifndef PYTHONIC_TYPES_NUMPY_TEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_TEXPR_HPP
namespace pythonic {

    namespace types {
        template<class Arg, class... S>
            struct numpy_gexpr;
        template<class Arg, class F>
            struct numpy_fexpr;

        /* expression template for Transposed matrix */
        template<class Arg>
            struct numpy_texpr;

        // only implemented for N = 2
        template<class T>
            // wrapper arounf numpy expression for 2D transposed amtrix using gexpr representation
            // >>> b = a.transpose
            // >>> b[i] == a[:,i]
            // True
            //
            // for N = 2
            struct numpy_texpr<ndarray<T, 2>> {
                typedef ndarray<T, 2> Arg;

                typedef nditerator<numpy_texpr<Arg>> iterator;
                typedef const_nditerator<numpy_texpr<Arg>> const_iterator;

                static constexpr size_t value = Arg::value;
                typedef numpy_gexpr<Arg, contiguous_slice, long> value_type;
                typedef T dtype;

                Arg arg;
                array<long, 2> shape;

                numpy_texpr() {}
                numpy_texpr(numpy_texpr const&) = default;
                numpy_texpr(numpy_texpr &&) = default;

                numpy_texpr(Arg const& arg) : arg(arg), shape{{arg.shape[1], arg.shape[0]}}
                {
                }
                const_iterator begin() const { return const_iterator(*this, 0); }
                const_iterator end() const { return const_iterator(*this, shape[0]); }

                iterator begin() { return iterator(*this, 0); }
                iterator end() { return iterator(*this, shape[0]); }

                auto fast(long i) const
                    -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), i))
                {
                    return arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), i);
                }

                auto fast(long i)
                    -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), i))
                {
                    return arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), i);
                }

                auto operator[](long i) const -> decltype(this->fast(i)) {
                    if(i<0) i += shape[0];
                    return fast(i);
                }
                auto operator[](long i) -> decltype(this->fast(i)) {
                    if(i<0) i += shape[0];
                    return fast(i);
                }
                auto operator()(long i) const -> decltype((*this)[i]) {
                    return (*this)[i];
                }
                auto operator()(long i) -> decltype((*this)[i]) {
                    return (*this)[i];
                }

                long size() const {
                    return arg.size();
                }

            };

    }

    template<class Arg>
        struct assignable<types::numpy_texpr<Arg>>
        {
            typedef typename types::numpy_expr_to_ndarray<types::numpy_texpr<Arg>>::type type;
        };
    template<class Arg>
        struct lazy<types::numpy_texpr<Arg>>
        {
            typedef types::numpy_texpr<typename lazy<Arg>::type> type;
        };

}

#endif


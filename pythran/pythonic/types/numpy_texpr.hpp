#ifndef PYTHONIC_TYPES_NUMPY_TEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_TEXPR_HPP

#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace types {

        template<class Arg, class... S>
            struct numpy_gexpr;
        template<class Arg, class F>
            struct numpy_fexpr;

        /* expression template for Transposed matrix */
        template<class Arg>
            struct numpy_texpr;

        // wrapper around numpy expression for 2D transposed matrix using gexpr representation
        // >>> b = a.transpose
        // >>> b[i] == a[:,i]
        // True
        //
        // for N = 2
        template<class E>
            struct numpy_texpr_2 {
                static_assert(E::value == 2, "texpr only implemented for matrices");
                static const bool is_vectorizable = false;
                static const bool is_strided = true;
                typedef E Arg;

                typedef nditerator<numpy_texpr_2<Arg>> iterator;
                typedef const_nditerator<numpy_texpr_2<Arg>> const_iterator;

                static constexpr size_t value = Arg::value;
                typedef numpy_gexpr<Arg, contiguous_slice, long> value_type;
                typedef typename E::dtype dtype;

                Arg arg;
                array<long, 2> _shape;
                array<long, 2> const& shape() const { return _shape; }

                numpy_texpr_2() {}
                numpy_texpr_2(numpy_texpr_2 const&) = default;
                numpy_texpr_2(numpy_texpr_2 &&) = default;

                numpy_texpr_2(Arg const& arg) : arg(arg), _shape{{arg.shape()[1], arg.shape()[0]}}
                {
                }
                const_iterator begin() const { return const_iterator(*this, 0); }
                const_iterator end() const { return const_iterator(*this, _shape[0]); }

                iterator begin() { return iterator(*this, 0); }
                iterator end() { return iterator(*this, _shape[0]); }

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
#ifdef USE_BOOST_SIMD
                template<class I>
                void load(I) const {
                  static_assert(I::this_should_never_happen, "this is *not* vectorizable");
                }
#endif

                auto operator[](long i) const -> decltype(this->fast(i)) {
                    if(i<0) i += _shape[0];
                    return fast(i);
                }
                auto operator[](long i) -> decltype(this->fast(i)) {
                    if(i<0) i += _shape[0];
                    return fast(i);
                }
                auto operator()(long i) const -> decltype((*this)[i]) {
                    return (*this)[i];
                }
                auto operator()(long i) -> decltype((*this)[i]) {
                    return (*this)[i];
                }
                auto operator[](array<long, value> const& indices) -> decltype(arg[array<long, 2>{{indices[1], indices[0]}}]) {
                  return arg[array<long, 2>{{indices[1], indices[0]}}];
                }
                auto operator[](array<long, value> const& indices) const -> decltype(arg[array<long, 2>{{indices[1], indices[0]}}]) {
                  return arg[array<long, 2>{{indices[1], indices[0]}}];
                }

                auto operator()(contiguous_slice const& s0) const
                -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), s0))
                {
                  return arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), s0);
                }
                auto operator()(contiguous_slice const& s0)
                -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), s0))
                {
                  return arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), s0);
                }
                auto operator()(slice const& s0) const
                -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), s0))
                {
                  return arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), s0);
                }
                auto operator()(slice const& s0)
                -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), s0))
                {
                  return arg(contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None), s0);
                }
                auto operator[](contiguous_slice const& s0) const
                -> decltype(this->operator()(s0))
                {
                  return (*this)(s0);
                }
                auto operator[](contiguous_slice const& s0)
                -> decltype(this->operator()(s0))
                {
                  return (*this)(s0);
                }
                auto operator[](slice const& s0) const
                -> decltype(this->operator()(s0))
                {
                  return (*this)(s0);
                }
                auto operator[](slice const& s0)
                -> decltype(this->operator()(s0))
                {
                  return (*this)(s0);
                }

                template<class S, int... I>
                  auto _reverse_index(S const& indices, utils::seq<I...>) const
                  -> decltype(this->arg(std::get<I>(indices)...))
                  {
                    return arg(std::get<I>(indices)...);
                  }
                template<class S0, class... S>
                auto operator()(S0 const& s0, S const&... s) const
                -> decltype(this->_reverse_index(std::tuple<S0 const&, S const&...>{s0, s...}, typename utils::rgens<1 + sizeof...(S)>::type{}))
                {
                  return _reverse_index(std::tuple<S0 const&, S const&...>{s0, s...}, typename utils::rgens<1 + sizeof...(S)>::type{});
                }

                long flat_size() const {
                    return arg.flat_size();
                }
                intptr_t id() const {
                  return arg.id();
                }
                ndarray<dtype, value> copy() const { return *this; }


            };

        // only implemented for N = 2
        template<class T>
            struct numpy_texpr<ndarray<T, 2>> : numpy_texpr_2<ndarray<T, 2>>{
                numpy_texpr() {}
                numpy_texpr(numpy_texpr const&) = default;
                numpy_texpr(numpy_texpr &&) = default;

                numpy_texpr(ndarray<T, 2> const& arg) : numpy_texpr_2<ndarray<T, 2>> {arg}
                {
                }
            };
        template<class E, class... S>
            struct numpy_texpr<numpy_gexpr<E, S...>> : numpy_texpr_2<numpy_gexpr<E, S...>>{
                numpy_texpr() {}
                numpy_texpr(numpy_texpr const&) = default;
                numpy_texpr(numpy_texpr &&) = default;

                numpy_texpr(numpy_gexpr<E, S...> const& arg) : numpy_texpr_2<numpy_gexpr<E, S...>> {arg}
                {
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
/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"
template<class E, class K>
struct __combined<pythonic::types::numpy_texpr<E>, K> {
    typedef pythonic::types::numpy_texpr<E> type;
};

#endif


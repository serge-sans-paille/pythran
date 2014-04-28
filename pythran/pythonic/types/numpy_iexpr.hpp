#ifndef PYTHONIC_TYPES_NUMPY_IEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_IEXPR_HPP

#include "pythonic/types/nditerator.hpp"
#include "pythonic/types/tuple.hpp"

#include <numeric>

namespace pythonic {

    namespace types {

        template<class Arg, class... S>
            struct numpy_gexpr;
        template<class Arg, class F>
            struct numpy_fexpr;

        /* Expression template for numpy expressions - indexing
         */
        template<size_t N>
            struct numpy_iexpr_helper;

        template<class Arg>
            struct numpy_iexpr {
                // wrapper around another numpy expression to skip first dimension using a given value.
                static constexpr size_t value = std::remove_reference<Arg>::type::value - 1;
                typedef typename std::remove_reference<Arg>::type::dtype dtype;
                typedef typename std::remove_reference<decltype(numpy_iexpr_helper<value>::get(std::declval<numpy_iexpr>(), 0L))>::type value_type;

                typedef nditerator<numpy_iexpr> iterator;
                typedef const_nditerator<numpy_iexpr> const_iterator;

                Arg arg;
                dtype* buffer;
                array<long, value> shape;

                numpy_iexpr() {}
                numpy_iexpr(numpy_iexpr const &) = default;
                numpy_iexpr(numpy_iexpr&&) = default;

                template<class Argp> // not using the default one, to make it possible to accept reference and non reference version of Argp
                    numpy_iexpr(numpy_iexpr<Argp> const & other) :
                        arg(other.arg),
                        buffer(other.buffer),
                        shape(other.shape)
                {
                }

                numpy_iexpr(Arg const &arg, long index) : arg(arg), buffer(arg.buffer)
                {
                    auto siter = shape.begin();
                    //accumulate the shape to jump to index position. Not done with std::accumulate
                    //as we want to copy the shape at the same time.
                    for(auto iter = arg.shape.begin() + 1, end = arg.shape.end(); iter != end; ++iter, ++siter)
                        index *= *siter = *iter;
                    buffer += index;
                }

                template<class E>
                numpy_iexpr& operator=(E const& expr) {
                    return utils::broadcast_copy(*this, expr, utils::int_<value - utils::dim_of<E>::value>());
                }
                numpy_iexpr& operator=(numpy_iexpr const& expr) {
                    return utils::broadcast_copy(*this, expr, utils::int_<value - utils::dim_of<numpy_iexpr>::value>());
                }
                template<class E>
                numpy_iexpr& operator+=(E const& expr) {
                    return (*this) = (*this) + expr;
                }
                numpy_iexpr& operator+=(numpy_iexpr const& expr) {
                    return (*this) = (*this) + expr;
                }
                template<class E>
                numpy_iexpr& operator-=(E const& expr) {
                    return (*this) = (*this) - expr;
                }
                numpy_iexpr& operator-=(numpy_iexpr const& expr) {
                    return (*this) = (*this) - expr;
                }
                template<class E>
                numpy_iexpr& operator*=(E const& expr) {
                    return (*this) = (*this) * expr;
                }
                numpy_iexpr& operator*=(numpy_iexpr const& expr) {
                    return (*this) = (*this) * expr;
                }
                template<class E>
                numpy_iexpr& operator/=(E const& expr) {
                    return (*this) = (*this) / expr;
                }
                numpy_iexpr& operator/=(numpy_iexpr const& expr) {
                    return (*this) = (*this) / expr;
                }

                const_iterator begin() const { return const_iterator(*this, 0); }
                const_iterator end() const { return const_iterator(*this, shape[0]); }

                iterator begin() { return iterator(*this, 0); }
                iterator end() { return iterator(*this, shape[0]); }

                dtype const * fbegin() const { return buffer; }
                dtype const * fend() const { return buffer + size(); }

                dtype * fbegin() { return buffer; }
                dtype const * fend() { return buffer + size(); }

                auto fast(long i) const -> decltype(numpy_iexpr_helper<value>::get(*this, i)) {
                    return numpy_iexpr_helper<value>::get(*this, i);
                }
                auto fast(long i) -> decltype(numpy_iexpr_helper<value>::get(*this, i)) {
                    return numpy_iexpr_helper<value>::get(*this, i);
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
                numpy_gexpr<numpy_iexpr, slice> operator()(slice const& s0) const
                {
                    return numpy_gexpr<numpy_iexpr, slice>(*this, s0);
                }
                numpy_gexpr<numpy_iexpr, slice> operator[](slice const& s0) const
                {
                    return numpy_gexpr<numpy_iexpr, slice>(*this, s0);
                }
                numpy_gexpr<numpy_iexpr, contiguous_slice> operator()(contiguous_slice const& s0) const
                {
                    return numpy_gexpr<numpy_iexpr, contiguous_slice>(*this, s0);
                }
                numpy_gexpr<numpy_iexpr, contiguous_slice> operator[](contiguous_slice const& s0) const
                {
                    return numpy_gexpr<numpy_iexpr, contiguous_slice>(*this, s0);
                }
                template<class ...S>
                    numpy_gexpr<numpy_iexpr, slice, S...> operator()(slice const& s0, S const&... s) const
                    {
                        return numpy_gexpr<numpy_iexpr, slice, S...>(*this, s0, s...);
                    }
                template<class ...S>
                    numpy_gexpr<numpy_iexpr, contiguous_slice, S...> operator()(contiguous_slice const& s0, S const&... s) const
                    {
                        return numpy_gexpr<numpy_iexpr, contiguous_slice, S...>(*this, s0, s...);
                    }
                template<class ...S>
                    auto operator()(long s0, S const&... s) const -> decltype( (*this)[s0](s...))
                    {
                        return (*this)[s0](s...);
                    }
                template<class F>
                    typename std::enable_if<is_numexpr_arg<F>::value, numpy_fexpr<numpy_iexpr, F>>::type
                    operator[](F const& filter) const {
                        return numpy_fexpr<numpy_iexpr, F>(*this, filter);
                    }

                long size() const { return /*arg.size()*/ std::accumulate(shape.begin() + 1, shape.end(), *shape.begin(), std::multiplies<long>()); }
            };

        template <size_t N>
            struct numpy_iexpr_helper {
                template<class E>
                static numpy_iexpr<E> get(E && e, long i) { return numpy_iexpr<E>(e, i);}
            };

        template <>
            struct numpy_iexpr_helper<1> {
                template<class E>
                static typename E::dtype get(E const & e, long i)
                {
                    return e.buffer[i];
                }
                template<class E>
                static typename E::dtype & get(E & e, long i)
                {
                    return e.buffer[i];
                }
            };

    }


    template<class Arg>
        struct assignable<types::numpy_iexpr<Arg>>
        {
            typedef types::numpy_iexpr<typename assignable<Arg>::type> type;
        };
    template<class Arg>
        struct lazy<types::numpy_iexpr<Arg>>
        {
            typedef types::numpy_iexpr<typename lazy<Arg>::type> type;
        };
    template<class Arg>
        struct lazy<types::numpy_iexpr<Arg const &>>
        {
            typedef types::numpy_iexpr<typename lazy<Arg>::type const &> type;
        };

}

#endif

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
        template<class T, size_t N>
            struct numpy_iexpr_helper;

        template<class Arg>
            struct numpy_iexpr {
                // wrapper around another numpy expression to skip first dimension using a given value.
                static constexpr size_t value = std::remove_reference<Arg>::type::value - 1;
                typedef typename std::remove_reference<Arg>::type::dtype dtype;
                typedef typename std::remove_reference<decltype(numpy_iexpr_helper<numpy_iexpr, value>::get(std::declval<numpy_iexpr>(), 0L))>::type value_type;

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

                numpy_iexpr(Arg const & arg, long index) : arg(arg), buffer(arg.buffer)
                {
                    buffer += buffer_offset(index, utils::int_<value>());
                }
                // force the move. Using universal reference here does not work (because of reference collapsing ?)
                numpy_iexpr(typename std::remove_reference<Arg>::type &&arg, long index) : arg(std::move(arg)), buffer(arg.buffer)
                {
                    buffer += buffer_offset(index, utils::int_<value>());
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

                /* There are three kind of indexing operator: fast(long), [long] and (long):
                 * - fast does not perform automatic bound wrapping
                 * - [] performs automatic bound wrapping, hen forwards to fast
                 * - () is an alias to [] and directly forwards to []
                 *
                 * For each indexing operator, we have three variant: &, const& and &&:
                 * - & means the numpy_iexpr has been bound to a non-const value, as in ``b=a[i] ; print b[j]``
                 *   in that case the return type if the dim of a is 2 is a reference, to allow ``b[j] = 1``
                 * - const & means the numpy_iexpr has been bound to a const value, as in ``np.copy(a[i])``
                 *   in that case the return type if the dim of a is 2 is a value (or const ref)
                 * - && means the numpy_iexpr is a r-value, which happens a lot, as in ``a[i][j]``
                 *   in that case the return type if the dim of a is 2 is a reference.
                 *   It is a bit weird because we return a refrence from a rvalue, but the reference is bound to
                 *   the buffer of ``a`` that is not temp.
                 */
                auto fast(long i) const &-> decltype(numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i)) {
                    return numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i);
                }
                auto fast(long i) &-> decltype(numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i)) {
                    return numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i);
                }
                auto fast(long i) &&-> decltype(numpy_iexpr_helper<numpy_iexpr, value>::get(std::move(*this), i)) {
                    return numpy_iexpr_helper<numpy_iexpr, value>::get(std::move(*this), i);
                }
                auto operator[](long i) const &-> decltype(this->fast(i)) {
                    if(i<0) i += shape[0];
                    return fast(i);
                }
                auto operator[](long i) &-> decltype(this->fast(i)) {
                    if(i<0) i += shape[0];
                    return fast(i);
                }
                auto operator[](long i) && -> decltype(std::move(*this).fast(i)) {
                    if(i<0) i += shape[0];
                    return std::move(*this).fast(i);
                }
                auto operator()(long i) const &-> decltype((*this)[i]) {
                    return (*this)[i];
                }
                auto operator()(long i) &-> decltype((*this)[i]) {
                    return (*this)[i];
                }
                auto operator()(long i) &&-> decltype(std::move(*this)[i]) {
                    return std::move(*this)[i];
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
                    auto operator()(long s0, S const&... s) const -> decltype(std::declval<numpy_iexpr<numpy_iexpr>>()(s...))
                    {
                        return (*this)[s0](s...);
                    }
                template<class F>
                    typename std::enable_if<is_numexpr_arg<F>::value, numpy_fexpr<numpy_iexpr, F>>::type
                    operator[](F const& filter) const {
                        return numpy_fexpr<numpy_iexpr, F>(*this, filter);
                    }

                dtype const &operator[](array<long, value> const& indices) const
                {
                    size_t offset = indices[value-1];
                    long mult = shape[value-1];
                    for(size_t i = value - 2; i > 0; --i) {
                        offset +=  indices[i] * mult;
                        mult *= shape[i];
                    }
                    return buffer[offset + indices[0] * mult];
                }
                dtype& operator[](array<long, value> const& indices)
                {
                    return const_cast<dtype&>(const_cast<numpy_iexpr const&>(*this)[indices]);
                }

                long size() const { return /*arg.size()*/ std::accumulate(shape.begin() + 1, shape.end(), *shape.begin(), std::multiplies<long>()); }

                private:

                /* compute the buffer offset, returning the offset between the
                 * first element of the iexpr and the start of the buffer.
                 * This used to be a plain loop, but g++ fails to unroll it, while it unrolls it with the template version...
                 */
                long buffer_offset(long index, utils::int_<0>) { return index;
                }

                template<size_t N>
                long buffer_offset(long index, utils::int_<N>) {
                    shape[value - N] = arg.shape[value - N + 1];
                    return buffer_offset(index * arg.shape[value - N + 1], utils::int_<N - 1>());
                }

            };

        // Indexing an numpy_iexpr that has a dimension greater than one yields a new numpy_iexpr
        template <class T, size_t N>
            struct numpy_iexpr_helper {
                static numpy_iexpr<T> get(T const& e, long i) {
                    return numpy_iexpr<T>(e, i);
                }
            };

        // Indexing an iexpr that has a dimension of one yields a qualified scalar. The qualifier is either:
        // - a reference if the numpy_iexpr is a ref itself, as in ``b = a[i] ; b[i] = 1``
        // - a reference if the numpy_iexpr is a r-value, as in ``a[i][j] = 1``
        // - a value if the numpy_iexpr is a const ref, as in ``b = a[i] ; c = b[i]``
        template <class T>
            struct numpy_iexpr_helper<T, 1> {
                static typename T::dtype get(T const & e, long i)
                {
                    return e.buffer[i];
                }
                static typename T::dtype & get(T && e, long i)
                {
                    return e.buffer[i];
                }
                static typename T::dtype & get(T & e, long i)
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
/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"
template<class E, class K>
struct __combined<pythonic::types::numpy_iexpr<E>, K> {
    typedef pythonic::types::numpy_iexpr<E> type;
};

#endif

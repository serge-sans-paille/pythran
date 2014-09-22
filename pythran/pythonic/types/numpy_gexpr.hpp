#ifndef PYTHONIC_TYPES_NUMPY_GEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_GEXPR_HPP

namespace pythonic {

    namespace types {
        /* manually unrolled copy function
         */
        template <size_t I> struct flat_copy;
        template<> struct flat_copy<0> { void operator()(long*, long const*){}};
        template<size_t I> struct flat_copy { void operator()(long* to, long const* from){ to[I-1] = from[I-1] ; flat_copy<I-1>()(to, from); }};

        /* Meta-Function to count the number of slices in a type list
         */
        template<class... Types>
            struct count_long;
        template<>
            struct count_long<long> {
                static constexpr size_t value = 1;
            };
        template<>
            struct count_long<slice> {
                static constexpr size_t value = 0;
            };
        template<>
            struct count_long<contiguous_slice> {
                static constexpr size_t value = 0;
            };

        template<class T, class... Types>
            struct count_long<T, Types...> {
                static constexpr size_t value = count_long<T>::value + count_long<Types...>::value;
            };
        template<>
            struct count_long<> {
                static constexpr size_t value = 0;
            };

        /* helper to get the type of the nth element of an array
         */
        template<class T, size_t N>
            struct nth_value_type {
                typedef typename nth_value_type<typename T::value_type, N-1>::type type;
            };

        template<class T>
            struct nth_value_type<T, 0> {
                typedef T type;
            };
        /* helper that yields true if the first slice of a pack is a contiguous slice
         */
        template<class... S>
            struct is_contiguous {
                static const bool value = false;
            };
        template<class... S>
            struct is_contiguous<contiguous_slice, S...> {
                static const bool value = true;
            };


        template <class Arg, class... S>
            struct numpy_gexpr_helper;

        /* Expression template for numpy expressions - extended slicing operators
         */
        template<class Arg, class... S>
            struct numpy_gexpr {
                // numpy_gexpr is a wrapper for extended sliced array around a numpy expression.
                // It contains compacted sorted slices value in lower, step and upper is the same as shape.
                // indices for long index are store in the indices array.
                // position for slice and long value in the extended slice can be found through the S... template
                // and compacted values as we know that first S is a slice.

                typedef typename std::remove_reference<Arg>::type::dtype dtype;
                static constexpr size_t value = std::remove_reference<Arg>::type::value - count_long<S...>::value;

                // It is not possible to vectorize everything. We only vectorize if the last dimension is contiguous, which happens if
                // 1. Arg is an ndarray (this is too strict)
                // 2. the size of the gexpr is lower than the dim of arg, or it's the same, but the last slice is contiguous
                static const bool is_vectorizable =
                  std::is_same<ndarray<typename std::remove_reference<Arg>::type::dtype, std::remove_reference<Arg>::type::value>,
                               typename std::remove_cv<typename std::remove_reference<Arg>::type>::type
                              >::value and
                  (
                    sizeof...(S) < std::remove_reference<Arg>::type::value or
                    std::is_same<contiguous_slice, typename std::tuple_element<sizeof...(S) - 1, std::tuple<S...>>::type>::value
                  );
                static const bool is_strided =
                    std::remove_reference<Arg>::type::is_strided or
                    (((sizeof...(S) - count_long<S...>::value) == value)
                    and  not std::is_same<contiguous_slice, typename std::tuple_element<sizeof...(S) - 1, std::tuple<S...>>::type>::value);

                typedef typename std::remove_reference<decltype(numpy_gexpr_helper<Arg, S...>::get(std::declval<numpy_gexpr>(), 0L))>::type value_type;

                typedef typename std::conditional<
                  is_strided or value != 1,
                  nditerator<numpy_gexpr>,
                  dtype*
                >::type iterator;
                typedef typename std::conditional<
                  is_strided or value != 1,
                  const_nditerator<numpy_gexpr>,
                  dtype const*
                >::type const_iterator;

                Arg arg;
                dtype* buffer;
                array<long, value> shape;
                array<long, value> lower;
                array<long, value> step;
                array<long, std::remove_reference<Arg>::type::value - value> indices;

                numpy_gexpr() {}
                numpy_gexpr(numpy_gexpr const & ) = default;
                numpy_gexpr(numpy_gexpr && ) = default;

                template<class Argp> // not using the default one, to make it possible to accept reference and non reference version of Argp
                numpy_gexpr(numpy_gexpr<Argp, S...> const& other) :
                    arg(other.arg),
                    buffer(other.buffer),
                    shape(other.shape),
                    lower(other.lower),
                    step(other.step),
                    indices(other.indices)
                {
                }

                template<size_t J>
                void init_shape(std::tuple<S const &...> const& values, contiguous_slice const& cs, utils::int_<1>, utils::int_<J>) {
                    contiguous_normalized_slice cns = cs.normalize(arg.shape[sizeof...(S) - 1]);
                    lower[J] = cns.lower;
                    step[J] = cns.step;
                    shape[J] = cns.size();
                }

                template<size_t I, size_t J>
                    void init_shape(std::tuple<S const&...> const & values, contiguous_slice const& cs, utils::int_<I>, utils::int_<J>) {
                        contiguous_normalized_slice cns = cs.normalize(arg.shape[sizeof...(S) - I]);
                        lower[J] = cns.lower;
                        step[J] = cns.step;
                        shape[J] = cns.size();
                        init_shape(values, std::get<sizeof...(S) - I + 1>(values), utils::int_<I - 1>(), utils::int_<J + 1>());
                    }
                template<size_t J>
                void init_shape(std::tuple<S const &...> const& values, slice const& cs, utils::int_<1>, utils::int_<J>) {
                    normalized_slice cns = cs.normalize(arg.shape[sizeof...(S) - 1]);
                    lower[J] = cns.lower;
                    step[J] = cns.step;
                    shape[J] = cns.size();
                }

                template<size_t I, size_t J>
                    void init_shape(std::tuple<S const&...> const & values, slice const& cs, utils::int_<I>, utils::int_<J>) {
                        normalized_slice cns = cs.normalize(arg.shape[sizeof...(S) - I]);
                        lower[J] = cns.lower;
                        step[J] = cns.step;
                        shape[J] = cns.size();
                        init_shape(values, std::get<sizeof...(S) - I + 1>(values), utils::int_<I - 1>(), utils::int_<J + 1>());
                    }

                template<size_t J>
                void init_shape(std::tuple<S const &...> const& values, long cs, utils::int_<1>, utils::int_<J>) {
                    if(cs < 0) cs += arg.shape[sizeof...(S) - 1];
                    indices[sizeof...(S) - 1 - J] = cs;
                }

                template<size_t I, size_t J>
                    void init_shape(std::tuple<S const&...> const & values, long cs, utils::int_<I>, utils::int_<J>) {
                        if(cs < 0) cs += arg.shape[sizeof...(S) - I];
                        indices[sizeof...(S) - I - J] = cs;
                        init_shape(values, std::get<sizeof...(S) - I + 1>(values), utils::int_<I - 1>(), utils::int_<J>());
                    }

                template<class E>
                    void fix_shape(E const&) {
                    }
                template<class Argp, class... Sp>
                    void fix_shape(numpy_gexpr<Argp, Sp...> const& arg) {
                        for(size_t i=0; i< value; ++i)
                        {
                            lower[i] += arg.lower[i];
                            step[i] *= arg.step[i];
                        }
                    }

                // When we create a new numpy_gexpr, we deduce step, lower and shape from slices
                // and indices from long value.
                // Also, last shape information are set from origin array like in :
                // >>> a = numpy.arange(2*3*4).reshape(2,3,4)
                // >>> a[:, 1]
                // the last dimension (4) is missing from slice information
                // Finally, if origin expression was already sliced, lower bound and step have to 
                // be increased
                numpy_gexpr(Arg const &arg, S const &...s) : arg(arg), buffer(arg.buffer) {
                    std::tuple<S const&...> values(s...);
                    init_shape(values, std::get<0>(values), utils::int_<sizeof...(S)>(), utils::int_<0>());
                    for(size_t i = sizeof...(S) - count_long<S...>::value; i < value; ++i)
                        shape[i] = arg.shape[i + count_long<S...>::value];
                    fix_shape(arg); // This is specialized for numpy_gexpr only
                }


                template<class Argp, class... Sp>
                numpy_gexpr(numpy_gexpr<Argp, Sp...> const &expr, Arg &&arg) : arg(std::forward<Arg>(arg)), buffer(arg.buffer) {
                  flat_copy<value>()(&shape[0], &expr.shape[1]);
                  flat_copy<value>()(&lower[0], &expr.lower[1]);
                  flat_copy<value>()(&step[0], &expr.step[1]);
                  flat_copy<std::remove_reference<Arg>::type::value - value>()(&indices[0], &expr.indices[0]);
                }

                template<class G>
                numpy_gexpr(G const &expr, Arg &&arg) : arg(std::forward<Arg>(arg)), buffer(arg.buffer) {
                  flat_copy<value>()(&shape[0], &expr.shape[1]);
                  flat_copy<value>()(&lower[0], &expr.lower[1]);
                  flat_copy<value>()(&step[0], &expr.step[1]);
                }

                template<class E>
                numpy_gexpr& operator=(E const& expr) {
                    return utils::broadcast_copy<numpy_gexpr&, E, value, value - utils::dim_of<E>::value, false/*NIY*/>(*this, expr);
                }
                numpy_gexpr& operator=(numpy_gexpr const& expr) {
                    return utils::broadcast_copy<numpy_gexpr&, numpy_gexpr, value, value - utils::dim_of<numpy_gexpr>::value, false/*NIY*/>(*this, expr);
                }
                template<class E>
                numpy_gexpr& operator+=(E const& expr) {
                    return (*this) = (*this) + expr;
                }
                numpy_gexpr& operator+=(numpy_gexpr const& expr) {
                    return (*this) = (*this) + expr;
                }
                template<class E>
                numpy_gexpr& operator-=(E const& expr) {
                    return (*this) = (*this) - expr;
                }
                numpy_gexpr& operator-=(numpy_gexpr const& expr) {
                    return (*this) = (*this) - expr;
                }
                template<class E>
                numpy_gexpr& operator*=(E const& expr) {
                    return (*this) = (*this) * expr;
                }
                numpy_gexpr& operator*=(numpy_gexpr const& expr) {
                    return (*this) = (*this) * expr;
                }
                template<class E>
                numpy_gexpr& operator/=(E const& expr) {
                    return (*this) = (*this) / expr;
                }
                numpy_gexpr& operator/=(numpy_gexpr const& expr) {
                    return (*this) = (*this) / expr;
                }

                const_iterator begin() const {
                  return make_const_nditerator<is_strided or value != 1>()(*this, (is_strided or value != 1) ?0 : lower[0]); }
                const_iterator end() const { return make_const_nditerator<is_strided or value != 1>()(*this, ((is_strided or value != 1) ?0 : lower[0]) + shape[0]); }

                iterator begin() { return make_nditerator<is_strided or value != 1>()(*this, (is_strided or value != 1) ?0 : lower[0]); }
                iterator end() { return make_nditerator<is_strided or value != 1>()(*this, ((is_strided or value != 1) ?0 : lower[0]) + shape[0]); }

                auto fast(long i) const -> decltype(numpy_gexpr_helper<Arg, S...>::get(*this, i)) {
                    return numpy_gexpr_helper<Arg, S...>::get(*this, lower[0] + (is_contiguous<S...>::value ? i : step[0] * i));
                }
                auto fast(long i) -> decltype(numpy_gexpr_helper<Arg, S...>::get(*this, i)) {
                    return numpy_gexpr_helper<Arg, S...>::get(*this, lower[0] + (is_contiguous<S...>::value ? i : step[0] * i));
                }

#ifdef USE_BOOST_SIMD
                template<class I>
                auto load(I i) const
                -> decltype(boost::simd::load<boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>>(this->buffer, i))
                {
                  typedef dtype T;
                  typedef typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
                  return boost::simd::load<vT>(buffer, lower[0] + i);
                }

#endif

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

                template<class... Sp>
                numpy_gexpr<numpy_gexpr, contiguous_slice, Sp...> operator()(contiguous_slice const& s0, Sp const&... s) const
                {
                    return numpy_gexpr<numpy_gexpr, contiguous_slice, Sp...>(*this, s0, s...);
                }

                //sliced array from sliced array is just a sliced array with modified first sliced dimension
                numpy_gexpr operator[](slice const& s) const
                {
                    normalized_slice ns = s.normalize(shape[0]);
                    numpy_gexpr other = (*this);
                    other.shape[0] = ns.size();
                    other.lower[0] += ns.lower;
                    other.step[0] *= ns.step;
                    return other;
                }
                numpy_gexpr operator[](contiguous_slice const& s) const
                {
                    contiguous_normalized_slice ns = s.normalize(shape[0]);
                    numpy_gexpr other = (*this);
                    other.shape[0] = ns.size();
                    other.lower[0] += ns.lower;
                    return other;
                }
                template<class F>
                    typename std::enable_if<is_numexpr_arg<F>::value, numpy_fexpr<numpy_gexpr, F>>::type
                    operator[](F const& filter) const {
                        return numpy_fexpr<numpy_gexpr, F>(*this, filter);
                    }

                long size() const {
                    return std::accumulate(shape.begin() + 1, shape.end(), *shape.begin(), std::multiplies<long>());
                }
            };

        // As gexpr have to begin with a slice. When we access it, we need to forward the firsts accessed information
        // to an iexpr until the value in S... is a slice again.
        template <class Arg, class S0, class S1, class...S>
            struct numpy_gexpr_helper<Arg, S0, S1, S...> {
                typedef numpy_gexpr<numpy_iexpr<Arg>, S1, S...> type;
                static type get(numpy_gexpr<Arg, S0, S1, S...> const& e, long i) {
                    return type(e, numpy_iexpr<Arg>(e.arg, i));
                }
                static type get(numpy_gexpr<Arg, S0, S1, S...> & e, long i) {
                    return type(e, numpy_iexpr<Arg>(e.arg, i));
                }
            };


        //Compute forwarding of "long" index to iexpr until we reach a new slice in S... parameters
        namespace {

            template <size_t N, class Arg, class...S>
                struct finalize_numpy_gexpr_helper;

            // We reach a new slice so we have a new gexpr
            template <size_t N, class Arg, class... S>
                struct finalize_numpy_gexpr_helper<N, Arg, contiguous_slice, S...> {

                    typedef numpy_gexpr<Arg, contiguous_slice, S...> type;
                    template<class E, class F>
                        static type get(E const& e, F && f) {
                            return type(e, std::forward<F>(f));
                        }
                };

            // We reach a new slice so we have a new gexpr
            template <size_t N, class Arg, class... S>
                struct finalize_numpy_gexpr_helper<N, Arg, slice, S...> {

                    typedef numpy_gexpr<Arg, slice, S...> type;
                    template<class E, class F>
                        static type get(E const& e, F && f) {
                            return type(e, std::forward<F>(f));
                        }
                };

            // We have a long index so it is not a gexpr but a iexpr.
            // We declare a new iexpr and we continue looking for a new slice.
            template <size_t N, class Arg, class... S>
                struct finalize_numpy_gexpr_helper<N, Arg, long, S...> {
                    template<class E, class F>
                        static auto get(E const& e, F && f)
                        -> decltype(finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg>, S...>::get(e, std::declval<numpy_iexpr<Arg>>()))
                        {
                            return finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg>, S...>::get(e, numpy_iexpr<Arg>(std::forward<F>(f), e.indices[N]));
                        }
                    template<class E, class F>
                        static auto get(E & e, F && f)
                        -> decltype(finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg>, S...>::get(e, std::declval<numpy_iexpr<Arg>&>()))
                        {
                            numpy_iexpr<Arg> iexpr(std::forward<F>(f), e.indices[N]);
                            return finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg>, S...>::get(e, iexpr);
                        }
                };

            //If it was a single sliced array, we can return the matching iexpr.
            template <size_t N, class Arg>
                struct finalize_numpy_gexpr_helper<N, Arg, long> {
                    template<class E, class F>
                        static auto get(E const& e, F const & f)
                        -> decltype(numpy_iexpr_helper<F, Arg::value>::get(f, 0))
                        {
                            return numpy_iexpr_helper<F, Arg::value>::get(f, e.indices[N]);
                        }
                    template<class E, class F>
                        static auto get(E const& e, F & f)
                        -> decltype(numpy_iexpr_helper<F, Arg::value>::get(f, 0))
                        {
                            return numpy_iexpr_helper<F, Arg::value>::get(f, e.indices[N]);
                        }
                };
        }

        // forward new combination of gexpr/iexpr computation to finalize_numpy_gexpr_helper
        template <class Arg, class S0, class... S>
            struct numpy_gexpr_helper<Arg, S0, long, S...> {
                static auto get(numpy_gexpr<Arg, S0, long, S...> const& e, long i)
                    ->decltype(finalize_numpy_gexpr_helper<0, numpy_iexpr<Arg>, long, S...>::get(e, std::declval<numpy_iexpr<Arg>>()))
                {
                    return finalize_numpy_gexpr_helper<0, numpy_iexpr<Arg>, long, S...>::get(e, numpy_iexpr<Arg>(e.arg, i));
                }
                static auto get(numpy_gexpr<Arg, S0, long, S...> & e, long i)
                    ->decltype(finalize_numpy_gexpr_helper<0, numpy_iexpr<Arg>, long, S...>::get(e, std::declval<numpy_iexpr<Arg>&>()))
                {
                    return finalize_numpy_gexpr_helper<0, numpy_iexpr<Arg>, long, S...>::get(e, numpy_iexpr<Arg>(e.arg, i));
                }
            };

        //If we have no more slice later, we can say it is an iexpr (We look only for one last long? Not many last long?)
        template <class Arg, class S>
            struct numpy_gexpr_helper<Arg, S, long> {
                static auto get(numpy_gexpr<Arg, S, long> const& e, long i)
                    -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg>, numpy_iexpr<Arg>::value>::get(std::declval<numpy_iexpr<Arg>>(), 0))
                {
                    return numpy_iexpr_helper<numpy_iexpr<Arg>, numpy_iexpr<Arg>::value>::get(numpy_iexpr<Arg>(e.arg, i), e.indices[0]);
                }
                static auto get(numpy_gexpr<Arg, S, long> & e, long i)
                    -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg>, numpy_iexpr<Arg>::value>::get(std::declval<numpy_iexpr<Arg>&>(), 0))
                {
                    numpy_iexpr<Arg> iexpr(e.arg, i);
                    return numpy_iexpr_helper<numpy_iexpr<Arg>, numpy_iexpr<Arg>::value>::get(iexpr, e.indices[0]);
                }
            };

        template <class Arg, class S>
            struct numpy_gexpr_helper<Arg, S> : numpy_iexpr_helper<numpy_gexpr<Arg, S>, numpy_gexpr<Arg, S>::value> {
            };

    }
    template<class Arg, class...S>
        struct assignable<types::numpy_gexpr<Arg, S...>>
        {
            typedef types::numpy_gexpr<typename assignable<Arg>::type, S...> type;
        };

    template<class Arg, class... S>
        struct lazy<types::numpy_gexpr<Arg, S...>>
        {
            typedef types::numpy_gexpr<typename lazy<Arg>::type, typename lazy<S>::type...> type;
        };
    template<class Arg, class... S>
        struct lazy<types::numpy_gexpr<Arg const &, S...>>
        {
            typedef types::numpy_gexpr<typename lazy<Arg>::type const &, typename lazy<S>::type...> type;
        };

}


#endif


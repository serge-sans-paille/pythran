#ifndef PYTHONIC_TYPES_NUMPY_GEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_GEXPR_HPP

namespace pythonic {

    namespace types {

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

                typedef typename std::remove_reference<decltype(std::declval<typename nth_value_type<typename std::remove_reference<Arg>::type, count_long<S...>::value>::type>()[0L])>::type value_type;
                typedef typename std::remove_reference<Arg>::type::dtype dtype;
                static constexpr size_t value = std::remove_reference<Arg>::type::value - count_long<S...>::value;

                typedef nditerator<numpy_gexpr<Arg, S...>> iterator;
                typedef const_nditerator<numpy_gexpr<Arg, S...>> const_iterator;

                Arg arg;
                dtype* buffer;
                array<long, value> shape;
                array<long, value> lower;
                array<long, value> step;
                array<long, std::remove_reference<Arg>::type::value - value> indices;

                numpy_gexpr() {}
                numpy_gexpr(numpy_gexpr const& ) = default;
                numpy_gexpr(numpy_gexpr && ) = default;

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

                numpy_gexpr(Arg const &arg, S const &...s) : arg(arg), buffer(arg.buffer) {
                    std::tuple<S const&...> values(s...);
                    init_shape(values, std::get<0>(values), utils::int_<sizeof...(S)>(), utils::int_<0>());
                    for(size_t i = sizeof...(S) - count_long<S...>::value; i < value; ++i)
                        shape[i] = arg.shape[i];
                }

                template<class Argp, class... Sp>
                numpy_gexpr(numpy_gexpr<Argp, Sp...> const &expr, Arg &&arg) : arg(std::move(arg)), buffer(arg.buffer) {
                    std::copy(expr.shape.begin()+1, expr.shape.end(), shape.begin());
                    std::copy(expr.lower.begin()+1, expr.lower.end(), lower.begin());
                    std::copy(expr.step.begin()+1, expr.step.end(), step.begin());
                    std::copy(expr.indices.begin(), expr.indices.end(), indices.begin());
                }

                template<class G>
                numpy_gexpr(G const &expr, Arg &&arg) : arg(std::move(arg)), buffer(arg.buffer) {
                    std::copy(expr.shape.begin()+1, expr.shape.end(), shape.begin());
                    std::copy(expr.lower.begin()+1, expr.lower.end(), lower.begin());
                    std::copy(expr.step.begin()+1, expr.step.end(), step.begin());
                }

                template<class E>
                numpy_gexpr& operator=(E const& expr) {
                    return utils::broadcast_copy(*this, expr, utils::int_<value - utils::dim_of<E>::value>());
                }
                numpy_gexpr& operator=(numpy_gexpr const& expr) {
                    return utils::broadcast_copy(*this, expr, utils::int_<value - utils::dim_of<numpy_gexpr>::value>());
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

                const_iterator begin() const { return const_iterator(*this, 0); }
                const_iterator end() const { return const_iterator(*this, shape[0]); }

                iterator begin() { return iterator(*this, 0); }
                iterator end() { return iterator(*this, shape[0]); }

                auto fast(long i) const -> decltype(numpy_gexpr_helper<Arg, S...>::get(*this, i)) {
                    return numpy_gexpr_helper<Arg, S...>::get(*this, lower[0] + (is_contiguous<S...>::value ? i : step[0] * i));
                }
                auto fast(long i) -> decltype(numpy_gexpr_helper<Arg, S...>::get(*this, i)) {
                    return numpy_gexpr_helper<Arg, S...>::get(*this, lower[0] + (is_contiguous<S...>::value ? i : step[0] * i));
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
                    other.shape[0] += ns.size();
                    other.lower[0] += ns.lower;
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


        namespace {

            template <size_t N, class Arg, class...S>
                struct finalize_numpy_gexpr_helper;

            template <size_t N, class Arg, class... S>
                struct finalize_numpy_gexpr_helper<N, Arg, contiguous_slice, S...> {

                    typedef numpy_gexpr<Arg, contiguous_slice, S...> type;
                    template<class E, class F>
                        static type get(E const& e, F && f) {
                            return type(e, std::move(f));
                        }
                };

            template <size_t N, class Arg, class... S>
                struct finalize_numpy_gexpr_helper<N, Arg, slice, S...> {

                    typedef numpy_gexpr<Arg, slice, S...> type;
                    template<class E, class F>
                        static type get(E const& e, F && f) {
                            return type(e, std::move(f));
                        }
                };

            template <size_t N, class Arg, class... S>
                struct finalize_numpy_gexpr_helper<N, Arg, long, S...> {
                    template<class E, class F>
                        static auto get(E const& e, F && f)
                        -> decltype(finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg>, S...>::get(e, std::declval<numpy_iexpr<Arg>>()))
                        {
                            return finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg>, S...>::get(e, numpy_iexpr<Arg>(std::move(f), e.indices[N]));
                        }
                    template<class E, class F>
                        static auto get(E & e, F && f)
                        -> decltype(finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg>, S...>::get(e, std::declval<numpy_iexpr<Arg>&>()))
                        {
                            numpy_iexpr<Arg> iexpr(std::move(f), e.indices[N]);
                            return finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg>, S...>::get(e, iexpr);
                        }
                };

            template <size_t N, class Arg>
                struct finalize_numpy_gexpr_helper<N, Arg, long> {
                    template<class E, class F>
                        static auto get(E const& e, F const & f)
                        -> decltype(numpy_iexpr_helper<Arg::value>::get(f, 0))
                        {
                            return numpy_iexpr_helper<Arg::value>::get(f, e.indices[N]);
                        }
                    template<class E, class F>
                        static auto get(E const& e, F & f)
                        -> decltype(numpy_iexpr_helper<Arg::value>::get(f, 0))
                        {
                            return numpy_iexpr_helper<Arg::value>::get(f, e.indices[N]);
                        }
                };
        }

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

        template <class Arg, class S>
            struct numpy_gexpr_helper<Arg, S, long> {
                static auto get(numpy_gexpr<Arg, S, long> const& e, long i)
                    -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg>::value>::get(std::declval<numpy_iexpr<Arg>>(), 0))
                {
                    return numpy_iexpr_helper<numpy_iexpr<Arg>::value>::get(numpy_iexpr<Arg>(e.arg, i), e.indices[0]);
                }
                static auto get(numpy_gexpr<Arg, S, long> & e, long i)
                    -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg>::value>::get(std::declval<numpy_iexpr<Arg>&>(), 0))
                {
                    numpy_iexpr<Arg> iexpr(e.arg, i);
                    return numpy_iexpr_helper<numpy_iexpr<Arg>::value>::get(iexpr, e.indices[0]);
                }
            };

        template <class Arg, class S>
            struct numpy_gexpr_helper<Arg, S> : numpy_iexpr_helper<numpy_gexpr<Arg, S>::value> {
            };

    }

}


#endif


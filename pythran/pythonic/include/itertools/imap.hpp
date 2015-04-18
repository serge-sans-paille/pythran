#ifndef PYTHONIC_INCLUDE_ITERTOOLS_IMAP_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_IMAP_HPP

#include "pythonic/types/none.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/itertools/common.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic {

    namespace utils {
        /* Get the "minimum" of all iterators :
           - only random => random
           - at least one forward => forward 
           */
        template<typename... Iters>
            struct iterator_min;

        template<typename T>
            struct iterator_min<T>
            {
                using type = typename std::iterator_traits<T>::iterator_category;
            };

        template<typename T, typename... Iters>
            struct iterator_min<T, Iters...>
            {
                using type = typename std::conditional<
                    std::is_same<
                        typename std::iterator_traits<T>::iterator_category,
                        std::forward_iterator_tag
                        >::value,
                    std::forward_iterator_tag,
                    typename iterator_min<Iters...>::type
                    >::type;
            };

    }

    namespace itertools {

        template <typename ResultType, typename Operator, typename... Iters>
            struct imap_iterator : std::iterator<typename utils::iterator_min<typename std::remove_reference<Iters>::type::iterator...>::type ,
                                                 ResultType,
                                                 ptrdiff_t,
                                                 ResultType*,
                                                 ResultType /* no ref */ >
            {

                template <typename Op, typename... It>
                    struct imap_iterator_data;

                template <typename Op, typename L0, typename... It>
                    struct imap_iterator_data<Op, L0, It...>
                    {
                        using sequence_type = typename std::remove_cv<typename std::remove_reference<L0>::type>::type;

                        sequence_type iterator_ref;  // keep value of iterable to avoid dangling reference
                        typename sequence_type::iterator iter;
                        imap_iterator_data<Op,It...> rec_iters; 

                        imap_iterator_data();
                        template<class First, class... Types>
                            imap_iterator_data(Op _op, First&& _seq, Types&&... _iters);
                        imap_iterator_data(npos, imap_iterator_data& beg);

                        template<typename... Types> 
                            auto next_value(Types&& ... params) const
                            -> decltype(rec_iters.next_value(std::forward<Types>(params)..., *iter));

                        bool operator==(imap_iterator_data const& other) const;
                        bool operator!=(imap_iterator_data const& other) const;
                        int operator-(imap_iterator_data const& other) const;
                        imap_iterator_data<Op, L0, It...>& operator++();
                        imap_iterator_data<Op, L0, It...>& operator+=(long i);
                        imap_iterator_data<Op, L0, It...> operator+(long i) const;
                    };

                template<typename Op, typename L0>
                    struct imap_iterator_data<Op, L0>
                    {
                        using sequence_type = typename std::remove_cv<typename std::remove_reference<L0>::type>::type;

                        Op op;
                        sequence_type iterator_ref;  // keep value of iterable to avoid dangling reference
                        typename sequence_type::iterator iter;

                        imap_iterator_data();
                        template<class First>
                            imap_iterator_data(Op _op, First&& _seq);
                            imap_iterator_data(npos, imap_iterator_data& beg);

                        template<typename... Types, typename O = Op, typename = typename std::enable_if<!std::is_same<types::none_type, O>::value, O>::type>
                            auto next_value(Types&& ... params) const
                            -> decltype(op(std::forward<Types>(params)..., *iter));
                        template<typename... Types, typename O = Op, typename = typename std::enable_if<std::is_same<types::none_type, O>::value, O>::type>
                            auto next_value(Types&& ... params) const
                            -> decltype(std::make_tuple(std::forward<Types>(params)..., *iter));

                        bool operator==(imap_iterator_data const& other) const;
                        bool operator!=(imap_iterator_data const& other) const;
                        int operator-(imap_iterator_data const& other) const;
                        imap_iterator_data<Op, L0>& operator++();
                        imap_iterator_data<Op, L0>& operator+=(long i);
                        imap_iterator_data<Op, L0> operator+(long i) const;
                    };

                imap_iterator_data<Operator, Iters...> it_data;

                imap_iterator();
                template<class... Types>
                    imap_iterator(Operator _op, Types&&... _iters);
                // constructor for the end iterator. Note how it uses a reference to another iterator to initialize itself
                // that way we are sure to always iterate on the same data
                template<class... Types>
                    imap_iterator(npos, imap_iterator& beg);

                typename imap_iterator::reference operator*() const;
                imap_iterator& operator++();
                imap_iterator& operator+=(long i);
                imap_iterator operator+(long i) const;
                bool operator==(imap_iterator const& other) const;
                bool operator!=(imap_iterator const& other) const;
                bool operator<(imap_iterator const& other) const;
                int operator-(imap_iterator const& other) const;
            };


        template <typename ResultType, typename Operator, typename... Iters>
            struct _imap: imap_iterator<ResultType, Operator, Iters...>
            {
                using iterator = imap_iterator<ResultType, Operator, Iters...>;
                using value_type = ResultType;

                iterator end_iter;

                _imap();
                template<class... Types>
                    _imap(Operator&& _op, Types&&... _iters);

                iterator& begin();
                iterator const& begin() const;
                iterator const& end() const;
                long size() const;
            };

        template <typename... Iter>
            auto imap(types::none_type _op, Iter && ... iters)
            -> _imap< decltype(std::make_tuple((*iters.begin())...)), types::none_type, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...>;

        template <typename Operator, typename... Iter>
            auto imap(Operator&& _op, Iter && ... iters)
            -> _imap< decltype(_op( (*iters.begin())...)), Operator, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...>;

        PROXY_DECL(pythonic::itertools, imap);

    }

    namespace types {

        template<class O, class Op, class Iter>
            struct len_of<pythonic::itertools::_imap<O, Op, Iter>>
            {
                static constexpr long value = len_of<typename std::remove_cv<typename std::remove_reference<Iter>::type>::type>::value;
            };

        template<class O, class Op, class I0, class I1, class... Iter>
            struct len_of<pythonic::itertools::_imap<O, Op, I0, I1, Iter...>>
            {
                static constexpr long _head = len_of<typename std::remove_cv<typename std::remove_reference<I0>::type>::type>::value;
                static constexpr long _tail = len_of<pythonic::itertools::_imap<O, Op,I1, Iter...>>::value;
                static constexpr long value = (_head < _tail ? _head : _tail); // take the minimal value. If one is negative, it will be automatically selected
            };
    }

}

#endif

#ifndef PYTHONIC_ITERTOOLS_IMAP_HPP
#define PYTHONIC_ITERTOOLS_IMAP_HPP

#include "pythonic/types/none.hpp"
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
            struct iterator_min<T> {typedef typename std::iterator_traits<T>::iterator_category type;};

        template<typename T, typename... Iters>
            struct iterator_min<T, Iters...> {typedef typename std::conditional<std::is_same<typename std::iterator_traits<T>::iterator_category, std::forward_iterator_tag>::value, std::forward_iterator_tag, typename iterator_min<Iters...>::type >::type type;};

    }

    namespace itertools {

        template <typename ResultType, typename Operator, typename... Iters>
            struct imap_iterator : std::iterator< typename utils::iterator_min<typename std::remove_reference<Iters>::type::iterator...>::type , ResultType, ptrdiff_t, ResultType*, ResultType /* no ref */ >  {

                template <typename Op, typename... It>
                    struct imap_iterator_data;

                template <typename Op, typename L0, typename... It>
                    struct imap_iterator_data<Op, L0, It...>
                    {
                        typedef typename std::remove_cv<typename std::remove_reference<L0>::type>::type sequence_type;
                        sequence_type iterator_ref;  // keep value of iterable to avoid dangling reference
                        typename sequence_type::iterator iter;
                        imap_iterator_data<Op,It...> rec_iters; 

                        imap_iterator_data() {}
                        template<class First, class... Types>
                            imap_iterator_data(Op _op, First&& _seq, Types&&... _iters) : iterator_ref(_seq), iter(iterator_ref.begin()), rec_iters(_op, std::forward<Types>(_iters)...) {}
                        template<class First, class... Types>
                            imap_iterator_data(npos, Op _op, First&& _seq, Types&&... _iters) : iterator_ref(_seq), iter(iterator_ref.end()), rec_iters(npos(), _op, std::forward<Types>(_iters)...) {}

                        template<typename... Types> 
                            auto next_value(Types&& ... params) const
                            -> decltype(rec_iters.next_value(std::forward<Types>(params)..., *iter))
                            {
                                return rec_iters.next_value(std::forward<Types>(params)..., *iter);
                            }

                        bool operator==(imap_iterator_data const& other) const {
                            return !(*this != other);
                        }

                        bool operator!=(imap_iterator_data const& other) const {
                            return (iter != other.iter) and (rec_iters != other.rec_iters); // stop as soon as one is different
                        }

                        int operator-(imap_iterator_data const& other) const {
                            return (iter - other.iter);
                        }

                        imap_iterator_data<Op, L0, It...>& operator++() {
                            ++iter;
                            ++rec_iters;
                            return *this;
                        }
                        imap_iterator_data<Op, L0, It...>& operator+=(long i) {
                            iter+=i;
                            rec_iters+=i;
                            return *this;
                        }
                        imap_iterator_data<Op, L0, It...> operator+(long i) const {
                            imap_iterator_data<Op, L0, It...> other(*this);
                            return other+=i;
                        }

                    };

                template<typename Op, typename L0>
                    struct imap_iterator_data<Op, L0>
                    {
                        Op op;
                        typedef typename std::remove_cv<typename std::remove_reference<L0>::type>::type sequence_type;
                        sequence_type iterator_ref;  // keep value of iterable to avoid dangling reference
                        typename sequence_type::iterator iter;

                        imap_iterator_data() {}
                        template<class First>
                            imap_iterator_data(Op _op, First&& _seq) : op(_op), iterator_ref(_seq), iter(iterator_ref.begin()) {
                            }
                        template<class First>
                            imap_iterator_data(npos, Op _op, First&& _seq) : op(_op), iterator_ref(_seq), iter(iterator_ref.end()) {
                            }

                        template<typename... Types, typename O = Op, typename = typename std::enable_if<!std::is_same<types::none_type, O>::value, O>::type>
                            auto next_value(Types&& ... params) const
                            -> decltype(op(std::forward<Types>(params)..., *iter))
                            {
                                return op(std::forward<Types>(params)..., *iter);
                            }
                        template<typename... Types, typename O = Op, typename = typename std::enable_if<std::is_same<types::none_type, O>::value, O>::type>
                            auto next_value(Types&& ... params) const
                            -> decltype(std::make_tuple(std::forward<Types>(params)..., *iter))
                            {
                                return std::make_tuple(std::forward<Types>(params)..., *iter);
                            }


                        bool operator==(imap_iterator_data const& other) const {
                            return !(iter != other.iter); 
                        }

                        bool operator!=(imap_iterator_data const& other) const {
                            return (iter != other.iter); 
                        }

                        int operator-(imap_iterator_data const& other) const {
                            return (iter - other.iter);
                        }

                        imap_iterator_data<Op, L0>& operator++() {
                            ++iter;
                            return *this;
                        }
                        imap_iterator_data<Op, L0>& operator+=(long i) {
                            iter+=i;
                            return *this;
                        }
                        imap_iterator_data<Op, L0> operator+(long i) const {
                            imap_iterator_data<Op, L0> other(*this);
                            return other+=i;
                        }


                    };

                imap_iterator_data<Operator, Iters...> it_data;

                imap_iterator() {}
                template<class... Types>
                    imap_iterator(Operator _op, Types&&... _iters)  : it_data(_op, std::forward<Types>(_iters)...) {}
                template<class... Types>
                    imap_iterator(npos, Operator _op,Types&&... _iters)  : it_data(npos(), _op, std::forward<Types>(_iters)...) {}

                typename imap_iterator::reference operator*() const { 
                    return it_data.next_value(); //value; 
                }

                imap_iterator& operator++() { 
                    ++it_data;
                    return *this; 
                }
                imap_iterator& operator+=(long i) { 
                    it_data+=i;
                    return *this; 
                }
                imap_iterator operator+(long i) const { 
                    imap_iterator other(*this);
                    return other+=i;
                }

                bool operator==(imap_iterator const& other) const { 
                    return it_data == other.it_data; 
                }

                bool operator!=(imap_iterator const& other) const { 
                    return it_data != other.it_data; 
                }

                bool operator<(imap_iterator const& other) const {
                    return it_data != other.it_data; 
                }

                int operator-(imap_iterator const& other) const {
                    return it_data - other.it_data;
                }

            };


        template <typename ResultType, typename Operator, typename... Iters>
            struct _imap: imap_iterator<ResultType, Operator, Iters...> {

                typedef imap_iterator<ResultType, Operator, Iters...> iterator;

                iterator end_iter;

                typedef ResultType value_type;

                _imap() {}
                template<class... Types>
                    _imap(Operator&& _op, Types&&... _iters) :
                        imap_iterator<ResultType, Operator, Iters...>(_op, std::forward<Types>(_iters)...),
                        end_iter(npos(), _op, std::forward<Types>(_iters)...)
                {}

                iterator& begin() { return *this; }
                iterator const& begin() const { return *this; }
                iterator const& end() const { return end_iter; }
                long size() const { return end() - begin(); }

            };

        template <typename... Iter>
            auto imap(types::none_type _op, Iter && ... iters)
            -> _imap< decltype(std::make_tuple((*iters.begin())...)), types::none_type, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...>
            {
                return _imap<decltype(std::make_tuple((*iters.begin())...)), types::none_type, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...> (std::forward<types::none_type>(_op), std::forward<Iter>(iters)...);
            }

        template <typename Operator, typename... Iter>
            auto imap(Operator&& _op, Iter && ... iters)
            -> _imap< decltype(_op( (*iters.begin())...)), Operator, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...>
            {
                return _imap<decltype(_op((*iters.begin())...)), Operator, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...> (std::forward<Operator>(_op), std::forward<Iter>(iters)...);
            }

        PROXY(pythonic::itertools,imap);

    }

}

#endif


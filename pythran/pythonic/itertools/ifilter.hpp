#ifndef PYTHONIC_ITERTOOLS_IFILTER_HPP
#define PYTHONIC_ITERTOOLS_IFILTER_HPP

#include "pythonic/types/none.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/itertools/common.hpp"

#include <iterator>
#include <type_traits>


namespace pythonic {

    namespace itertools {

        template <typename ResultType, typename Operator, typename List0>
            struct ifilter_iterator : std::iterator< std::forward_iterator_tag, ResultType >  {

                Operator op;
                typedef typename std::remove_cv<typename std::remove_reference<List0>::type>::type sequence_type;
                typename List0::iterator iter;
                typename List0::iterator iter_end;

                bool test_filter(std::false_type) {
                    return op(*iter);
                }

                bool test_filter(std::true_type) {
                    return *iter;
                }

                ifilter_iterator() {}
                ifilter_iterator(Operator _op, List0 _seq) : op(_op), iter(const_cast<sequence_type&>(_seq).begin()), iter_end(const_cast<sequence_type &>(_seq).end()) {
                    if (!test_filter(std::is_same<types::none_type, Operator>()))
                        next_value();
                }
                ifilter_iterator(npos, Operator _op, List0 _seq) : op(_op), iter(const_cast<sequence_type &>(_seq).end()), iter_end(const_cast<sequence_type &>(_seq).end()) {
                }

                ResultType operator*() const { 
                    return *iter;
                }

                ifilter_iterator& operator++() { 
                    next_value();
                    return *this;
                }

                void next_value() {
                    while (++iter != iter_end) {
                        if (test_filter(std::is_same<types::none_type, Operator>()))
                            return;
                    }
                }

                bool operator==(ifilter_iterator const& other) const { 
                    return !(iter != other.iter); 
                }

                bool operator!=(ifilter_iterator const& other) const { 
                    return iter != other.iter; 
                }

                bool operator<(ifilter_iterator const& other) const {
                    return iter != other.iter; 
                }

                int operator-(ifilter_iterator const& other) const {
                    return (iter - other.iter); 
                }

            };

        template <typename ResultType, typename Operator, typename List0>
            struct _ifilter : ifilter_iterator<ResultType, Operator, List0>{

                typedef ifilter_iterator<ResultType, Operator, List0> iterator;

                List0 seq; // to make sure we keep a reference on all the containers
                iterator end_iter;

                typedef ResultType value_type;

                _ifilter() {}
                _ifilter(Operator _op, List0 _seq) : iterator(_op, _seq), seq(_seq), end_iter(npos(), _op, _seq) {
                }

                iterator& begin() { return *this; }
                iterator const& begin() const { return *this; }
                iterator const& end() const { return end_iter; }

            };

        template <typename List0>
            auto ifilter(types::none_type _op, List0&& _seq) -> _ifilter< typename std::remove_cv<typename std::remove_reference<List0>::type>::type::value_type, types::none_type, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> {
                return _ifilter<typename std::remove_cv<typename std::remove_reference<List0>::type>::type::value_type, types::none_type, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> (std::forward<types::none_type>(_op), std::forward<List0>(_seq));
            }

        template <typename Operator, typename List0>
            auto ifilter(Operator&& _op, List0&& _seq) -> _ifilter< typename std::remove_cv<typename std::remove_reference<decltype(*_seq.begin())>::type>::type, Operator, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> {
                return _ifilter<typename std::remove_cv<typename std::remove_reference<decltype(*_seq.begin())>::type>::type, Operator, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> (std::forward<Operator>(_op), std::forward<List0>(_seq));
            }

        PROXY(pythonic::itertools,ifilter);

    }

}
#endif

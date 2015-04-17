#ifndef PYTHONIC_ITERTOOLS_IFILTER_HPP
#define PYTHONIC_ITERTOOLS_IFILTER_HPP

#include "pythonic/include/itertools/ifilter.hpp"
#include "pythonic/types/none.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/itertools/common.hpp"

#include <iterator>
#include <type_traits>


namespace pythonic {

    namespace itertools {


        template <typename ResultType, typename Operator, typename List0>
            bool ifilter_iterator<ResultType, Operator, List0>::test_filter(std::false_type)
            {
                return op(*iter);
            }

        template <typename ResultType, typename Operator, typename List0>
            bool ifilter_iterator<ResultType, Operator, List0>::test_filter(std::true_type)
            {
                return *iter;
            }

        template <typename ResultType, typename Operator, typename List0>
            ifilter_iterator<ResultType, Operator, List0>::ifilter_iterator()
            {}

        template <typename ResultType, typename Operator, typename List0>
            ifilter_iterator<ResultType, Operator, List0>::ifilter_iterator(Operator _op, List0 _seq) :
                op(_op),
                iter(const_cast<sequence_type&>(_seq).begin()),
                iter_end(const_cast<sequence_type &>(_seq).end())
            {
                if (!test_filter(std::is_same<types::none_type, Operator>()))
                    next_value();
            }

        template <typename ResultType, typename Operator, typename List0>
            ifilter_iterator<ResultType, Operator, List0>::ifilter_iterator(npos, Operator _op, List0 _seq) :
                op(_op),
                iter(const_cast<sequence_type &>(_seq).end()),
                iter_end(const_cast<sequence_type &>(_seq).end())
            {}

        template <typename ResultType, typename Operator, typename List0>
            ResultType ifilter_iterator<ResultType, Operator, List0>::operator*() const
            { 
                return *iter;
            }

        template <typename ResultType, typename Operator, typename List0>
            ifilter_iterator<ResultType, Operator, List0>& ifilter_iterator<ResultType, Operator, List0>::operator++()
            {
                next_value();
                return *this;
            }

        template <typename ResultType, typename Operator, typename List0>
            void ifilter_iterator<ResultType, Operator, List0>::next_value()
            {
                while (++iter != iter_end)
                {
                    if (test_filter(std::is_same<types::none_type, Operator>()))
                        return;
                }
            }

        template <typename ResultType, typename Operator, typename List0>
            bool ifilter_iterator<ResultType, Operator, List0>::operator==(ifilter_iterator const& other) const
            {
                return !(iter != other.iter); 
            }

        template <typename ResultType, typename Operator, typename List0>
            bool ifilter_iterator<ResultType, Operator, List0>::operator!=(ifilter_iterator const& other) const
            { 
                return iter != other.iter; 
            }

        template <typename ResultType, typename Operator, typename List0>
            bool ifilter_iterator<ResultType, Operator, List0>::operator<(ifilter_iterator const& other) const
            {
                return iter != other.iter; 
            }

        template <typename ResultType, typename Operator, typename List0>
            int ifilter_iterator<ResultType, Operator, List0>::operator-(ifilter_iterator const& other) const
            {
                return (iter - other.iter); 
            }

        template <typename ResultType, typename Operator, typename List0>
            _ifilter<ResultType, Operator, List0>::_ifilter()
            {}

        template <typename ResultType, typename Operator, typename List0>
            _ifilter<ResultType, Operator, List0>::_ifilter(Operator _op, List0 _seq) :
                iterator(_op, _seq),
                seq(_seq),
                end_iter(npos(), _op, _seq)
            {}

        template <typename ResultType, typename Operator, typename List0>
            typename _ifilter<ResultType, Operator, List0>::iterator&
            _ifilter<ResultType, Operator, List0>::begin()
            {
                return *this;
            }

        template <typename ResultType, typename Operator, typename List0>
            typename _ifilter<ResultType, Operator, List0>::iterator
            const& _ifilter<ResultType, Operator, List0>::begin() const
            {
                return *this;
            }

        template <typename ResultType, typename Operator, typename List0>
            typename _ifilter<ResultType, Operator, List0>::iterator const&
            _ifilter<ResultType, Operator, List0>::end() const
            {
                return end_iter;
            }

        template <typename List0>
            _ifilter<
                typename std::remove_cv<
                    typename std::remove_reference<List0>::type
                    >::type::value_type,
                types::none_type,
                typename std::remove_cv<
                    typename std::remove_reference<List0>::type
                    >::type
                >
            ifilter(types::none_type _op, List0&& _seq)
            {
                return {std::forward<types::none_type>(_op), std::forward<List0>(_seq)};
            }

        template <typename Operator, typename List0>
            auto ifilter(Operator&& _op, List0&& _seq)
            -> _ifilter<
                typename std::remove_cv<
                    typename std::remove_reference<decltype(*_seq.begin())>::type
                    >::type,
                Operator,
                typename std::remove_cv<
                    typename std::remove_reference<List0>::type
                    >::type
                >
            {
                return {std::forward<Operator>(_op), std::forward<List0>(_seq)};
            }

        PROXY_IMPL(pythonic::itertools,ifilter);

    }

}
#endif

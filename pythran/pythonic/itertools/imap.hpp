#ifndef PYTHONIC_ITERTOOLS_IMAP_HPP
#define PYTHONIC_ITERTOOLS_IMAP_HPP

#include "pythonic/include/itertools/imap.hpp"
#include "pythonic/types/none.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/itertools/common.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic {

    namespace itertools {

        template <typename ResultType, typename Operator, typename... Iters>
        template <typename Op, typename L0, typename... It>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>::imap_iterator_data()
            {}

        template <typename ResultType, typename Operator, typename... Iters>
        template <typename Op, typename L0, typename... It>
        template<class First, class... Types>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>::imap_iterator_data(Op _op, First&& _seq, Types&&... _iters) :
                iterator_ref(_seq),
                iter(iterator_ref.begin()),
                rec_iters(_op, std::forward<Types>(_iters)...)
            {}

        template <typename ResultType, typename Operator, typename... Iters>
        template <typename Op, typename L0, typename... It>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>::imap_iterator_data(npos, imap_iterator_data& beg) :
                iterator_ref(beg.iterator_ref),
                iter(beg.iterator_ref.end()),
                rec_iters(npos(), beg.rec_iters)
            {}

        template <typename ResultType, typename Operator, typename... Iters>
        template <typename Op, typename L0, typename... It>
        template<typename... Types> 
            auto imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>::next_value(Types&& ... params) const
            -> decltype(rec_iters.next_value(std::forward<Types>(params)..., *iter))
            {
                return rec_iters.next_value(std::forward<Types>(params)..., *iter);
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template <typename Op, typename L0, typename... It>
            bool imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>::operator==(imap_iterator_data const& other) const
            {
                return !(*this != other);
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template <typename Op, typename L0, typename... It>
            bool imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>::operator!=(imap_iterator_data const& other) const
            {
                return (iter != other.iter) and (rec_iters != other.rec_iters); // stop as soon as one is different
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template <typename Op, typename L0, typename... It>
            int imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>::operator-(imap_iterator_data const& other) const
            {
                return (iter - other.iter);
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template <typename Op, typename L0, typename... It>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>&
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>::operator++()
            {
                ++iter;
                ++rec_iters;
                return *this;
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template <typename Op, typename L0, typename... It>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>&
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>::operator+=(long i)
            {
                iter += i;
                rec_iters += i;
                return *this;
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template <typename Op, typename L0, typename... It>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...>::operator+(long i) const
            {
                imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0, It...> other(*this);
                return other += i;
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::imap_iterator_data()
            {}

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
        template<class First>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::imap_iterator_data(Op _op, First&& _seq) :
                op(_op),
                iterator_ref(_seq),
                iter(iterator_ref.begin())
            {}

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::imap_iterator_data(npos, imap_iterator_data& beg) :
                op(beg.op),
                iterator_ref(beg.iterator_ref),
                iter(beg.iterator_ref.end())
            {}

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
        template<typename... Types, typename O, typename>
            auto imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::next_value(Types&& ... params) const
            -> decltype(op(std::forward<Types>(params)..., *iter))
            {
                return op(std::forward<Types>(params)..., *iter);
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
        template<typename... Types, typename O, typename>
            auto imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::next_value(Types&& ... params) const
            -> decltype(std::make_tuple(std::forward<Types>(params)..., *iter))
            {
                return std::make_tuple(std::forward<Types>(params)..., *iter);
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
            bool imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::operator==(imap_iterator_data const& other) const
            {
                return !(iter != other.iter); 
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
            bool imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::operator!=(imap_iterator_data const& other) const
            {
                return (iter != other.iter); 
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
            int imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::operator-(imap_iterator_data const& other) const
            {
                return (iter - other.iter);
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>&
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::operator++()
            {
                ++iter;
                return *this;
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>&
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::operator+=(long i)
            {
                iter += i;
                return *this;
            }

        template <typename ResultType, typename Operator, typename... Iters>
        template<typename Op, typename L0>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0>::operator+(long i) const
            {
                imap_iterator<ResultType, Operator, Iters...>::imap_iterator_data<Op, L0> other(*this);
                return other+=i;
            }

        template <typename ResultType, typename Operator, typename... Iters>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator()
            {}

        template <typename ResultType, typename Operator, typename... Iters>
        template<class... Types>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator(Operator _op, Types&&... _iters) :
                it_data(_op, std::forward<Types>(_iters)...)
            {}

        // constructor for the end iterator. Note how it uses a reference to another iterator to initialize itself
        // that way we are sure to always iterate on the same data
        template <typename ResultType, typename Operator, typename... Iters>
        template<class... Types>
            imap_iterator<ResultType, Operator, Iters...>::imap_iterator(npos, imap_iterator& beg) :
                it_data(npos(), beg.it_data)
            {}

        template <typename ResultType, typename Operator, typename... Iters>
            typename imap_iterator<ResultType, Operator, Iters...>::reference
            imap_iterator<ResultType, Operator, Iters...>::operator*() const
            { 
                return it_data.next_value(); //value; 
            }

        template <typename ResultType, typename Operator, typename... Iters>
            imap_iterator<ResultType, Operator, Iters...>&
            imap_iterator<ResultType, Operator, Iters...>::operator++()
            { 
                ++it_data;
                return *this; 
            }

        template <typename ResultType, typename Operator, typename... Iters>
            imap_iterator<ResultType, Operator, Iters...>&
            imap_iterator<ResultType, Operator, Iters...>::operator+=(long i)
            { 
                it_data+=i;
                return *this; 
            }

        template <typename ResultType, typename Operator, typename... Iters>
            imap_iterator<ResultType, Operator, Iters...>
            imap_iterator<ResultType, Operator, Iters...>::operator+(long i) const
            { 
                imap_iterator<ResultType, Operator, Iters...> other(*this);
                return other+=i;
            }

        template <typename ResultType, typename Operator, typename... Iters>
            bool imap_iterator<ResultType, Operator, Iters...>::operator==(imap_iterator<ResultType, Operator, Iters...> const& other) const
            { 
                return it_data == other.it_data; 
            }

        template <typename ResultType, typename Operator, typename... Iters>
            bool imap_iterator<ResultType, Operator, Iters...>::operator!=(imap_iterator<ResultType, Operator, Iters...> const& other) const
            { 
                return it_data != other.it_data; 
            }

        template <typename ResultType, typename Operator, typename... Iters>
            bool imap_iterator<ResultType, Operator, Iters...>::operator<(imap_iterator<ResultType, Operator, Iters...> const& other) const
            {
                return it_data != other.it_data; 
            }

        template <typename ResultType, typename Operator, typename... Iters>
            int imap_iterator<ResultType, Operator, Iters...>::operator-(imap_iterator<ResultType, Operator, Iters...> const& other) const
            {
                return it_data - other.it_data;
            }

        template <typename ResultType, typename Operator, typename... Iters>
            _imap<ResultType, Operator, Iters...>::_imap()
            {}

        template <typename ResultType, typename Operator, typename... Iters>
        template<class... Types>
            _imap<ResultType, Operator, Iters...>::_imap(Operator&& _op, Types&&... _iters) :
                imap_iterator<ResultType, Operator, Iters...>(_op, std::forward<Types>(_iters)...),
                end_iter(npos(), *this) // NOTE: end_iter is initialised using npos to distinguish it from begin,
                                        // and using a reference to begin (i.e. this) to avoid iterating over different
                                        // objects.
            {}

        template <typename ResultType, typename Operator, typename... Iters>
            typename _imap<ResultType, Operator, Iters...>::iterator&
            _imap<ResultType, Operator, Iters...>::begin()
            {
                return *this;
            }

        template <typename ResultType, typename Operator, typename... Iters>
            typename _imap<ResultType, Operator, Iters...>::iterator const&
            _imap<ResultType, Operator, Iters...>::begin() const
            {
                return *this;
            }

        template <typename ResultType, typename Operator, typename... Iters>
            typename _imap<ResultType, Operator, Iters...>::iterator
            const& _imap<ResultType, Operator, Iters...>::end() const
            {
                return end_iter;
            }

        template <typename ResultType, typename Operator, typename... Iters>
            long _imap<ResultType, Operator, Iters...>::size() const
            {
                return end() - begin();
            }

        template <typename... Iter>
            auto imap(types::none_type _op, Iter && ... iters)
            -> _imap< decltype(std::make_tuple((*iters.begin())...)), types::none_type, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...>
            {
                return {std::forward<types::none_type>(_op), std::forward<Iter>(iters)...};
            }

        template <typename Operator, typename... Iter>
            auto imap(Operator&& _op, Iter && ... iters)
            -> _imap< decltype(_op( (*iters.begin())...)), Operator, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...>
            {
                return {std::forward<Operator>(_op), std::forward<Iter>(iters)...};
            }

        PROXY_IMPL(pythonic::itertools, imap);

    }

}

#endif

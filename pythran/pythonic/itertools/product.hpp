#ifndef PYTHONIC_ITERTOOLS_PRODUCT_HPP
#define PYTHONIC_ITERTOOLS_PRODUCT_HPP

#include "pythonic/include/itertools/product.hpp"
#include "pythonic/itertools/common.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic {

    namespace itertools {

        template <typename ResultType, typename... Iters>
        template <typename L0, typename... It>
            product_iterator<ResultType, Iters...>::product_iterator_data<L0, It...>::product_iterator_data()
            {}

        template <typename ResultType, typename... Iters>
        template <typename L0, typename... It>
            product_iterator<ResultType, Iters...>::product_iterator_data<L0, It...>::product_iterator_data(L0 _seq, It... _iters) :
                iter(const_cast<sequence_type&>(_seq).begin()),
                iter_begin(const_cast<sequence_type&>(_seq).begin()),
                iter_end(const_cast<sequence_type&>(_seq).end()),
                rec_iters(_iters...)
            {}

        template <typename ResultType, typename... Iters>
        template <typename L0, typename... It>
            product_iterator<ResultType, Iters...>::product_iterator_data<L0, It...>::product_iterator_data(npos, L0 _seq, It... _iters) :
                iter(const_cast<sequence_type &>(_seq).end()),
                iter_begin(const_cast<sequence_type&>(_seq).begin()),
                iter_end(const_cast<sequence_type&>(_seq).end()),
                rec_iters(npos(), _iters...)
            {}

        template <typename ResultType, typename... Iters>
        template <typename L0, typename... It>
            bool product_iterator<ResultType, Iters...>::product_iterator_data<L0, It...>::next_value()
            {
                if (rec_iters.next_value())
                {
                    ++iter;
                    if (!(iter != iter_end))
                    {
                        iter = iter_begin;
                        return true;
                    }
                }
                return false;
            }

        template <typename ResultType, typename... Iters>
        template <typename L0, typename... It>
        template<typename... Types> 
            auto product_iterator<ResultType, Iters...>::product_iterator_data<L0, It...>::get_value(Types const&... params) const
            -> decltype(rec_iters.get_value(params..., *iter))
            {
                return rec_iters.get_value(params..., *iter);
            }

        template <typename ResultType, typename... Iters>
        template <typename L0, typename... It>
            long product_iterator<ResultType, Iters...>::product_iterator_data<L0, It...>::operator-(product_iterator_data<L0, It...> const& other) const
            {
                return (iter - other.iter) * (rec_iters - other.rec_iters);
            }

        template <typename ResultType, typename... Iters>
        template <typename L0>
            product_iterator<ResultType, Iters...>::product_iterator_data<L0>::product_iterator_data()
            {}

        template <typename ResultType, typename... Iters>
        template <typename L0>
            product_iterator<ResultType, Iters...>::product_iterator_data<L0>::product_iterator_data(L0 _seq) :
                iter(const_cast<sequence_type &>(_seq).begin()),
                iter_begin(const_cast<sequence_type&>(_seq).begin()),
                iter_end(const_cast<sequence_type&>(_seq).end())
            {}

        template <typename ResultType, typename... Iters>
        template <typename L0>
            product_iterator<ResultType, Iters...>::product_iterator_data<L0>::product_iterator_data(npos, L0 _seq) :
                iter(const_cast<sequence_type &>(_seq).end()),
                iter_begin(const_cast<sequence_type&>(_seq).begin()),
                iter_end(const_cast<sequence_type&>(_seq).end())
            {}

        template <typename ResultType, typename... Iters>
        template <typename L0>
            bool
            product_iterator<ResultType, Iters...>::product_iterator_data<L0>::next_value()
            {
                ++iter;
                if (!(iter != iter_end))
                {
                    iter = iter_begin;
                    return true;
                }
                return false;
            }

        template <typename ResultType, typename... Iters>
        template <typename L0>
        template<typename... Types>
            auto product_iterator<ResultType, Iters...>::product_iterator_data<L0>::get_value(Types const&... params) const
            -> decltype(std::make_tuple(params..., *iter))
            {
                return std::make_tuple(params..., *iter);
            }

        template <typename ResultType, typename... Iters>
        template <typename L0>
            long
            product_iterator<ResultType, Iters...>::product_iterator_data<L0>::operator-(product_iterator_data<L0> const& other) const
            {
                return iter - other.iter;
            }

        template <typename ResultType, typename... Iters>
            product_iterator<ResultType, Iters...>::product_iterator()
            {}

        template <typename ResultType, typename... Iters>
            product_iterator<ResultType, Iters...>::product_iterator(Iters... _iters) :
                it_data(_iters...),
                end(false)
            {}

        template <typename ResultType, typename... Iters>
            product_iterator<ResultType, Iters...>::product_iterator(npos, Iters... _iters) :
                it_data(npos(), _iters...),
                end(true)
            {}

        template <typename ResultType, typename... Iters>
            auto product_iterator<ResultType, Iters...>::operator*() const
            -> decltype(this->it_data.get_value())
            {
                return it_data.get_value();
            }

        template <typename ResultType, typename... Iters>
            product_iterator<ResultType, Iters...>&
            product_iterator<ResultType, Iters...>::operator++()
            { 
                end = it_data.next_value();
                return *this; 
            }

        template <typename ResultType, typename... Iters>
            bool
            product_iterator<ResultType, Iters...>::operator==(product_iterator<ResultType, Iters...> const& other) const
            { 
                return (end == other.end);
            }

        template <typename ResultType, typename... Iters>
            bool
            product_iterator<ResultType, Iters...>::operator!=(product_iterator<ResultType, Iters...> const& other) const
            {
                return end != other.end;
            }

        template <typename ResultType, typename... Iters>
            bool
            product_iterator<ResultType, Iters...>::operator<(product_iterator<ResultType, Iters...> const& other) const
            {
                return end != other.end;                       
            }

        template <typename ResultType, typename... Iters>
            long
            product_iterator<ResultType, Iters...>::operator-(product_iterator<ResultType, Iters...> const& other) const
            {
                return it_data - other.it_data;
            }


        template <typename... Iters>
            _product<Iters...>::_product()
            {}

        template <typename... Iters>
            _product<Iters...>::_product(Iters... _iters) :
                iterator(_iters...),
                iters(_iters...),
                end_iter(npos(), _iters...)
            {}

        template <typename... Iters>
            typename _product<Iters...>::iterator& _product<Iters...>::begin()
            {
                return *this;
            }

        template <typename... Iters>
            typename _product<Iters...>::iterator
            const& _product<Iters...>::begin() const
            {
                return *this;
            }

        template <typename... Iters>
            typename _product<Iters...>::iterator
            _product<Iters...>::end() const
            {
                return end_iter;
            }

        template <typename... Iter>
            auto product(Iter &&... iters)
            -> _product< typename std::remove_cv<typename std::remove_reference<Iter>::type>::type...>
            {
                return {std::forward<Iter>(iters)...};
            }

        PROXY_IMPL(pythonic::itertools, product);

    }

}

#endif

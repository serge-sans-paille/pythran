#ifndef PYTHONIC_ITERTOOLS_PRODUCT_HPP
#define PYTHONIC_ITERTOOLS_PRODUCT_HPP

#include "pythonic/itertools/common.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic {

    namespace itertools {

        template <typename ResultType, typename... Iters>
            struct product_iterator : std::iterator< std::forward_iterator_tag, ResultType >  {

                template <typename... It>
                    struct product_iterator_data;

                template <typename L0, typename... It>
                    struct product_iterator_data<L0, It...>
                    {
                        typedef typename std::remove_cv<typename std::remove_reference<L0>::type>::type sequence_type;
                        typename sequence_type::iterator iter;
                        typename sequence_type::iterator iter_begin;
                        typename sequence_type::iterator iter_end;
                        product_iterator_data<It...> rec_iters; 

                        product_iterator_data() {}
                        product_iterator_data(L0 _seq, It... _iters) : iter(const_cast<sequence_type&>(_seq).begin()), iter_begin(const_cast<sequence_type&>(_seq).begin()), iter_end(const_cast<sequence_type&>(_seq).end()), rec_iters(_iters...) {
                        }
                        product_iterator_data(npos, L0 _seq, It... _iters) : iter(const_cast<sequence_type &>(_seq).end()), iter_begin(const_cast<sequence_type&>(_seq).begin()), iter_end(const_cast<sequence_type&>(_seq).end()), rec_iters(npos(), _iters...) {
                        }

                        bool next_value() {
                            if (rec_iters.next_value()) {
                                ++iter;
                                if (!(iter != iter_end)) {
                                    iter = iter_begin;
                                    return true;
                                }
                            }
                            return false;
                        }

                        template<typename... Types> 
                            auto get_value(Types const&... params) const -> decltype(rec_iters.get_value(params..., *iter)) {
                                return rec_iters.get_value(params..., *iter);
                            }

                        long operator-(product_iterator_data<L0, It...> const& other) const {
                            return (iter - other.iter) * (rec_iters - other.rec_iters);
                        }

                    };

                template<typename L0>
                    struct product_iterator_data<L0>
                    {
                        //L0 seq;
                        typedef typename std::remove_cv<typename std::remove_reference<L0>::type>::type sequence_type;
                        typename sequence_type::iterator iter;
                        typename sequence_type::iterator iter_begin;
                        typename sequence_type::iterator iter_end;

                        product_iterator_data() {}
                        product_iterator_data(L0 _seq) : iter(const_cast<sequence_type &>(_seq).begin()), iter_begin(const_cast<sequence_type&>(_seq).begin()), iter_end(const_cast<sequence_type&>(_seq).end()) {
                        }
                        product_iterator_data(npos, L0 _seq) : iter(const_cast<sequence_type &>(_seq).end()), iter_begin(const_cast<sequence_type&>(_seq).begin()), iter_end(const_cast<sequence_type&>(_seq).end()) {
                        }

                        bool next_value() {
                            ++iter;
                            if (!(iter != iter_end)) {
                                iter = iter_begin;
                                return true;
                            }
                            return false;
                        }

                        template<typename... Types>
                            auto get_value(Types const&... params) const ->decltype(std::make_tuple(params..., *iter)) {
                                return std::make_tuple(params..., *iter);
                            }

                        long operator-(product_iterator_data<L0> const& other) const {
                            return iter - other.iter;
                        }

                    };

                product_iterator_data<Iters...> it_data;
                bool end;

                product_iterator() {}
                product_iterator(Iters... _iters)  : it_data(_iters...), end(false) {
                }
                product_iterator(npos, Iters... _iters)  : it_data(npos(), _iters...), end(true) {
                }

                decltype(it_data.get_value()) operator*() const {
                    return it_data.get_value();
                }

                product_iterator& operator++() { 
                    end = it_data.next_value();
                    return *this; 
                }

                bool operator==(product_iterator const& other) const { 
                    return (end == other.end);
                }

                bool operator!=(product_iterator const& other) const { 
                    return end != other.end;
                }

                bool operator<(product_iterator const& other) const {
                    return end != other.end;                       
                }

                long operator-(product_iterator const& other) const {
                    return it_data - other.it_data;
                }

            };


        template <typename... Iters>
            struct _product : product_iterator<decltype(std::make_tuple((*std::declval<Iters>().begin())...)), Iters...> {

                typedef decltype(std::make_tuple((*std::declval<Iters>().begin())...)) value_type;
                typedef product_iterator<value_type, Iters...> iterator;

                std::tuple<Iters ...> iters;

                iterator end_iter;


                _product() {}
                _product(Iters... _iters) : iterator(_iters...), iters(_iters...), end_iter(npos(), _iters...) {
                }

                iterator& begin() { return *this; }
                iterator const& begin() const { return *this; }
                iterator end() const { return end_iter; }

            };

        template <typename... Iter>
            auto product(Iter &&... iters) -> _product< typename std::remove_cv<typename std::remove_reference<Iter>::type>::type...> {
                return _product<typename std::remove_cv<typename std::remove_reference<Iter>::type>::type...> ( std::forward<Iter>(iters)...);
            }

        PROXY(pythonic::itertools,product);

    }

}

#endif

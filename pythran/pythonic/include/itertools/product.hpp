#ifndef PYTHONIC_INCLUDE_ITERTOOLS_PRODUCT_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_PRODUCT_HPP

#include "pythonic/itertools/common.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic {

    namespace itertools {

        template <typename ResultType, typename... Iters>
            struct product_iterator : std::iterator<std::forward_iterator_tag,
                                                    ResultType >
            {

                template <typename... It>
                    struct product_iterator_data;

                template <typename L0, typename... It>
                    struct product_iterator_data<L0, It...>
                    {
                        using sequence_type = typename std::remove_cv<typename std::remove_reference<L0>::type>::type;

                        typename sequence_type::iterator iter;
                        typename sequence_type::iterator iter_begin;
                        typename sequence_type::iterator iter_end;
                        product_iterator_data<It...> rec_iters; 

                        product_iterator_data();
                        product_iterator_data(L0 _seq, It... _iters);
                        product_iterator_data(npos, L0 _seq, It... _iters);

                        bool next_value();

                        template<typename... Types> 
                            auto get_value(Types const&... params) const
                            -> decltype(rec_iters.get_value(params..., *iter));

                        long operator-(product_iterator_data<L0, It...> const& other) const;
                    };

                template<typename L0>
                    struct product_iterator_data<L0>
                    {
                        //L0 seq;
                        using sequence_type = typename std::remove_cv<typename std::remove_reference<L0>::type>::type;

                        typename sequence_type::iterator iter;
                        typename sequence_type::iterator iter_begin;
                        typename sequence_type::iterator iter_end;

                        product_iterator_data();
                        product_iterator_data(L0 _seq);
                        product_iterator_data(npos, L0 _seq);

                        bool next_value();

                        template<typename... Types>
                            auto get_value(Types const&... params) const
                            -> decltype(std::make_tuple(params..., *iter));

                        long operator-(product_iterator_data<L0> const& other) const;
                    };

                product_iterator_data<Iters...> it_data;
                bool end;

                product_iterator();
                product_iterator(Iters... _iters);
                product_iterator(npos, Iters... _iters);

                auto operator*() const -> decltype(this->it_data.get_value());
                product_iterator& operator++();
                bool operator==(product_iterator const& other) const;
                bool operator!=(product_iterator const& other) const;
                bool operator<(product_iterator const& other) const;
                long operator-(product_iterator const& other) const;
            };

        template <typename... Iters>
            struct _product : product_iterator<decltype(std::make_tuple((*std::declval<Iters>().begin())...)), Iters...>
            {
                using value_type = decltype(std::make_tuple((*std::declval<Iters>().begin())...));
                using iterator = product_iterator<value_type, Iters...>;

                std::tuple<Iters ...> iters;

                iterator end_iter;

                _product();
                _product(Iters... _iters);

                iterator& begin();
                iterator const& begin() const;
                iterator end() const;
            };

        template <typename... Iter>
            _product< typename std::remove_cv<typename std::remove_reference<Iter>::type>::type...>
            product(Iter &&... iters);

        PROXY_DECL(pythonic::itertools, product);

    }

}

#endif

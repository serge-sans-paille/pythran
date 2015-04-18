#ifndef PYTHONIC_INCLUDE_ITERTOOLS_IFILTER_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_IFILTER_HPP

#include "pythonic/types/none.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/itertools/common.hpp"

#include <iterator>
#include <type_traits>


namespace pythonic {

    namespace itertools {

        template <typename ResultType, typename Operator, typename List0>
            struct ifilter_iterator : std::iterator< std::forward_iterator_tag, ResultType >
            {
                using sequence_type = typename std::remove_cv<typename std::remove_reference<List0>::type>::type;

                Operator op;
                typename List0::iterator iter;
                typename List0::iterator iter_end;

                bool test_filter(std::false_type);
                bool test_filter(std::true_type);

                ifilter_iterator();
                ifilter_iterator(Operator _op, List0 _seq);
                ifilter_iterator(npos, Operator _op, List0 _seq);

                ResultType operator*() const;

                ifilter_iterator& operator++();
                void next_value();

                bool operator==(ifilter_iterator const& other) const;
                bool operator!=(ifilter_iterator const& other) const;
                bool operator<(ifilter_iterator const& other) const;
                int operator-(ifilter_iterator const& other) const;
            };

        template <typename ResultType, typename Operator, typename List0>
            struct _ifilter : ifilter_iterator<ResultType, Operator, List0>
            {

                using iterator = ifilter_iterator<ResultType, Operator, List0>;
                using value_type = ResultType;

                List0 seq; // to make sure we keep a reference on all the containers
                iterator end_iter;

                _ifilter();
                _ifilter(Operator _op, List0 _seq);

                iterator& begin();
                iterator const& begin() const;
                iterator const& end() const;
            };

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
            ifilter(types::none_type _op, List0&& _seq);

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
                >;

        PROXY_DECL(pythonic::itertools, ifilter);

    }

}
#endif

#ifndef ITERTOOLS_H

#define ITERTOOLS_H

#include <type_traits>

namespace pythonic {

    namespace itertools {
         struct npos {};


        template <typename ResultType, typename Operator, typename... Iters>
            struct imap_iterator : std::iterator< std::random_access_iterator_tag, ResultType >  {

                template <typename Op, typename... It>
                    struct imap_iterator_data;

                template <typename Op, typename L0, typename... It>
                    struct imap_iterator_data<Op, L0, It...>
                    {
                        typedef typename std::remove_cv<typename std::remove_reference<L0>::type>::type sequence_type;
                        typename std::remove_reference<L0>::type::iterator iter;
                        imap_iterator_data<Op,It...> rec_iters; 

                        imap_iterator_data() {}
                        imap_iterator_data(Op _op, L0 _seq, It... _iters) : iter(const_cast<sequence_type&>(_seq).begin()), rec_iters(_op, _iters...) {
                        }
                        imap_iterator_data(npos, Op _op, L0 _seq, It... _iters) : iter(const_cast<sequence_type &>(_seq).end()), rec_iters(npos(), _op, _iters...) {
                        }

                        template<typename... Types> 
                            auto next_value(Types ... params) -> decltype(rec_iters.next_value(params..., *(iter))) {
                                return rec_iters.next_value(params..., *iter);
                            }

                        bool operator==(imap_iterator_data const& other) {
                            return !(iter != other.iter) && (rec_iters == other.rec_iters); 
                        }

                        bool operator!=(imap_iterator_data const& other) {
                            return (iter != other.iter) || (rec_iters != other.rec_iters); 
                        }

                        int operator-(imap_iterator_data const& other) {
                            return (iter != other.iter);
                        }

                        imap_iterator_data<Op, L0, It...>& operator++() {
                            ++iter;
                            ++rec_iters;
                        }

                    };

                template<typename Op, typename L0>
                    struct imap_iterator_data<Op, L0>
                    {
                        Op op;
                        typedef typename std::remove_cv<typename std::remove_reference<L0>::type>::type sequence_type;
                        typename std::remove_reference<L0>::type::iterator iter;

                        imap_iterator_data() {}
                        imap_iterator_data(Op _op, L0 _seq) : op(_op), iter(const_cast<sequence_type &>(_seq).begin()) {
                        }
                        imap_iterator_data(npos, Op _op, L0 _seq) : op(_op), iter(const_cast<sequence_type &>(_seq).end()) {
                        }

                        template<typename... Types, typename O = Op, typename = typename std::enable_if<!std::is_same<pythonic::none_type, O>::value, O>::type>
                            auto next_value(Types ... params) -> decltype(op(params..., *iter)) {
                                return op(params..., *iter);
                            }

                        template<typename... Types, typename O = Op, typename = typename std::enable_if<std::is_same<pythonic::none_type, O>::value, O>::type>
                            auto next_value(Types ... params) -> decltype(std::make_tuple(params..., *iter)) {
                                return std::make_tuple(params..., *iter);
                            }

                        bool operator==(imap_iterator_data const& other) {
                            return !(iter != other.iter); 
                        }

                        bool operator!=(imap_iterator_data const& other) {
                            return (iter != other.iter); 
                        }

                        int operator-(imap_iterator_data const& other) {
                            return (iter != other.iter) ? 1 : 0;
                        }

                        imap_iterator_data<Op, L0>& operator++() {
                            ++iter;
                        }

                    };

                imap_iterator_data<Operator, Iters...> it_data;
                //decltype(it_data.next_value()) value;

                // Incrementation of iterator currently fail if the iterator
                // is assigned before being returned. This quick fix ensure
                // that the iterator is assigned after being returned.

                imap_iterator() {}
                imap_iterator(Operator _op, Iters... _iters)  : it_data(_op, _iters...) {
                }
                imap_iterator(npos, Operator _op, Iters... _iters)  : it_data(npos(), _op, _iters...) {
                }

                decltype(it_data.next_value()) operator*() { 
                    return it_data.next_value(); //value; 
                }

                imap_iterator& operator++() { 
                    ++it_data;
                    return *this; 
                }

                bool operator==(imap_iterator const& other) { 
                    return it_data == other.it_data; 
                }

                bool operator!=(imap_iterator const& other) { 
                    return it_data != other.it_data; 
                }

                bool operator<(imap_iterator const& other) {
                    return it_data != other.it_data; 
                }

                int operator-(imap_iterator const& other) {
                    return it_data - other.it_data;
                }

            };


        template <typename ResultType, typename Operator, typename... Iters>
            struct _imap{

                typedef imap_iterator<ResultType, Operator, Iters...> iterator;

                std::tuple<typename std::remove_cv<typename std::remove_reference<Iters>::type>::type ...> iters; // to make sure we keep a reference on all the containers
                iterator iter;
                iterator end_iter;

                typedef ResultType value_type;

                _imap() {}
                _imap(Operator _op, Iters... _iters) : iters(_iters...), iter(_op, _iters...), end_iter(npos(), _op, _iters...) {
                }

                iterator begin() const { return iter; }
                iterator end() const { return end_iter; }

            };

        template <typename... Iter>
            auto imap(pythonic::none_type _op, Iter && ... iters) -> _imap< decltype(std::make_tuple((*iters.begin())...)), pythonic::none_type, Iter...> {
                return _imap<decltype(std::make_tuple((*iters.begin())...)), pythonic::none_type, Iter...> (std::forward<pythonic::none_type>(_op), std::forward<Iter>(iters)...);
            }

        template <typename Operator, typename... Iter>
            auto imap(Operator&& _op, Iter && ... iters) -> _imap< decltype(_op( (*iters.begin())...)), Operator, Iter...> {
                return _imap<decltype(_op((*iters.begin())...)), Operator, Iter...> (std::forward<Operator>(_op), std::forward<Iter>(iters)...);
            }

        PROXY(pythonic::itertools,imap);

        template <typename ResultType, typename Operator, typename List0>
            struct ifilter_iterator : std::iterator< std::random_access_iterator_tag, ResultType >  {

                List0 seq;
                Operator op;
                typename List0::iterator iter;
                ResultType val;
                // Incrementation of iterator currently fail if the iterator
                // is assigned before being returned. This quick fix ensure
                // that the iterator is assigned after being returned.
                bool init;  //cf next_value

                ifilter_iterator() {}
                ifilter_iterator(Operator _op, List0 _seq) : op(_op), seq(_seq), init(false) {
                    //iter = seq.begin(); //cf init
                }

                ResultType& operator*() { 
                    if (!init) { //cf init
                        iter = seq.begin();
                        val = next_value();
                        init = true;
                    }

                    return val; 
                }

                ifilter_iterator& operator++() { 
                    if (iter != seq.end()) {
                        ++iter;
                        val = next_value(); //cf next_value
                    }
                    return *this; 
                }

                bool operator!=(ifilter_iterator const& other) { 
                    if ( !init || !other.init) {//cf next_value
                        return true;
                    }
                    return iter != other.iter; 
                }

                bool operator<(ifilter_iterator const& other) {
                    if ( !init || !other.init) {//cf next_value
                        return true;
                    }
                    return iter != other.iter; 
                }

                bool test_filter(std::false_type) {
                    return op(*iter);
                }

                bool test_filter(std::true_type) {
                    return *iter;
                }

                ResultType next_value() {
                    while (iter != seq.end()) {
                        if (test_filter(std::is_same<pythonic::none_type, Operator>())) {
                            return *iter;
                        } else
                            ++iter;
                    }
                }

                void set_end() {
                    iter = seq.end();
                    init = true; //cf. next_value
                }

            };

        template <typename ResultType, typename Operator, typename List0>
            struct _ifilter{

                typedef ifilter_iterator<ResultType, Operator, List0> iterator;

                iterator iter;
                iterator end_iter;

                _ifilter() {}
                _ifilter(Operator&& _op, List0&& _seq) {
                    iter = iterator(_op, _seq);
                    end_iter = iterator(_op, _seq);
                    end_iter.set_end();
                }
                _ifilter(Operator&& _op, const List0&& _seq) {
                    iter = iterator(_op, _seq);
                    end_iter = iterator(_op, _seq);
                    end_iter.set_end();
                }

                iterator begin() {  return iter; }
                iterator end() {  return end_iter; }

            };

        template <typename List0>
            auto ifilter(pythonic::none_type _op, List0&& _seq) -> _ifilter< bool, pythonic::none_type, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> {
                return _ifilter<bool, pythonic::none_type, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> (std::forward<pythonic::none_type>(_op), std::forward<typename std::remove_reference<List0>::type>(_seq));
            }

        template <typename Operator, typename List0>
            auto ifilter(Operator&& _op, List0&& _seq) -> _ifilter< typename std::remove_cv<typename std::remove_reference<decltype(*_seq.begin())>::type>::type, Operator, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> {
                return _ifilter<typename std::remove_cv<typename std::remove_reference<decltype(*_seq.begin())>::type>::type, Operator, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> (std::forward<Operator>(_op), std::forward<typename std::remove_reference<List0>::type>(_seq));
            }

        PROXY(pythonic::itertools,ifilter);

        template <typename ResultType, typename... Iters>
            struct product_iterator : std::iterator< std::random_access_iterator_tag, ResultType >  {

                template <typename... It>
                    struct product_iterator_data;

                template <typename L0, typename... It>
                    struct product_iterator_data<L0, It...>
                    {
                        L0 seq;
                        typename L0::iterator iter;
                        product_iterator_data<It...> rec_iters; 

                        product_iterator_data() {}
                        product_iterator_data(L0 _seq, It const&... _iters) : seq(_seq) {
                            //iter = seq.begin(); //cf. product_iterator.init
                            rec_iters = product_iterator_data<It...>(_iters...);
                        }

                        bool next_value() {
                            if (rec_iters.next_value()) {
                                ++iter;
                                if (!(iter != seq.end())) {
                                    iter = seq.begin();
                                    return true;
                                }
                            }
                            return false;
                        }

                        template<typename... Types> 
                            auto get_value(Types const&... params) -> decltype(rec_iters.get_value(params..., *iter)) {
                                return rec_iters.get_value(params..., *iter);
                            }

                        void init() { //cf. product_iterator.init
                            iter = seq.begin();
                            rec_iters.init();
                        }

                    };

                template<typename L0>
                    struct product_iterator_data<L0>
                    {
                        L0 seq;
                        typename L0::iterator iter;

                        product_iterator_data() {}
                        product_iterator_data(L0 const& _seq) : seq(_seq) {
                            //iter = seq.begin(); //cf. product_iterator.init
                        }

                        bool next_value() {
                            ++iter;
                            if (!(iter != seq.end())) {
                                iter = seq.begin();
                                return true;
                            }
                            return false;
                        }

                        template<typename... Types>
                            auto get_value(Types const&... params) ->decltype(std::make_tuple(params..., *iter)) {
                                return std::make_tuple(params..., *iter);
                            }

                        void init() { //cf. product_iterator.init
                            iter = seq.begin();
                        }

                    };

                product_iterator_data<Iters...> it_data;
                decltype(it_data.get_value()) value;
                // Incrementation of iterator currently fail if the iterator
                // is assigned before being returned. This quick fix ensure
                // that the iterator is assigned after being returned.
                bool init;
                bool end;

                product_iterator() {}
                product_iterator(Iters const&... _iters) : init(false), end(false)  {
                    it_data = product_iterator_data<Iters...>(_iters...);
                }

                decltype(it_data.get_value())& operator*() {
                    if (!init) { //cf. init
                        it_data.init();
                        value = it_data.get_value();
                        init = true;
                    }
                    if (!end) {
                        value = it_data.get_value();
                    }
                    return value;
                }

                product_iterator& operator++() { 
                    end = it_data.next_value();
                    return *this; 
                }

                bool operator!=(product_iterator const& other) { 
                    return !init || !other.init || end != other.end;  //cf. init
                }

                bool operator<(product_iterator const& other) {
                    return !init || !other.init || end != other.end; //cf. init
                }

                int operator-(product_iterator const& other) {
                    return (end != other.end) ? 1 : 0;
                }

                void set_end() {
                    init = true; //cf. init
                    end = true;
                }

            };


        template <typename ResultType, typename... Iters>
            struct _product{

                typedef product_iterator<ResultType, Iters...> iterator;

                iterator iter;
                iterator end_iter;

                _product() {}
                _product(Iters const&... _iters) {
                    iter = iterator(_iters...);
                    end_iter = iterator(_iters...);
                    end_iter.set_end();
                }

                iterator begin() const { 
                    return iter; }
                iterator end() const { 
                    return end_iter; }

            };

        template <typename... Iter>
            auto product(Iter const&... iters) -> _product< decltype(std::make_tuple((*iters.begin())...)), Iter...> {
                return _product<decltype(std::make_tuple((*iters.begin())...)), Iter...> ( iters...);
            }

        PROXY(pythonic::itertools,product);

        template <typename... Iter>
            auto izip(Iter &&... iters) -> decltype(imap(None, std::forward<Iter>(iters)...)) {
                return imap(None, std::forward<Iter>(iters)...);
            }

        PROXY(pythonic::itertools,izip);

    }
}

#endif

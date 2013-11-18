#ifndef ITERTOOLS_H

#define ITERTOOLS_H

#include <type_traits>

namespace pythonic {

    namespace itertools {

        struct npos {};

        template <typename ResultType, typename Operator, typename... Iters>
            struct imap_iterator : std::iterator< typename pythonic::min_iterator<typename std::remove_reference<Iters>::type::iterator...>::type , ResultType, ptrdiff_t, ResultType*, ResultType /* no ref */ >  {

                template <typename Op, typename... It>
                    struct imap_iterator_data;

                template <typename Op, typename L0, typename... It>
                    struct imap_iterator_data<Op, L0, It...>
                    {
                        typedef typename std::remove_cv<typename std::remove_reference<L0>::type>::type sequence_type;
                        imap_iterator_data<Op,It...> rec_iters; 
                        sequence_type iterator_ref;  // keep value of iterable to avoid dangling reference
                        typename sequence_type::iterator iter;

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

                        template<typename... Types, typename O = Op, typename = typename std::enable_if<!std::is_same<pythonic::none_type, O>::value, O>::type>
                            auto next_value(Types&& ... params) const
                            -> decltype(op(std::forward<Types>(params)..., *iter))
                            {
                                return op(std::forward<Types>(params)..., *iter);
                            }
                        template<typename... Types, typename O = Op, typename = typename std::enable_if<std::is_same<pythonic::none_type, O>::value, O>::type>
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
            auto imap(pythonic::none_type _op, Iter && ... iters)
            -> _imap< decltype(std::make_tuple((*iters.begin())...)), pythonic::none_type, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...>
            {
                return _imap<decltype(std::make_tuple((*iters.begin())...)), pythonic::none_type, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...> (std::forward<pythonic::none_type>(_op), std::forward<Iter>(iters)...);
            }

        template <typename Operator, typename... Iter>
            auto imap(Operator&& _op, Iter && ... iters)
            -> _imap< decltype(_op( (*iters.begin())...)), Operator, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...>
            {
                return _imap<decltype(_op((*iters.begin())...)), Operator, typename std::remove_cv<typename std::remove_reference<Iter>::type>::type ...> (std::forward<Operator>(_op), std::forward<Iter>(iters)...);
            }

        PROXY(pythonic::itertools,imap);

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
                    if (!test_filter(std::is_same<pythonic::none_type, Operator>()))
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
                        if (test_filter(std::is_same<pythonic::none_type, Operator>()))
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
            auto ifilter(pythonic::none_type _op, List0&& _seq) -> _ifilter< typename std::remove_cv<typename std::remove_reference<List0>::type>::type::value_type, pythonic::none_type, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> {
                return _ifilter<typename std::remove_cv<typename std::remove_reference<List0>::type>::type::value_type, pythonic::none_type, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> (std::forward<pythonic::none_type>(_op), std::forward<List0>(_seq));
            }

        template <typename Operator, typename List0>
            auto ifilter(Operator&& _op, List0&& _seq) -> _ifilter< typename std::remove_cv<typename std::remove_reference<decltype(*_seq.begin())>::type>::type, Operator, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> {
                return _ifilter<typename std::remove_cv<typename std::remove_reference<decltype(*_seq.begin())>::type>::type, Operator, typename std::remove_cv<typename std::remove_reference<List0>::type>::type> (std::forward<Operator>(_op), std::forward<List0>(_seq));
            }

        PROXY(pythonic::itertools,ifilter);

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

        template <typename... Iter>
            auto izip(Iter &&... iters) -> decltype(imap(__builtin__::None, std::forward<Iter>(iters)...)) {
                return imap(__builtin__::None, std::forward<Iter>(iters)...);
            }

        PROXY(pythonic::itertools,izip);

        template <typename Iterable>
            struct islice_iterator : std::iterator< typename Iterable::iterator::iterator_category, typename Iterable::iterator::value_type > {
                typename std::remove_reference<typename std::remove_cv<Iterable>::type>::type iterable_ref;
                typename std::remove_reference<typename std::remove_cv<Iterable>::type>::type::iterator iterable;
                __builtin__::xrange xr_ref;
                __builtin__::xrange_iterator state;
                __builtin__::xrange_iterator::value_type prev;

                islice_iterator() {}
                islice_iterator(Iterable const & iterable, __builtin__::xrange const& xr): xr_ref(xr), iterable_ref(iterable), iterable(iterable_ref.begin()), state(xr_ref.begin()), prev(*state) {
                    std::advance(this->iterable, *state);
                }
                islice_iterator(npos const& n, Iterable const & iterable, __builtin__::xrange const& xr): xr_ref(xr), iterable_ref(iterable), iterable(iterable_ref.begin()), state(xr_ref.end()), prev(0) {}

                typename Iterable::value_type operator*() const {
                    return *iterable;
                }

                islice_iterator& operator++() { 
                    ++state;
                    std::advance(this->iterable, *state-prev);
                    prev = *state;
                    return *this; 
                }

                bool operator==(islice_iterator const& other) const { 
                    return (state == other.state);
                }

                bool operator!=(islice_iterator const& other) const { 
                    return state != other.state;
                }

                bool operator<(islice_iterator const& other) const {
                    return state != other.state;                       
                }

                int operator-(islice_iterator const& other) const {
                    return state - other.state;
                }

            };


        template <typename Iterable>
            struct _islice : islice_iterator<Iterable> {

                typedef islice_iterator<Iterable> iterator;
                typedef typename Iterable::value_type value_type;

                iterator end_iter;

                _islice() {}
                _islice(Iterable const& iterable, __builtin__::xrange const& xr) : iterator(iterable, xr), end_iter(npos(), iterable, xr) {
                }

                iterator& begin() { return *this; }
                iterator const& begin() const { return *this; }
                iterator end() const { return end_iter; }

            };

        template <typename Iterable>
            _islice<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type> islice(Iterable&& iterable, long start, long stop, long step=1) {
                return _islice<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>(iterable, __builtin__::xrange(start, stop, step));
            }
        template <typename Iterable>
            _islice<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type> islice(Iterable&& iterable, long stop) {
                return _islice<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>(iterable, __builtin__::xrange(0, stop, 1));
            }

        PROXY(pythonic::itertools, islice);

        template<class T>
        struct count_iterator : std::iterator< std::random_access_iterator_tag, T > {
            T value;
            T step;
            count_iterator() {}
            count_iterator(T value, T step) : value(value), step(step) {}
            T operator*() const { return value;}
            count_iterator& operator++() { value+=step; return *this;}
            count_iterator& operator+=(long n) { value+=step*n; return *this; }
            bool operator!=(count_iterator const& other) const { return value != other.value; }
            bool operator==(count_iterator const& other) const { return value == other.value; }
            bool operator<(count_iterator const& other) const { return value < other.value; }
            long operator-(count_iterator const& other) const { return (value - other.value)/step; }

        };

        template<class T>
            struct _count :  count_iterator<T> {
                typedef T value_type;
                typedef count_iterator<T> iterator;
                _count() {}
                _count(T value, T step) : count_iterator<T>(value, step) {}
                iterator& begin() { *this; }
                iterator const& begin() const { *this; }
                iterator end() const { return count_iterator<T>(std::numeric_limits<T>::max(), count_iterator<T>::step); }
            };

        template <typename T0, typename T1=T0>
            _count<decltype(std::declval<T0>()+std::declval<T1>())> count(T0 start, T1 step=1) {
                return _count<decltype(std::declval<T0>()+std::declval<T1>())>(start, step);
            }

            _count<long> count() {
                return _count<long>(0, 1);
            }
        PROXY(pythonic::itertools, count);

        template<class T>
        struct combination_iterator : std::iterator< std::forward_iterator_tag,
                                                     core::list<typename T::value_type>,
                                                     ptrdiff_t,
                                                     core::list<typename T::value_type>*,
                                                     core::list<typename T::value_type> /*no ref*/
                                                   >
        {
            std::vector<typename T::value_type> iterable;
            std::vector<bool> curr_permut;
            bool end;
            combination_iterator() {}
            combination_iterator(std::vector<typename T::value_type> const& iter, int num_elts, bool end) : iterable(iter), end(end)
            {
                curr_permut.resize(iterable.size());
                std::fill(curr_permut.begin() + num_elts, curr_permut.end(), true);
            }
            core::list<typename T::value_type> operator*() const {
                core::list<typename T::value_type> res(0);
                int i=0;
                for(auto const& iter : iterable)
                {
                    if(!curr_permut[i++])
                        res.push_back(iter);
                }
                return res;
            }
            combination_iterator& operator++()
            {
                end = std::next_permutation(curr_permut.begin(), curr_permut.end());
                return *this;
            }
            bool operator!=(combination_iterator const& other) const
            {
                return !(*this==other);
            }
            bool operator==(combination_iterator const& other) const
            {
                if(other.end != end)
                    return false;
                return std::equal(curr_permut.begin(), curr_permut.end(), other.curr_permut.begin());
            }
            bool operator<(combination_iterator const& other) const
            {
                if(end!=other.end)
                    return end>other.end;
                for(int i=0; i<iterable.size(); i++)
                    if(other.curr_permut[i] < curr_permut[i])
                        return false;
                    else if(other.curr_permut[i] > curr_permut[i])
                        return true;
                return false;
            }
        };

        template<class T>
            struct _combination: combination_iterator<T> {
                typedef T value_type;
                typedef combination_iterator<T> iterator;
                size_t num_elts;
                _combination() {}
                _combination(T iter, int elts): iterator(std::vector<typename T::value_type>(iter.begin(), iter.end()), elts, true), num_elts(elts){}
                iterator const& begin() const {
                    return *this;
                }
                iterator begin() {
                    return *this;
                }
                iterator end() const {
                    return combination_iterator<T>(combination_iterator<T>::iterable, num_elts, false);
                }
            };

        template <typename T0>
            _combination<T0> combinations(T0 iter, int num_elts) {
                return _combination<T0>(iter, num_elts);
            }

        PROXY(pythonic::itertools, combinations);

        /** Permutation iterator
         *
         *  It wraps a vector and provide an iteration over every possible
         *  permutation of the vector. The permutations are represented as lists
         *  of elements.
         *
         *  The following iterator:
         *
         *  permutations_iterator([0, 1, 2])
         *
         *  yelds the following suite:
         *
         *  [(0, 1, 2), (0, 2, 1), (1, 0, 2), (1, 2, 0), (2, 0, 1), (2, 1, 0)]
         *
         */
        template<class T>
        struct permutations_iterator :
                std::iterator< std::forward_iterator_tag,
                               core::list<typename T::value_type>,
                               ptrdiff_t,
                               core::list<typename T::value_type>*,
                               core::list<typename T::value_type> /* no ref*/
                             > {
            // Vector of inputs, contains elements to permute
            std::vector<typename T::value_type> pool;

            // The current permutation as a list of index in the pool
            // Internally it always has the same size as the pool, even if the
            // external view is limited
            core::list<int> curr_permut;

            // Size of the "visible" permutation
            size_t size;
            bool end; // sentinel marker

            permutations_iterator() {}
            permutations_iterator(std::vector<typename T::value_type> const& iter,
                                  int num_elts,
                                  bool end) :
                    pool(iter), size(num_elts), end(end),
                    curr_permut(__builtin__::range(pool.size())) {
                if(num_elts > iter.size()) {
                    end = true;
                }
            }

            /** Build the permutation visible from the "outside" */
            core::list<typename T::value_type> operator*() const {
                core::list<typename T::value_type> res(size);
                for(int i =0; i<size; i++)
                {
                    res[i] = pool[curr_permut[i]]; // Ok because core::list is indeed a vector
                }
                return res;
            }
            /*  Generate next permutation
             *
             *  If the size of the permutation is smaller than the size of the
             *  pool, we may have to iterate multiple times
             */
            permutations_iterator& operator++()
            {
                if(size!=pool.size()) {
                    // Slow path, the iterator is a "view" of a prefix smaller
                    // than the the pool size
                    // FIXME a better implementation would be to avoid
                    // std::next_permutation, but only in the slow path
                    core::list<int> prev_permut(curr_permut.begin(),
                                                curr_permut.begin()+size);
                    core::list<int> new_permut;
                    while((end = std::next_permutation(curr_permut.begin(),
                                                    curr_permut.end()))) {
                        // Check if the prefix of the new permutation is
                        // different of the previous one
                        core::list<int> new_permut(curr_permut.begin(),
                                                   curr_permut.begin()+size);
                        if(!(prev_permut==new_permut)) break;
                    }
                } else {
                    end = std::next_permutation(curr_permut.begin(),
                                                curr_permut.end());
                }
                return *this;
            }
            bool operator!=(permutations_iterator const& other) const
            {
                return !(*this==other);
            }
            bool operator==(permutations_iterator const& other) const
            {
                if(other.end != end)
                    return false;
                return std::equal(curr_permut.begin(), curr_permut.end(), other.curr_permut.begin());
            }
            bool operator<(permutations_iterator const& other) const
            {
                if(end!=other.end)
                    return end>other.end;
                for(int i=0; i<pool.size(); i++)
                    if(other.curr_permut[i] < curr_permut[i])
                        return false;
                    else if(other.curr_permut[i] > curr_permut[i])
                        return true;
                return false;
            }
        };

        template<class T>
            // FIXME document why this inheritance???
            struct _permutations: permutations_iterator<T> {
                typedef T value_type;
                typedef permutations_iterator<T> iterator;
                _permutations() {}
                _permutations(T iter, int elts) :
                        iterator(std::vector<typename T::value_type>(iter.begin(),
                                                                     iter.end()),
                                 elts,
                                 true) {}

                iterator const& begin() const {
                    return *this;
                }
                iterator begin() {
                    return *this;
                }
                iterator end() const {
                    return iterator(iterator::pool, iterator::size, false);
                }
            };

        template <typename T0>
            _permutations<T0> permutations(T0 iter, int num_elts) {
                return _permutations<T0>(iter, num_elts);
            }

        template <typename T0>
            _permutations<T0> permutations(T0 iter) {
                return _permutations<T0>(iter, std::distance(iter.begin(), iter.end()));
            }

        PROXY(pythonic::itertools, permutations);

    }
}

#endif

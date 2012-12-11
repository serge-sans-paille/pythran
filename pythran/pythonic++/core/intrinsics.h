#ifndef PYTHONIC_INTRINSICS_H
#define PYTHONIC_INTRINSICS_H

#include <tuple>
#include <sstream>
#include <complex>

namespace pythonic {

    /* abs */
    using std::abs;
    PROXY(pythonic, abs);

    /* all */
    template <class Iterable>
        bool all( Iterable && s) {
            //return s.end() == std::find_if(s.begin(), s.end(), [](typename Iterable::iterator::value_type const&t) { return not bool(t); });
            auto iend = s.end();
            for(auto iter = s.begin() ; iter != iend ; ++iter)
                if( not *iter ) return false;
            return true;
        }
    PROXY(pythonic, all);

    /* any */
    template <class Iterable>
        bool any( Iterable && s) {
            auto iend = s.end();
            for(auto iter = s.begin() ; iter != iend ; ++iter)
                if( *iter ) return true;
            return false;
        }
    PROXY(pythonic, any);

    /* bin */
    template<class T>
        core::string bin(T const &v) {
            long long unsigned int i = 1LL << (8*sizeof(T)-1);
            while(i and not (v&i)) i>>=1;
            if(not i) return "0b0";
            else {
                std::ostringstream oss;
                oss << "0b";
                for(; i ; i>>=1)
                    if(v & i) oss << "1";
                    else oss << "0";
                return oss.str();
            }
        }
    PROXY(pythonic, bin);

    /* chr */
    template<class T>
        core::string chr(T const &v) { return core::string((char)v); }
    PROXY(pythonic, chr);

    /* cmp */
    template<class T0, class T1>
        long cmp(T0 const& v0, T1 const& v1) {
            return v0 == v1 ? 0 : ( v0 < v1 ? -1 : 1 );
        }
    PROXY(pythonic, cmp);

    /* complex */
    template<class T0, class T1=double> // do not handle string as first argument
        std::complex<double> complex(T0 const& v0, T1 const& v1 = 0.) {
            return std::complex<double>(v0,v1);
        }
    PROXY(pythonic, complex);

    /* dict */
    core::empty_dict dict() {
        return core::empty_dict();
    }

    template<class Iterable>
        core::dict<typename std::tuple_element<0, typename std::remove_reference<Iterable>::type::iterator::value_type>::type ,
        typename std::tuple_element<1, typename std::remove_reference<Iterable>::type::iterator::value_type>::type >
            dict( Iterable&& iterable) {
                core::dict<typename std::tuple_element<0, typename std::remove_reference<Iterable>::type::iterator::value_type>::type ,
                typename std::tuple_element<1, typename std::remove_reference<Iterable>::type::iterator::value_type>::type > out=core::empty_dict();
                for(auto const & i : iterable)
                    out[std::get<0>(i)] = std::get<1>(i);
                return out;
            }

    PROXY(pythonic,dict);

    /* divmod */
    template<class T0, class T1>
        auto divmod(T0 const& t0, T1 const& t1) // other types are left over
        -> decltype(std::make_tuple(t0/t1, t0%t1)) {
            return std::make_tuple(t0/t1, t0%t1);
        }
    PROXY(pythonic, divmod);

    /* enumerate */
    template<class Iterable>
        struct enumerate_iterator : std::iterator< std::random_access_iterator_tag, std::tuple<long, typename Iterable::iterator::value_type> >{
            long value;
            typename Iterable::iterator iter;
            enumerate_iterator(){}
            enumerate_iterator(long value, typename Iterable::iterator iter) : value(value), iter(iter) {}
            std::tuple<long, typename Iterable::iterator::value_type> operator*() { return std::make_tuple(value, *iter); }
            enumerate_iterator& operator++() { ++value,++iter; return *this; }
            enumerate_iterator operator++(int) { enumerate_iterator self(*this); ++value, ++iter; return self; }
            enumerate_iterator& operator+=(long n) { value+=n,iter+=n; return *this; }
            bool operator!=(enumerate_iterator const& other) { return iter != other.iter; }
            bool operator<(enumerate_iterator const& other) { return iter < other.iter; }
            long operator-(enumerate_iterator const& other) { return iter - other.iter; }
        };

    template <class Iterable>
        struct _enumerate {
            typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type seq;
            _enumerate() {}
            typedef enumerate_iterator<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type> iterator;
            _enumerate( Iterable&& seq ) : seq(seq) {}
            iterator begin() { return iterator(0L, seq.begin()); }
            iterator end() { return iterator(-1L, seq.end()); }
        };

    template <class Iterable>
        _enumerate<Iterable> enumerate(Iterable && seq) { return _enumerate<Iterable>(std::forward<Iterable>(seq)); }

    PROXY(pythonic,enumerate);

    /* filter */
    template<class F, class Iterable>
        core::list<typename Iterable::iterator::value_type> filter(F const& f, Iterable const& iterable) { /* does not implement the full standard */
            core::list<typename Iterable::iterator::value_type> out;
            out=core::empty_list();
            std::copy_if(iterable.begin(), iterable.end(), std::back_inserter(out), f);
            return out;
        }

    PROXY(pythonic, filter);

    /* hex */
    template <class T>
        core::string hex(T const & v) {
            std::ostringstream oss;
            oss << "0x" << std::hex << v;
            return oss.str();
        }
    PROXY(pythonic, hex);

    /* id */
    template <class T>
        struct _id {
            intptr_t operator()(T const &t) {
                return reinterpret_cast<intptr_t>(&t);
            }
        };
    template <class T>
        struct _id< none<T> > {
            intptr_t operator()(none<T> const &t) {
                return t ? reinterpret_cast<intptr_t>(&t.data): reinterpret_cast<intptr_t>(&None);
            }
        };
    template <class T>
        struct _id< core::list<T> > {
            intptr_t operator()(core::list<T> const &t) {
                return reinterpret_cast<intptr_t>(&t.get_data());
            }
        };
    template <class T>
        struct _id< core::set<T> > {
            intptr_t operator()(core::set<T> const &t) {
                return reinterpret_cast<intptr_t>(&t.get_data());
            }
        };

    template <class T>
        intptr_t id(T const & t) {
            return _id<T>()(t);
        }
    PROXY(pythonic,id);

    /* in */
    template <class T, class V>
        struct _in {
            bool operator()(T const &t, V const &v) {
                return std::find(t.begin(), t.end(), v) != t.end();
            }
        };
    template <class K, class V>
        struct _in<core::dict<K,V>,K> {
            bool operator()(core::dict<K,V> const &t, K const &v) {
                return t.find(v) != t.item_end();
            }
        };
    template <class D, class I>
        struct _in<core::dict_items<D>,I> {
            bool operator()(core::dict_items<D> const &t, I const &v) {
                auto found = t.data.find(std::get<0>(v));
                return found != t.data.item_end() and std::get<1>(*found) == std::get<1>(v);
            }
        };
    template <class T, class V>
        bool in(T const &t, V const &v) {
            return _in<T,V>()(t,v);
        }
    template <class T, class V>
        bool in(core::set<T> const &t, V const &v) {
            return t.get_data().find(v) != t.end();
        }
    template <>
        bool in<core::string, core::string>(core::string const &t, core::string const &v) {
            return t.find(v) != core::string::npos;
        }
    PROXY(pythonic,in);


    /* len */

    template <class T, class I>
        struct _len {
            long operator()(T const &t) {
                static_assert(!std::is_same<I, std::random_access_iterator_tag>::value, "WTF");
                return 1;
            }
        };

    template <class T>
        struct _len<T, std::random_access_iterator_tag> {
            long operator()(T const &t) {
                return std::distance(t.begin(), t.end());
            }
        };

    template <class T, class I>
        struct _len<core::set<T>, I> {
            long operator()(core::set<T> const &t) {
                return t.size();
            }
        };

    template <class K, class V, class I>
        struct _len<core::dict<K,V>, I> {
            long operator()(core::dict<K,V> const &t) {
                return t.size();
            }
        };

    template <class... Types, class I>
        struct _len<std::tuple<Types...>, I> {
            long operator()(std::tuple<Types...> const&) {
                return sizeof...(Types);
            }
        };

    template <class T>
        long len(T const &t) {
            return _len<T, typename std::iterator_traits<typename T::iterator>::iterator_category>()(t);
        }
    PROXY(pythonic,len);

    /* list */
    core::empty_list list() {
        return core::empty_list();
    }
    core::empty_list list(core::empty_list) {
        return core::empty_list();
    }

    template <class Iterable>
        core ::list<typename std::remove_reference<Iterable>::type::iterator::value_type> list(Iterable && t) {
            return core::list<typename std::remove_reference<Iterable>::type::iterator::value_type>(t.begin(), t.end());
        } 

    PROXY(pythonic,list);

    /* exception */
#define PYTHONIC_EXCEPTION(name)\
    template<typename ... Types>\
    core::name name(Types ... args) {\
        return core::name(args ...);\
    }\
    \
    PROXY(pythonic,name);\

    PYTHONIC_EXCEPTION(BaseException);
    PYTHONIC_EXCEPTION(SystemExit);
    PYTHONIC_EXCEPTION(KeyboardInterrupt);
    PYTHONIC_EXCEPTION(GeneratorExit);
    PYTHONIC_EXCEPTION(Exception);
    PYTHONIC_EXCEPTION(StopIteration);
    PYTHONIC_EXCEPTION(StandardError);
    PYTHONIC_EXCEPTION(Warning);
    PYTHONIC_EXCEPTION(BytesWarning);
    PYTHONIC_EXCEPTION(UnicodeWarning);
    PYTHONIC_EXCEPTION(ImportWarning);
    PYTHONIC_EXCEPTION(FutureWarning);
    PYTHONIC_EXCEPTION(UserWarning);
    PYTHONIC_EXCEPTION(SyntaxWarning);
    PYTHONIC_EXCEPTION(RuntimeWarning);
    PYTHONIC_EXCEPTION(PendingDeprecationWarning);
    PYTHONIC_EXCEPTION(DeprecationWarning);
    PYTHONIC_EXCEPTION(BufferError);
    PYTHONIC_EXCEPTION(ArithmeticError);
    PYTHONIC_EXCEPTION(AssertionError);
    PYTHONIC_EXCEPTION(AttributeError);
    PYTHONIC_EXCEPTION(EOFError);
    PYTHONIC_EXCEPTION(ImportError);
    PYTHONIC_EXCEPTION(LookupError);
    PYTHONIC_EXCEPTION(MemoryError);
    PYTHONIC_EXCEPTION(NameError);
    PYTHONIC_EXCEPTION(ReferenceError);
    PYTHONIC_EXCEPTION(RuntimeError);
    PYTHONIC_EXCEPTION(SyntaxError);
    PYTHONIC_EXCEPTION(SystemError);
    PYTHONIC_EXCEPTION(TypeError);
    PYTHONIC_EXCEPTION(ValueError);
    PYTHONIC_EXCEPTION(FloatingPointError);
    PYTHONIC_EXCEPTION(OverflowError);
    PYTHONIC_EXCEPTION(ZeroDivisionError);
    PYTHONIC_EXCEPTION(IndexError);
    PYTHONIC_EXCEPTION(KeyError);
    PYTHONIC_EXCEPTION(UnboundLocalError);
    PYTHONIC_EXCEPTION(NotImplementedError);
    PYTHONIC_EXCEPTION(IndentationError);
    PYTHONIC_EXCEPTION(TabError);
    PYTHONIC_EXCEPTION(UnicodeError);
    PYTHONIC_EXCEPTION(EnvironmentError);
    PYTHONIC_EXCEPTION(IOError);
    PYTHONIC_EXCEPTION(OSError);

    /* tuple */
    template <class Iterable>
        struct _tuple {
            core::list<typename Iterable::value_type> operator()(Iterable i) {
                return core::list<typename Iterable::value_type>(i.begin(), i.end());
            }
        };

    template <class T>
        struct _tuple<core::list<T>> {
            core::list<T> operator()(core::list<T> i) {
                return core::list<T>(i.begin(), i.end());
            }
        };
    template <class Iterable> /* this is far from perfect, but how to cope with the difference between python tuples and c++ ones ? */
        core::list<typename Iterable::iterator::value_type> tuple(Iterable i) {
            return _tuple<Iterable>()(i);
        }
    PROXY(pythonic, tuple);

    /* set */
    core::empty_set set() {
        return core::empty_set();
    }

    template <class Iterable>
        core::set<typename std::remove_reference<Iterable>::type::iterator::value_type > set(Iterable&& t) {
            return core::set<typename std::remove_reference<Iterable>::type::iterator::value_type >(t.begin(), t.end());
        } 
    PROXY(pythonic,set);



    /* map */
    template <typename Operator, typename List0, typename... Iterators>
        auto _map(Operator& op, List0 && seq, Iterators... iterators)
        -> core::list< decltype(op(*seq.begin(), *iterators...)) > 
        {
            core::list< decltype(op(*seq.begin(), *iterators...)) > s = core::empty_list();
            s.reserve(len(seq));
            for(auto const& iseq : seq)
                s.push_back(op(iseq, *iterators++...));
            return s;
        }


    template <typename List0, typename... Iterators>
        auto _map(pythonic::none_type, List0 && seq, Iterators... iterators) 
        -> core::list< std::tuple< typename std::remove_reference<List0>::type::iterator::value_type,  typename Iterators::value_type... > >
        {
            core::list< std::tuple< typename std::remove_reference<List0>::type::iterator::value_type,  typename Iterators::value_type... > > s = core::empty_list();
            s.reserve(len(seq));
            for(auto const& iseq : seq) {
                s.push_back(std::make_tuple( iseq, *iterators... ));
                fwd(++iterators...);
            }
	    return s;
        }

    template <typename List0>
        auto _map(pythonic::none_type, List0 && seq)
        -> core::list< typename std::remove_reference<List0>::type::iterator::value_type >
        {
            core::list< typename std::remove_reference<List0>::type::iterator::value_type > s = core::empty_list();
            s.reserve(len(seq));
            for(auto const& iseq : seq)
                s.push_back(iseq);
            return s;
        }

    template <typename Operator, typename List0, typename... ListN>
        auto map(Operator op, List0 && seq, ListN &&... lists)
        -> decltype( _map(op, std::forward<List0>(seq), lists.begin()...) )
        {
            return _map(op, std::forward<List0>(seq), lists.begin()...);
        }

    PROXY(pythonic,map);

    /* max */
    template <int n, class... Types>
        struct Max;

    template <class T0>
        struct Max<true, T0> {
            typedef typename std::remove_reference<T0>::type::iterator::value_type result_type;
            result_type operator()(T0 && t) {
                return *std::max_element(t.begin(), t.end());
            }
        };

    template<class T0>
        struct Max<false, T0> {
            typedef T0 result_type;
            result_type operator()( T0 const & t ) {
                return t;
            }
        };

    template <class T0, class T1>
        struct Max<false, T0, T1> {
            typedef decltype(std::declval<T0>() + std::declval<T1>()) result_type;
            result_type operator()(T0 const & t0, T1 const& t1) {
                return t0>t1? t0: t1;
            }

        };

    template <class T0, class... Types>
        struct Max<false, T0, Types...> {
            typedef typename Max<false, T0, typename Max<false, Types...>::result_type>::result_type result_type;

            result_type operator()(T0 const & t0, Types const&... values)
            {
                result_type t1 = Max<false, Types...>()(values...);
                return t0 > t1 ? t0 : t1;
            }
        };

    template <class... Types>
        typename Max<  sizeof...(Types) == 1, Types...>::result_type max(Types &&... values) {
            return Max< sizeof...(Types) ==1, Types...>()(std::forward<Types>(values)...);
        }
    PROXY(pythonic,max);

    /* min */
    template <int n, class... Types>
        struct Min;

    template <class T0>
        struct Min<true, T0> {
            typedef typename std::remove_reference<T0>::type::iterator::value_type result_type;
            result_type operator()(T0 && t) {
                return *std::min_element(t.begin(), t.end());
            }
        };

    template<class T0>
        struct Min<false, T0> {
            typedef T0 result_type;
            result_type operator()( T0 const & t ) {
                return t;
            }
        };

    template <class T0, class T1>
        struct Min<false, T0, T1> {
            typedef decltype(std::declval<T0>() + std::declval<T1>()) result_type;
            result_type operator()(T0 const & t0, T1 const& t1) {
                return t0<t1? t0: t1;
            }

        };

    template <class T0, class... Types>
        struct Min<false, T0, Types...> {
            typedef decltype( Min<false, T0, typename Min<false, Types...>::result_type>::result_type) result_type;


            result_type operator()(T0 const & t0, Types const&... values)
            {
                auto t1 = (*this)(values...);
                return t0 < t1 ? t0 : t1;
            }
        };

    template <class... Types>
        typename Min<  sizeof...(Types) == 1, Types...>::result_type min(Types &&... values) {
            return Min< sizeof...(Types) ==1, Types...>()(std::forward<Types>(values)...);
        }
    PROXY(pythonic,min);

    /* oct */
    template <class T>
        core::string oct(T const & v) {
            std::ostringstream oss;
            oss << '0' << std::oct << v;
            return oss.str();
        }
    PROXY(pythonic, oct);

    /* pow */
    using std::pow;
    long pow(long n, long m) { return std::pow(n,m); }
    PROXY(pythonic, pow);

    /* xrange */
    struct xrange_iterator : std::iterator< std::random_access_iterator_tag, long >{
        long value;
        long step;
        long sign;
        xrange_iterator() {}
        xrange_iterator(long v, long s) : value(v), step(s), sign(s<0?-1:1) {}
        long& operator*() { return value; }
        xrange_iterator& operator++() { value+=step; return *this; }
        xrange_iterator operator++(int) { xrange_iterator self(*this); value+=step; return self; }
        xrange_iterator& operator+=(long n) { value+=step*n; return *this; }
        bool operator!=(xrange_iterator const& other) { return value != other.value; }
        bool operator<(xrange_iterator const& other) { return sign*value < sign*other.value; }
        long operator-(xrange_iterator const& other) { return (value - other.value)/step; }
    };
    struct xrange_riterator : std::iterator< std::random_access_iterator_tag, long >{
        long value;
        long step;
        long sign;
        xrange_riterator() {}
        xrange_riterator(long v, long s) : value(v), step(s), sign(s<0?1:-1) {}
        long& operator*() { return value; }
        xrange_riterator& operator++() { value+=step; return *this; }
        xrange_riterator operator++(int) { xrange_riterator self(*this); value+=step; return self; }
        xrange_riterator& operator+=(long n) { value+=step*n; return *this; }
        bool operator!=(xrange_riterator const& other) { return value != other.value; }
        bool operator<(xrange_riterator const& other) { return sign*value > sign*other.value; }
        long operator-(xrange_riterator const& other) { return (value - other.value)/step; }
    };

    struct xrange {
        long _begin;
        long _end;
        long _step;
        long _last;
        typedef long value_type;
        typedef xrange_iterator iterator;
        typedef xrange_iterator const_iterator;
        typedef xrange_riterator reverse_iterator;
        typedef xrange_riterator const_reverse_iterator;
        void _init_last() {
            if(_step>0) _last= _begin + std::max(0L,_step * ( (_end - _begin + _step -1)/ _step));
            else _last= _begin + std::min(0L,_step * ( (_end - _begin + _step +1)/ _step)) ;
        }
        xrange(){}
        xrange( long b, long e , long s=1) : _begin(b), _end(e), _step(s) { _init_last(); }
        xrange( long e ) : _begin(0), _end(e), _step(1) { _init_last(); }
        xrange_iterator begin() const { return xrange_iterator(_begin, _step); }
        xrange_iterator end() const {
            return xrange_iterator(_last, _step);
        }
        reverse_iterator rbegin() const { return reverse_iterator(_end-_step, -_step); }
        reverse_iterator rend() const {
            if(_step>0) return reverse_iterator(_end - std::max(0L,_step * ( 1 + (_end - _begin)/ _step)) , -_step);
            else return reverse_iterator(_end - std::min(0L,_step * ( 1 + (_end - _begin)/ _step)) , -_step);
        }
    };
    PROXY(pythonic,xrange);

    /* range */
    core::list<long> _range(xrange & xr) {
        core::list<long> s(len(xr));
        std::copy(xr.begin(), xr.end(), s.begin());
        return s;
    }

    core::list<long> range(long e) {
        xrange xr(e);
        return _range(xr);
    }
    core::list<long> range(long b, long e, long s=1) {
        xrange xr(b, e, s);
        return _range(xr);
    }
    PROXY(pythonic,range);

    /* reduce */

    template<class Iterable, class Operator>
        auto reduce(Operator op, Iterable s)
        -> decltype( op( std::declval< typename Iterable::iterator::value_type >(), std::declval< typename Iterable::iterator::value_type >() ) )
        {
            auto iter = s.begin();
            auto r = *iter;
            ++iter;
            if(iter!=s.end())
                return  std::accumulate(iter, s.end(), r, op);
            else
                return r;
        }
    template<class Iterable, class Operator, class T>
        auto reduce(Operator op, Iterable s, T const & init)
        -> decltype( std::accumulate(s.begin(), s.end(), static_cast<decltype(op(init,std::declval<typename Iterable::iterator::value_type>()))>(init), op) )
        {
            return std::accumulate(s.begin(), s.end(), static_cast<decltype(op(init,std::declval<typename Iterable::iterator::value_type>()))>(init), op);
        }
    PROXY(pythonic,reduce);

    /* reversed */
    template <class Iterable>
        struct _reversed {
            Iterable iterable;
            _reversed() {}
            _reversed(Iterable const& iterable) : iterable(iterable) {}
            typedef typename Iterable::value_type value_type;
            typedef typename Iterable::reverse_iterator iterator;
            typedef typename Iterable::const_reverse_iterator const_iterator;
            iterator begin() { return iterable.rbegin(); }
            iterator end() { return iterable.rend(); }
            const_iterator begin() const { return iterable.rbegin(); }
            const_iterator end() const { return iterable.rend(); }
        };


    template <class Iterable>
        _reversed<Iterable> reversed(Iterable const& iterable) {
            return _reversed<Iterable>(iterable);
        }
    PROXY(pythonic, reversed);


    /* round */
    template <class T>
        double round(T const & v, size_t n=0) {
            T p = std::pow(10,n);
            return std::lround(v * p)/p;
        }
    PROXY(pythonic, round);

    /* sorted */
    template <class Iterable>
        core::list<typename std::remove_cv<typename Iterable::iterator::value_type>::type> sorted(Iterable const& seq) {
            core::list<typename std::remove_cv<typename Iterable::iterator::value_type>::type> out(seq.begin(), seq.end());
            std::sort(out.begin(), out.end());
            return out;
        }
    template <class Iterable, class C>
        core::list<typename std::remove_cv<typename Iterable::iterator::value_type>::type> sorted(Iterable const& seq, C const& cmp) {
            core::list<typename std::remove_cv<typename Iterable::iterator::value_type>::type> out(seq.begin(), seq.end());
            std::sort(out.begin(), out.end(), cmp);
            return out;
        }
    PROXY(pythonic, sorted);

    /* str */
    template <class T>
        core::string str(T const & t) {
            std::ostringstream oss;
            oss << t;
            return oss.str();
        }
    PROXY(pythonic, str);

    /* sum */
    template<class Iterable, class T>
        auto sum(Iterable s, T start) -> decltype(start+std::declval<typename Iterable::iterator::value_type>())
        {
            return std::accumulate(s.begin(), s.end(), (decltype(start+*s.begin()))start);
        }
    template<class Iterable>
        typename Iterable::iterator::value_type sum(Iterable s)
        {
            return sum(s,0L);
        }

    template<class Tuple>
        auto tuple_sum(Tuple const& t, int_<0>) -> decltype(std::get<0>(t)) {
            return std::get<0>(t);
        }

    template<class Tuple, int I>
        auto tuple_sum(Tuple const& t, int_<I>) -> typename std::remove_reference<decltype(std::get<I>(t))>::type {
            return std::get<I>(t) + tuple_sum(t, int_<I-1>());
        }


    template<class... Types>
        auto sum(std::tuple<Types...> const & t) -> decltype(tuple_sum(t, int_<sizeof...(Types)-1>())) {
            return tuple_sum(t, int_<sizeof...(Types)-1>());
        }

    PROXY(pythonic,sum);

    /* xrange -> forward declared */

    /* zip */
    template<class Iterator0, class... Iterators>
        core::list< std::tuple<typename Iterator0::value_type, typename Iterators::value_type... > > _zip(size_t n, Iterator0 first, Iterator0 last, Iterators...  iters) {
            core::list< std::tuple< typename Iterator0::value_type, typename Iterators::value_type... > > out = core::empty_list();
            out.reserve(n);
            for(; first!=last; ++first, fwd(++iters...)) {
                out.push_back(std::make_tuple( *first, *iters... ));
            }
            return out;
        }

    template<class List0, class... Lists>
        core::list< std::tuple<typename std::remove_reference<List0>::type::value_type, typename std::remove_reference<Lists>::type::value_type... > > zip(List0 && s0, Lists &&...  lists) {
            size_t n = max(len(std::forward<List0>(s0)), len(std::forward<Lists>(lists))...);
            return _zip(n, s0.begin(), s0.end(), lists.begin()...);
        }

    core::empty_list zip() {
        return core::empty_list();
    }

    PROXY(pythonic,zip);

    /* constructor */
    template<typename T>
    struct constructor {
        template<class V>
        T operator()(V&& v) {
            return T(std::forward<V>(v));
        }
    };


    /* reserve */
    template <class Container, class From>
        void reserve(Container & , From &) //do nothing unless specialized
        {
        }
    template <class T, class From>
        void reserve(core::list<T> & l, From const &f, typename From::const_iterator p=typename From::const_iterator())
        {
            l.reserve(len(f));
        }

    /* get good typing for floordiv */
    template<class T0, class T1>
        long floordiv(T0 a, T1 b) {
            return T0(floor(a/b));
        }


}
#endif

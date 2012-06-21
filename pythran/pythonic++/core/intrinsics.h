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
    template <class T>
        bool all( core::list<T> const& s) {
            return s.end() == std::find_if(s.begin(), s.end(), [](T const&t) { return not bool(t); });
        }
    PROXY(pythonic, all);

    /* any */
    template <class T>
        bool any( core::list<T> const& s) {
            return s.end() != std::find_if(s.begin(), s.end(), [](T const&t) { return bool(t); });
        }
    PROXY(pythonic, any);

    /* bin */
    template<class T>
        std::string bin(T const &v) {
            std::ostringstream oss("0b");
            for(size_t i=1 << (8*sizeof(T)-1); i ; i>>=1)
                if(v & i) oss << "1";
                else oss << "0";
            return oss.str();
        }
    PROXY(pythonic, bin);

    /* chr */
    template<class T>
        std::string chr(T const &v) { return std::string(1,(char)v); }
    PROXY(pythonic, chr);

    /* cmp */
    template<class T0, class T1>
        bool cmp(T0 const& v0, T1 const& v1) {
            return v0 == v1 ? 0 : ( v0 < v1 ? -1 : 1 );
        }
    PROXY(pythonic, cmp);

    /* complex */
    template<class T0, class T1=double> // do not handle string as first argument
    std::complex<double> complex(T0 const& v0, T1 const& v1 = 0.) {
        return std::complex<double>(v0,v1);
    }
    PROXY(pythonic, complex);

    /* divmod */
    template<class T0, class T1>
        auto divmod(T0 const& t0, T1 const& t1) // other types are left over
            -> decltype(std::make_tuple(t0/t1, t0%t1)) {
                return std::make_tuple(t0/t1, t0%t1);
            }
    PROXY(pythonic, divmod);

    /* enumerate */
    template<class T>
    struct enumerate_iterator : std::iterator< std::forward_iterator_tag, long >{
        long value;
        typename core::list<T>::const_iterator iter;
        enumerate_iterator(long value, typename core::list<T>::const_iterator iter) : value(value), iter(iter) {}
        std::tuple<long,T>  operator*() { return std::make_tuple(value, *iter); }
        enumerate_iterator& operator++() { ++value,++iter; return *this; }
        enumerate_iterator operator++(int) { enumerate_iterator self(*this); ++value, ++iter; return self; }
        bool operator!=(enumerate_iterator const& other) { return value != other.value; }
    };

    template <class T>
    struct _enumerate {
        core::list<T> const& seq;
        typedef std::tuple<long, T> value_type;
        _enumerate( core::list<T> const& seq ) : seq(seq) {}
        enumerate_iterator<T> begin() const { return enumerate_iterator<T>(0L,seq.begin()); }
        enumerate_iterator<T> end() const { return enumerate_iterator<T>(seq.end()-seq.begin(), seq.end()); }
    };
    template <class T>
    _enumerate<T> enumerate(core::list<T> const& seq) { return _enumerate<T>(seq); }
    PROXY(pythonic,enumerate);

    /* filter */
    template<class F, class T>
        core::list<T> filter(F const& f, core::list<T> const& seq) { /* does not implement the full standard */
            core::list<T> out;
            std::copy_if(seq.begin(), seq.end(), std::back_inserter(out), f);
            return out;
        }
    PROXY(pythonic, filter);

    /* hex */
    template <class T>
        std::string hex(T const & v) {
            std::ostringstream oss("0x");
            oss << std::hex << v;
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
        struct _id< core::list<T> > {
            intptr_t operator()(core::list<T> const &t) {
                return reinterpret_cast<intptr_t>(&(*t.data));
            }
        };

    template <class T>
        intptr_t id(T const & t) {
            return _id<T>()(t);
        }
    PROXY(pythonic,id);

    /* in */
    template <class T, class V>
        bool in(T const &t, V const &v) {
            return std::find(t.begin(), t.end(), v) != t.end();
        }
    template <>
        bool in<std::string, std::string>(std::string const &t, std::string const &v) {
            return t.find(v) != std::string::npos;
        }
    PROXY(pythonic,in);


    /* len */
    template <class T>
        size_t len(T const &t ) {
            return std::distance(t.begin(), t.end());
        }
    PROXY(pythonic,len);

    /* list */
    core::empty_list list() {
        return core::empty_list();
    }

    template <class T, int V>
        struct _list {
        };
    template <class T>
        struct _list<T,0> {
        };

    template <class T>
        struct _list<T,1> {
            typedef core::list<typename T::value_type> type;
            type operator()(T const &t) {
                type r;
                auto inserter = std::back_inserter(r);
                for(auto &i : t) *inserter++=i;
                return r;
            }
        };

    template <class T, int V = is_container<T>::value>
        typename _list<T,V>::type list(T const & t) {
            return _list<T,V>()(t);
        } 
    PROXY(pythonic,list);

    /* set */
    core::empty_set set() {
        return core::empty_set();
    }

    template <class T, int V>
        struct _set {
        };
    template <class T>
        struct _set<T,0> {
        };

    template <class T>
        struct _set<T,1> {
            typedef core::set<typename T::value_type> type;
            type operator()(T const &t) {
                type r;
                auto inserter = std::back_inserter(r);
                for(auto &i : t) *inserter++=i;
                return r;
            }
        };

    template <class T, int V = is_container<T>::value>
        typename _set<T,V>::type set(T const & t) {
            return _set<T,V>()(t);
        } 
    PROXY(pythonic,set);



    /* map */
    template <typename Operator, typename List0, typename... Iterators>
        auto _map(Operator& op, List0 const& seq, Iterators... iterators)
        -> core::list< decltype(op(*seq.begin(), *iterators...)) >
        {
            decltype(_map(op,seq, iterators...)) s;
            auto iter = std::back_inserter(s);
            for(auto & iseq : seq)
                *iter++= op(iseq, *iterators++...);
            return s;
        }

    template <typename Operator, typename List0, typename... ListN>
        auto map(Operator op, List0 const& seq, ListN const &... lists)
        -> decltype( _map(op, seq, lists.begin()...) )
        {
            return _map(op, seq, lists.begin()...);
        }

    PROXY(pythonic,map);

    /* max */
    template <class... Types> struct Max;

    template <class T0>
        struct Max<T0> {
            typedef T0 return_type;
            return_type operator()(T0 const & t) {
                return t;
            }
        };
    template <class T0, class T1>
        struct Max<T0, T1> {
            typedef decltype(std::declval<T0>() + std::declval<T1>()) return_type;
            return_type operator()(T0 const & t0, T1 const& t1) {
                return t0>t1? t0: t1;
            }

        };

    template <class T0, class... Types>
        struct Max<T0, Types...> {
            typedef decltype( Max<T0, typename Max<Types...>::return_type >::return_type) return_type;


            return_type operator()(T0 const & t0, Types const&... values)
            {
                auto t1 = (*this)(values...);
                return t0 > t1 ? t0 : t1;
            }
        };
    template<class T>
        struct Max<core::list<T>> {
            typedef typename core::list<T>::value_type return_type;

            return_type operator()( core::list<T> const & s ) {
                return *std::max_element(s.begin(), s.end());
            }
        };

    template <class... Types>
        typename Max<Types...>::return_type max(Types const&... values) {
            return Max<Types...>()(values...);
        }
    PROXY(pythonic,max);

    /* min */
    template <class... Types> struct Min;

    template <class T0>
        struct Min<T0> {
            typedef T0 return_type;
            return_type operator()(T0 const & t) {
                return t;
            }
        };
    template <class T0, class T1>
        struct Min<T0, T1> {
            typedef decltype(std::declval<T0>() + std::declval<T1>()) return_type;
            return_type operator()(T0 const & t0, T1 const& t1) {
                return t0>t1? t0: t1;
            }

        };

    template <class T0, class... Types>
        struct Min<T0, Types...> {
            typedef decltype( Min<T0, typename Min<Types...>::return_type >::return_type) return_type;


            return_type operator()(T0 const & t0, Types const&... values)
            {
                auto t1 = (*this)(values...);
                return t0 > t1 ? t0 : t1;
            }
        };

    template<class T>
        struct Min<core::list<T>> {
            typedef typename core::list<T>::value_type return_type;

            return_type operator()( core::list<T> const & s ) {
                return *std::min_element(s.begin(), s.end());
            }
        };

    template <class... Types>
        typename Min<Types...>::return_type min(Types const&... values) {
            return Min<Types...>()(values...);
        }
    PROXY(pythonic,min);

    /* oct */
    template <class T>
        std::string oct(T const & v) {
            std::ostringstream oss("0");
            oss << std::oct << v;
            return oss.str();
        }
    PROXY(pythonic, oct);

    /* pow */
    using std::pow;
    PROXY(pythonic, pow);

    /* xrange */
    struct xrange_iterator : std::iterator< std::forward_iterator_tag, long >{
        long value;
        long step;
        xrange_iterator(long v, long s) : value(v), step(s) {}
        long& operator*() { return value; }
        xrange_iterator& operator++() { value+=step; return *this; }
        xrange_iterator operator++(int) { xrange_iterator self(*this); value+=step; return self; }
        bool operator!=(xrange_iterator const& other) { return value != other.value; }
    };

    struct xrange {
        long _begin;
        long _end;
        long _step;
        typedef long value_type;
        xrange( long b, long e , long s=1) : _begin(b), _end(e), _step(s) {}
        xrange( long e ) : _begin(0), _end(e), _step(1) {}
        xrange_iterator begin() const { return xrange_iterator(_begin, _step); }
        xrange_iterator end() const {
            if(_step>0) return xrange_iterator(_begin + std::max(0L,_step * ( (_end - _begin)/ _step)) , _step);
            else return xrange_iterator(_begin + std::min(0L,_step * ( (_end - _begin)/ _step)) , _step);
        }
    };
    PROXY(pythonic,xrange);

    /* range */
    core::list<long> _range(xrange & xr) {
        core::list<long> s;
        std::copy(xr.begin(), xr.end(), std::back_inserter(s));
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

    template<class List, class Operator>
        auto reduce(Operator op, List const& s)
        -> decltype( op( std::declval< typename List::value_type >(), std::declval< typename List::value_type >() ) )
        {
            decltype( op( std::declval< typename List::value_type >(), std::declval< typename List::value_type >() ) ) res = op( s[0], s[1] );
            return std::accumulate(s.begin() + 2, s.end(), res, op);
        }
    template<class List, class Operator, class T>
        auto reduce(Operator op, List const& s, T const & init)
        -> decltype( std::accumulate(s.begin(), s.end(), init, op) )
        {
            return std::accumulate(s.begin(), s.end(), init, op);
        }
    PROXY(pythonic,reduce);

    /* reversed */
    template <class T>
        struct _reversed {
            core::list<T> const& seq;
            _reversed(core::list<T> const& seq) : seq(seq) {}
            typedef typename core::list<T>::value_type value_type;
            auto begin() -> decltype(seq.rbegin()) { return seq.rbegin(); }
            auto end() -> decltype(seq.rend()) { return seq.rend(); }
        };


    template <class T>
        _reversed<T> reversed(core::list<T> const& seq) {
            return _reversed<T>(seq);
        }
    PROXY(pythonic, reversed);


    /* round */
    template <class T>
        T round(T const & v, size_t n=0) {
            T p = std::pow(10,n);
            return std::floor(v * p)/p;
        }
    PROXY(pythonic, round);

    /* sorted */
    template <class T>
        core::list<T> sorted(core::list<T> const& seq) {
            core::list<T> out(seq);
            std::sort(out.begin(), out.end());
            return out;
        }
    template <class T, class C>
        core::list<T> sorted(core::list<T> const& seq, C const& cmp) {
            core::list<T> out(seq);
            std::sort(seq.bein(), seq.end(), cmp);
            return out;
        }
    PROXY(pythonic, sorted);

    /* str */
    template <class T>
        std::string str(T const & t) {
            std::ostringstream oss;
            oss << t;
            return oss.str();
        }
    PROXY(pythonic, str);

    /* sum */
    template<class List>
        auto sum(List const& s, size_t start=0)
        -> decltype( std::declval< typename List::value_type >() + std::declval< typename List::value_type >() )
        {
            auto iter = s.begin()+start;
            decltype( std::declval< typename List::value_type >() + std::declval< typename List::value_type >() ) res = *(iter++);
            return std::accumulate(iter, s.end(), res);
        }
    PROXY(pythonic,sum);

    /* xrange -> forward declared */

    /* zip */
    template<class Iterator0, class... Iterators>
        core::list< std::tuple<typename Iterator0::value_type, typename Iterators::value_type... > > _zip(Iterator0 first, Iterator0 last, Iterators...  iters) {
            core::list< std::tuple< typename Iterator0::value_type, typename Iterators::value_type... > > out;
            auto biter = std::back_inserter(out);
            while(first!=last)
                *biter++= std::make_tuple( *first++, *iters++... );
            return out;
        }

    template<class List0, class... Lists>
        core::list< std::tuple<typename List0::value_type, typename Lists::value_type... > > zip(List0 const& s0, Lists const&...  lists) {
            return _zip(s0.begin(), s0.end(), lists.begin()...);
        }

    core::empty_list zip() {
        return core::empty_list();
    }

    PROXY(pythonic,zip);

}
#endif

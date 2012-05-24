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
        bool all( sequence<T> const& s) {
            return s.end() == std::find_if(s.begin(), s.end(), [](T const&t) { return not bool(t); });
        }
    PROXY(pythonic, all);

    /* any */
    template <class T>
        bool any( sequence<T> const& s) {
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
        typename sequence<T>::const_iterator iter;
        enumerate_iterator(long value, typename sequence<T>::const_iterator iter) : value(value), iter(iter) {}
        std::tuple<long,T>  operator*() { return std::make_tuple(value, *iter); }
        enumerate_iterator& operator++() { ++value,++iter; return *this; }
        enumerate_iterator operator++(int) { enumerate_iterator self(*this); ++value, ++iter; return self; }
        bool operator!=(enumerate_iterator const& other) { return value != other.value; }
    };

    template <class T>
    struct _enumerate {
        sequence<T> const& seq;
        typedef std::tuple<long, T> value_type;
        _enumerate( sequence<T> const& seq ) : seq(seq) {}
        enumerate_iterator<T> begin() const { return enumerate_iterator<T>(0L,seq.begin()); }
        enumerate_iterator<T> end() const { return enumerate_iterator<T>(seq.end()-seq.begin(), seq.end()); }
    };
    template <class T>
    _enumerate<T> enumerate(sequence<T> const& seq) { return _enumerate<T>(seq); }
    PROXY(pythonic,enumerate);

    /* filter */
    template<class F, class T>
        sequence<T> filter(F const& f, sequence<T> const& seq) { /* does not implement the full standard */
            sequence<T> out;
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
        struct _id< sequence<T> > {
            intptr_t operator()(sequence<T> const &t) {
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
    empty_sequence list() {
        return empty_sequence();
    }

    template <class T, int V>
        struct _list {
        };
    template <class T>
        struct _list<T,0> {
        };

    template <class T>
        struct _list<T,1> {
            typedef sequence<typename T::value_type> type;
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


    /* map */
    template <typename Operator, typename Sequence0, typename... Iterators>
        auto _map(Operator& op, Sequence0 const& seq, Iterators... iterators)
        -> sequence< decltype(op(*seq.begin(), *iterators...)) >
        {
            decltype(_map(op,seq, iterators...)) s;
            auto iter = std::back_inserter(s);
            for(auto & iseq : seq)
                *iter++= op(iseq, *iterators++...);
            return s;
        }

    template <typename Operator, typename Sequence0, typename... SequenceN>
        auto map(Operator op, Sequence0 const& seq, SequenceN const &... sequences)
        -> decltype( _map(op, seq, sequences.begin()...) )
        {
            return _map(op, seq, sequences.begin()...);
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
        struct Max<sequence<T>> {
            typedef typename sequence<T>::value_type return_type;

            return_type operator()( sequence<T> const & s ) {
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
        struct Min<sequence<T>> {
            typedef typename sequence<T>::value_type return_type;

            return_type operator()( sequence<T> const & s ) {
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
        xrange_iterator end() const { return xrange_iterator(_begin + _step * ( (_end - _begin)/ _step) , _step); }
    };
    PROXY(pythonic,xrange);

    /* range */
    sequence<long> _range(xrange & xr) {
        sequence<long> s;
        std::copy(xr.begin(), xr.end(), std::back_inserter(s));
        return s;
    }

    sequence<long> range(long e) {
        xrange xr(e);
        return _range(xr);
    }
    sequence<long> range(long b, long e, long s=1) {
        xrange xr(b, e, s);
        return _range(xr);
    }
    PROXY(pythonic,range);

    /* reduce */

    template<class Sequence, class Operator>
        auto reduce(Operator op, Sequence const& s)
        -> decltype( op( std::declval< typename Sequence::value_type >(), std::declval< typename Sequence::value_type >() ) )
        {
            decltype( op( std::declval< typename Sequence::value_type >(), std::declval< typename Sequence::value_type >() ) ) res = op( s[0], s[1] );
            return std::accumulate(s.begin() + 2, s.end(), res, op);
        }
    template<class Sequence, class Operator, class T>
        auto reduce(Operator op, Sequence const& s, T const & init)
        -> decltype( std::accumulate(s.begin(), s.end(), init, op) )
        {
            return std::accumulate(s.begin(), s.end(), init, op);
        }
    PROXY(pythonic,reduce);

    /* reversed */
    template <class T>
        struct _reversed {
            sequence<T> const& seq;
            _reversed(sequence<T> const& seq) : seq(seq) {}
            typedef typename sequence<T>::value_type value_type;
            auto begin() -> decltype(seq.rbegin()) { return seq.rbegin(); }
            auto end() -> decltype(seq.rend()) { return seq.rend(); }
        };


    template <class T>
        _reversed<T> reversed(sequence<T> const& seq) {
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
        sequence<T> sorted(sequence<T> const& seq) {
            sequence<T> out(seq);
            std::sort(out.begin(), out.end());
            return out;
        }
    template <class T, class C>
        sequence<T> sorted(sequence<T> const& seq, C const& cmp) {
            sequence<T> out(seq);
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
    template<class Sequence>
        auto sum(Sequence const& s, size_t start=0)
        -> decltype( std::declval< typename Sequence::value_type >() + std::declval< typename Sequence::value_type >() )
        {
            auto iter = s.begin()+start;
            decltype( std::declval< typename Sequence::value_type >() + std::declval< typename Sequence::value_type >() ) res = *(iter++);
            return std::accumulate(iter, s.end(), res);
        }
    PROXY(pythonic,sum);

    /* xrange -> forward declared */

    /* zip */
    template<class Iterator0, class... Iterators>
        sequence< std::tuple<typename Iterator0::value_type, typename Iterators::value_type... > > _zip(Iterator0 first, Iterator0 last, Iterators...  iters) {
            sequence< std::tuple< typename Iterator0::value_type, typename Iterators::value_type... > > out;
            auto biter = std::back_inserter(out);
            while(first!=last)
                *biter++= std::make_tuple( *first++, *iters++... );
            return out;
        }

    template<class Sequence0, class... Sequences>
        sequence< std::tuple<typename Sequence0::value_type, typename Sequences::value_type... > > zip(Sequence0 const& s0, Sequences const&...  sequences) {
            return _zip(s0.begin(), s0.end(), sequences.begin()...);
        }

    empty_sequence zip() {
        return empty_sequence();
    }

    PROXY(pythonic,zip);

}
#endif

#ifndef PYTHONIC_INTRINSICS_H
#define PYTHONIC_INTRINSICS_H

#include <tuple>

namespace pythonic {
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

    /* in */
    template <class T, class V>
        bool in(T const &t, V const &v) {
            return std::find(t.begin(), t.end(), v) == t.end();
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
}
#endif

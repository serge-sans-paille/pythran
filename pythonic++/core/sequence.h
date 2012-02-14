#ifndef PYTHONIC_SEQUENCE_H
#define PYTHONIC_SEQUENCE_H
#include <vector>
#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>

namespace  pythonic {

    struct empty_sequence;

    struct slice {
        long lower, upper, step;
        slice(long lower=0, long upper=std::numeric_limits<long>::max(), long step=1)
            : lower(lower), upper(upper), step(step) {}
    };

    /* the container type */
    template<class T>
        class sequence {

            // data holder
            typedef std::vector< typename std::remove_cv< typename std::remove_reference<T>::type>::type > container_type;
            std::shared_ptr<container_type> data; 

            template<class U>
                friend struct _id;


            public:

            // types
            typedef typename container_type::reference reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::iterator iterator;
            typedef typename container_type::const_iterator const_iterator;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::difference_type difference_type;
            typedef typename container_type::value_type value_type;
            typedef typename container_type::allocator_type allocator_type;
            typedef typename container_type::pointer pointer;
            typedef typename container_type::const_pointer const_pointer;
            typedef typename container_type::reverse_iterator reverse_iterator;
            typedef typename container_type::const_reverse_iterator const_reverse_iterator;

            // constructors
            sequence() : data(new container_type()) {}
            sequence(empty_sequence const &) : data(new container_type()) {}
            sequence(size_type sz) : data( new container_type(sz) ) {}
            sequence(std::initializer_list<value_type> l) : data(new container_type(l)) {}
            sequence(sequence<T> const & other) : data(const_cast<sequence<T>*>(&other)->data) {}
            template<class F>
                sequence(sequence<F> const & other) : data(new container_type()) { std::copy(other.begin(), other.end(), std::back_inserter(*data)); }
            sequence<T>& operator=(sequence<T> const & other) { data=other.data; return *this; }

            // iterators
            iterator begin() { return data->begin(); }
            const_iterator begin() const { return data->begin(); }
            iterator end() { return data->end(); }
            const_iterator end() const { return data->end(); }
            reverse_iterator rbegin() { return data->rbegin(); }
            const_reverse_iterator rbegin() const { return data->rbegin(); }
            reverse_iterator rend() { return data->rend(); }
            const_reverse_iterator rend() const { return data->rend(); }

            // element access
            reference operator[]( size_type n ) { return (*data)[n]; }
            const_reference operator[]( size_type n ) const { return (*data)[n]; }
            sequence<T> operator[]( slice const &s ) const {
                sequence<T> out;
                long lower = s.lower >= 0L ? s.lower : ( s.lower + data->size());
                lower = std::max(0L,lower);
                long upper = s.upper >= 0L ? s.upper : ( s.upper + data->size());
                upper = std::min(upper, (long)data->size());
                for(long iter = lower; iter < upper ; iter+=s.step)
                    out.push_back((*data)[iter]);
                return out;
            }

            // modifiers
            void push_back( const T& x) { data->push_back(x); }

            // list interface
            operator bool() { return not data->empty(); }

            template <class F>
                sequence<decltype(std::declval<T>()+std::declval<typename sequence<F>::value_type>())> operator+(sequence<F> const & s) const {
                    sequence<decltype(std::declval<T>()+std::declval<typename sequence<F>::value_type>())> clone;
                    std::transform(this->begin(), this->end(), s.begin(), std::back_inserter(clone), [] (T const & t, typename sequence<F>::value_type const & f) { return t+f ; });
                    return clone;
                }

            sequence<T> operator+(empty_sequence const &) const {
                return *this;
            }

            template <class F>
                sequence<T>& operator+=(sequence<F> const & s) {
                    std::copy(s.begin(), s.end(), std::back_inserter(*this));
                    return *this;
                }

        };

    struct empty_sequence {
        template<class T> // just for type inference, should never been instantiated
            sequence<T> operator+(sequence<T> const & s) { return s; }
        empty_sequence operator+(empty_sequence const &) { return empty_sequence(); }
    };
}
#endif

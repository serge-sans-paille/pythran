#ifndef PYTHONIC_LIST_H
#define PYTHONIC_LIST_H
#include <vector>
#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>

namespace  pythonic {

    namespace core {

        struct empty_list;

        struct slice {
            long lower, upper, step;
            slice(long lower=0, long upper=std::numeric_limits<long>::max(), long step=1)
                : lower(lower), upper(upper), step(step) {}
        };

        /* the container type */
        template<class T>
            class list {

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
                list() : data(new container_type()) {}
                list(empty_list const &) : data(new container_type()) {}
                list(size_type sz) : data( new container_type(sz) ) {}
                list(std::initializer_list<value_type> l) : data(new container_type(l)) {}
                list(list<T> const & other) : data(const_cast<list<T>*>(&other)->data) {}
                template<class F>
                    list(list<F> const & other) : data(new container_type()) { std::copy(other.begin(), other.end(), std::back_inserter(*data)); }
                list<T>& operator=(list<T> const & other) { data=other.data; return *this; }

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
                list<T> operator[]( slice const &s ) const {
                    list<T> out;
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
                void insert(size_t i, const T& x) { data->insert(data->begin()+i, x); }
                void reserve(size_t n) { data->reserve(n); }

                // list interface
                operator bool() { return not data->empty(); }

                template <class F>
                    list<decltype(std::declval<T>()+std::declval<typename list<F>::value_type>())> operator+(list<F> const & s) const {
                        list<decltype(std::declval<T>()+std::declval<typename list<F>::value_type>())> clone;
                        std::transform(this->begin(), this->end(), s.begin(), std::back_inserter(clone), [] (T const & t, typename list<F>::value_type const & f) { return t+f ; });
                        return clone;
                    }

                list<T> operator+(empty_list const &) const {
                    return *this;
                }
                template<class F>
                    list<T> operator*(F const& t) const {
                        list<T> r;
                        size_t n = t;
                        r.data->reserve(r.data->size()*n);
                        for(size_t i=0;i<n;i++)
                            std::copy(this->begin(), this->end(),std::back_inserter((*r.data)));
                        return r;
                    }

                template <class F>
                    list<T>& operator+=(list<F> const & s) {
                        std::copy(s.begin(), s.end(), std::back_inserter(*this));
                        return *this;
                    }

            };

        struct empty_list {
            template<class T> // just for type inference, should never been instantiated
                list<T> operator+(list<T> const & s) { return s; }
            empty_list operator+(empty_list const &) { return empty_list(); }
        };
    }
}
#endif

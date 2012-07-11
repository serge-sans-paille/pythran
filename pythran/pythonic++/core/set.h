#ifndef PYTHONIC_SET_H
#define PYTHONIC_SET_H
#include <set>
#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>

namespace  pythonic {


    /* the container type */
    namespace core {

        struct empty_set;

        template<class T>
            class set {

                // data holder
                typedef std::set< typename std::remove_cv< typename std::remove_reference<T>::type>::type > container_type;
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
                set() : data(new container_type()) {}
                set(empty_set const &) : data(new container_type()) {}
                set(size_type sz) : data( new container_type(sz) ) {}
                set(std::initializer_list<value_type> l) : data(new container_type(l)) {}
                set(set<T> const & other) : data(const_cast<set<T>*>(&other)->data) {}
                template<class F>
                    set(set<F> const & other) : data(new container_type()) { std::copy(other.begin(), other.end(), std::back_inserter(*data)); }
                set<T>& operator=(set<T> const & other) { data=other.data; return *this; }

                // iterators
                iterator begin() { return data->begin(); }
                const_iterator begin() const { return data->begin(); }
                iterator end() { return data->end(); }
                const_iterator end() const { return data->end(); }
                reverse_iterator rbegin() { return data->rbegin(); }
                const_reverse_iterator rbegin() const { return data->rbegin(); }
                reverse_iterator rend() { return data->rend(); }
                const_reverse_iterator rend() const { return data->rend(); }

                // modifiers
                void add( const T& x) { data->insert(x); }
                void push_back( const T& x) { data->insert(x); }

                // set interface
                operator bool() { return not data->empty(); }

                set<T> operator+(empty_set const &) const {
                    return *this;
                }
                template <class F>
                    set<decltype(std::declval<T>()+std::declval<typename set<F>::value_type>())> operator+(set<F> const & s) const;

            };

        struct empty_set {
            template<class T> // just for type inference, should never been instantiated
                set<T> operator+(set<T> const & s) { return s; }
            empty_set operator+(empty_set const &) { return empty_set(); }
        };
    }
}
#endif

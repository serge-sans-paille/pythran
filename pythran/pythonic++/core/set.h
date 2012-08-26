#ifndef PYTHONIC_SET_H
#define PYTHONIC_SET_H
#include <set>
#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>
#include <boost/pool/object_pool.hpp>
#include "fsb_allocator.h"

namespace  pythonic {


    /* the container type */
    namespace core {



        struct empty_set;

        template<class T>
            class set {

                // data holder
                typedef  typename std::remove_cv< typename std::remove_reference<T>::type>::type  _type;
                typedef std::set< _type, std::less<_type>, FSBAllocator<_type> > container_type;
                size_t* refcount;
                container_type* data; 

                template<class U>
                    friend struct _id;

                struct memory_size { size_t refcount; container_type data; };
                static boost::object_pool<memory_size> pool;

                public:

                // types
                typedef typename container_type::reference reference;
                typedef typename container_type::const_reference const_reference;
                typedef comparable_iterator<typename container_type::iterator> iterator;
                typedef comparable_iterator<typename container_type::const_iterator> const_iterator;
                typedef typename container_type::size_type size_type;
                typedef typename container_type::difference_type difference_type;
                typedef typename container_type::value_type value_type;
                typedef typename container_type::allocator_type allocator_type;
                typedef typename container_type::pointer pointer;
                typedef typename container_type::const_pointer const_pointer;
                typedef typename container_type::reverse_iterator reverse_iterator;
                typedef typename container_type::const_reverse_iterator const_reverse_iterator;

                // constructors
                set() :
                    refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type()) { *refcount=1; }
                template<class InputIterator>
                    set(InputIterator start, InputIterator stop) : 
                        refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type()) {
                            std::copy(start, stop, std::back_inserter(*this));
                            *refcount=1;
                        }
                set(empty_set const &) : 
                    refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type()) { *refcount=1; }
                set(std::initializer_list<value_type> l) : 
                    refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type(l)) { *refcount=1; }
                set(set<T> const & other) :
                    data(const_cast<set<T>*>(&other)->data), refcount(const_cast<set<T>*>(&other)->refcount) { ++*refcount; }
                template<class F>
                    set(set<F> const & other) : 
                        refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type()){
                            std::copy(other.begin(), other.end(), std::back_inserter(*data));
                        }
                ~set() {
                    assert(*refcount>0);
                    if(not --*refcount) { pool.free( reinterpret_cast<memory_size*>(refcount)); }
                }
                set<T>& operator=(set<T> const & other) {
                    assert(*refcount>0);
                    if(other.data != data) {
                        if(not --*refcount) {  pool.free( reinterpret_cast<memory_size*>(refcount) ); }
                        data=const_cast<set<T>*>(&other)->data;
                        refcount=const_cast<set<T>*>(&other)->refcount;
                        ++*refcount;
                    }
                    return *this;
                }

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

                long size() const { return data->size(); }

                template<class U> // just for type inference, should never been instantiated
                    set<decltype(std::declval<T>()+std::declval<U>())> operator+(set<U> const &);
            };

        template<class T>
            boost::object_pool<typename set<T>::memory_size> set<T>::pool;

        struct empty_set {
            template<class T> 
                set<T> operator+(set<T> const & s) { return s; }
            empty_set operator+(empty_set const &) { return empty_set(); }
        };
    }
}
#endif

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

        template<class T>
        struct comparable_iterator:T {
            comparable_iterator(const T& t) : T(t) {}
            bool operator<(comparable_iterator<T> other) {
                return (*this)!= other;
            }
        };


        struct empty_set;

        template<class T>
            class set {

                // data holder
                typedef  typename std::remove_cv< typename std::remove_reference<T>::type>::type  _type;
                typedef std::set< _type, std::less<_type>, FSBAllocator<_type> > container_type;
                size_t* refcount;
                container_type* data; 

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
		T pop() {
			if(size()<=0)
				throw std::out_of_range("Trying to pop() an empty set.");

			T tmp=*begin();
			data->erase(begin());
			return tmp;
		}
                void add( const T& x) { data->insert(x); }
                void push_back( const T& x) { data->insert(x); }
		void clear() { data->clear(); };

		template<class U>
		void discard(U const& elem){
			//Remove element elem from the set if it is present.
			data->erase(elem);
		}

		template<class U>
		void delete_(U const& elem){
			//Remove element elem from the set. Raises KeyError if elem is not contained in the set.
			iterator it;
			if((it=data->find(elem)) != end())
				throw std::runtime_error("set.delete() : couldn't delete element not in the set.");
			data->erase(it);
		}

                // set interface
                operator bool() { return not data->empty(); }

                long size() const { return data->size(); }

                template<class U> // just for type inference, should never been instantiated
                    set<decltype(std::declval<T>()+std::declval<U>())> operator+(set<U> const &);

		// Misc
		template<class U>
		bool isdisjoint(set<U> const & other) const {
			//Return true if the this has no elements in common with other.
			for(iterator i=begin(); i!=end(); ++i){
				if(other.get_data().find(*i)!=other.end())
					return false;
			}
			return true;
		}
		
		// Operators
		template<class U>
		bool operator<=(set<U> const& other) const {
			// Every element in this is in other
			for(iterator i=begin(); i!=end(); ++i){
				if(other.get_data().find(*i)==other.end())
					return false;
			}
			return true;
		}

		template<class U>
		bool operator<(set<U> const& other) const {
			// Every element in this is in other and this != other
			return (*this <= other) && (this->size() != other.size());
		}

		template<class U>
		bool operator>=(set<U> const& other) const {
			// Every element in other is in set
			return other <= *this;
		}

		template<class U>
		bool operator>(set<U> const& other) const {
			// Every element in other is in set and this != other
			return other < *this;
		}

		// const getter
		container_type const & get_data() const { return *data; }
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

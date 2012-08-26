#ifndef PYTHONIC_SEQUENCE_H
#define PYTHONIC_SEQUENCE_H
#include <cassert>
#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>
#include <boost/pool/object_pool.hpp>
#define DEFAULT_LIST_CAPACITY 16

namespace  pythonic {

    template <class T> struct _id;

    namespace core {

        struct empty_list;
        template <class T> class list;


        struct slice {
            long lower, upper, step;
            slice(long lower=0, long upper=std::numeric_limits<long>::max(), long step=1)
                : lower(lower), upper(upper), step(step) {}
        };

        template<class T>
            class list_view {

                // data holder
                typedef  typename std::remove_cv< typename std::remove_reference<T>::type>::type  _type;
                typedef std::vector< _type > container_type;
                size_t* refcount;
                container_type* data; 

                template<class U>
                    friend class list;

                slice slicing;

                public:
                //  types
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

                // constructor
                list_view(): data(nullptr),refcount(nullptr) {}
                list_view(list_view<T> const & s): data(s.data),refcount(s.refcount), slicing(s.slicing) { 
                    if(refcount)
                        ++*refcount;
                }
                list_view(list<T> & , slice const &);
                ~list_view() {
                    if(refcount) {
                        assert(*refcount>0);
                        --*refcount;
                        //sg ! maybe leak
                    }
                }

                // assignment
                list_view& operator=(list<T> const & );
                list_view& operator=(list_view<T> const & );
                list<T> operator+(list_view<T> const & );

                // iterators
                iterator begin() { assert(slicing.step==1) ; return data->begin()+slicing.lower; }
                const_iterator begin() const { assert(slicing.step==1) ; return data->begin()+slicing.lower; }
                iterator end() { assert(slicing.step==1) ; return data->begin()+slicing.upper; }
                const_iterator end() const { assert(slicing.step==1) ; return data->begin()+slicing.upper; }

                // size
                size_type size() const { assert(slicing.step==1); return slicing.upper - slicing.lower ; }

            };

        /* the container type */
        template<class T>
            class list {

                // data holder
                typedef  typename std::remove_cv< typename std::remove_reference<T>::type>::type  _type;
                typedef std::vector< _type > container_type;
                size_t* refcount;
                container_type* data; 

                struct memory_size { size_t refcount; container_type data; };


                template<class U>
                    friend struct pythonic::_id;

                template<class U>
                    friend class list_view;

                template<class U>
                    friend class list;

                static boost::object_pool<memory_size> pool;

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
                list() :
                    refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type()) { *refcount=1; }
                template<class InputIterator>
                    list(InputIterator start, InputIterator stop) :
                        refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type()) {
                            data->reserve(DEFAULT_LIST_CAPACITY);
                            std::copy(start, stop, std::back_inserter(*data));
                            *refcount=1;
                        }
                list(empty_list const &) :
                    refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type()) { *refcount=1; }
                list(size_type sz) :
                    refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type(sz)) { *refcount=1; }
                list(std::initializer_list<value_type> l) :
                    refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type(l)) { *refcount=1; }
                list(list<T> const & other) :
                    data(const_cast<list<T>*>(&other)->data), refcount(const_cast<list<T>*>(&other)->refcount) { ++*refcount; }
                template<class F>
                    list(list<F> const & other) :
                        refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type(other.data->size())) {
                            *refcount=1; 
                            std::copy(other.begin(), other.end(), begin());
                        }
                ~list() {
                    assert(*refcount>0);
                    if(not --*refcount) { pool.free( reinterpret_cast<memory_size*>(refcount)); }
                }

                list<T>& operator=(list<T> const & other) {
                    assert(*refcount>0);
                    if(other.data != data) {
                        if(not --*refcount) {  pool.free( reinterpret_cast<memory_size*>(refcount) ); }
                        data=const_cast<list<T>*>(&other)->data;
                        refcount=const_cast<list<T>*>(&other)->refcount;
                        ++*refcount;
                    }
                    return *this;
                }
                list<T>& operator=(list_view<T> const & other) {
                    assert(*refcount >0) ;
                    if(other.data == data ) {
                        auto it = std::copy(other.begin(), other.end(), data->begin());
                        data->resize(it - data->begin());
                    }
                    else {
                        if(not --*refcount) {
                            /* should free the memory then reallocate it, so do nothing */
                            /* HERE */
                        }
                        else {
                            refcount=reinterpret_cast<size_t*>(pool.malloc());
                            data=new (refcount+1) container_type(other.end() - other.begin());
                        }
                        *refcount=1;
                        std::copy(other.begin(), other.end(), data->begin());
                    }
                    return *this;
                }
                list<T>& operator+=(list_view<T> const & other) {
                    data->resize(data->size() + len(other));
                    std::copy(other.begin(), other.end(), data->begin());
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

                // element access
                reference operator[]( long n ) {
#ifndef NDEBUG
                    return (*data)[(n>=0)?n : (data->size() + n)];
#else
                    return (*data).at((n>=0)?n : (data->size() + n));
#endif
                }
                const_reference operator[]( long n ) const {
#ifndef NDEBUG
                    return (*data)[(n>=0)?n : (data->size() + n)];
#else
                    return (*data).at((n>=0)?n : (data->size() + n));
#endif
                }

                list<T> operator[]( slice const &s ) {
                    list<T> out(0);
                    long lower, upper;
                    if(s.step<0) {
                        if( s.lower == std::numeric_limits<long>::max() )
                            lower = data->size()-1;
                        else
                            lower = s.lower >= 0L ? s.lower : ( s.lower + data->size());
                        lower = std::max(0L,lower);
                        upper = s.upper >= 0L ? s.upper : ( s.upper + data->size());
                        upper = std::min(upper, (long)data->size());
                        for(long iter = lower; iter >= upper ; iter+=s.step)
                            out.push_back((*data)[iter]);
                    }
                    else {
                        lower = s.lower >= 0L ? s.lower : ( s.lower + data->size());
                        lower = std::max(0L,lower);
                        upper = s.upper >= 0L ? s.upper : ( s.upper + data->size());
                        upper = std::min(upper, (long)data->size());
                        for(long iter = lower; iter < upper ; iter+=s.step)
                            out.push_back((*data)[iter]);
                    }
                    return out;
                }

                list_view<T> operator()( slice const &s) {
                    return list_view<T>(*this, s);
                }

                // modifiers
                void push_back( const T& x) { data->push_back(x); }
                void insert(size_t i, const T& x) { data->insert(data->begin()+i, x); }
                void reserve(size_t n) { data->reserve(n); }
                void resize(size_t n) { data->resize(n); }
                iterator erase(size_t n) { return data->erase(data->begin()+n); }

                // list interface
                operator bool() { return not data->empty(); }

                template <class F>
                    list<decltype(std::declval<T>()+std::declval<typename list<F>::value_type>())> operator+(list<F> const & s) const {
                        list<decltype(std::declval<T>()+std::declval<typename list<F>::value_type>())> clone(data->size()+s.data->size());
                        std::copy(s.begin(), s.end(), std::copy(begin(), end(), clone.begin()));
                        return clone;
                    }

                template <class F>
                    list<decltype(std::declval<T>()+std::declval<typename list_view<F>::value_type>())> operator+(list_view<F> const & s) const {
                        list<decltype(std::declval<T>()+std::declval<typename list_view<F>::value_type>())> clone(data->size()+len(s));
                        std::copy(s.begin(), s.end(), std::copy(begin(), end(), clone.begin()));
                        return clone;
                    }

                list<T> operator+(empty_list const &) const {
                    return list<T>(begin(), end());
                }
                template<class F>
                    list<T> operator*(F const& t) const {
                        size_t n = t;
                        list<T> r(data->size()*n);
                        auto start = r.begin();
                        for(size_t i=0;i<n;i++, start+=data->size()) 
                            std::copy(this->begin(), this->end(),start);
                        return r;
                    }

                template <class F>
                    list<T>& operator+=(list<F> const & s) {
                        reserve(size()+s.size());
                        std::copy(s.begin(), s.end(), std::back_inserter(*this));
                        return *this;
                    }
                long size() const { return data->size(); }

                T pop(long x = -1) {
                    x = x%size();
                    if (x<0) x+=size();
                    T res = (*data)[x];
                    erase(x);
                    return res;
                }   


            };
        template<class T>
            boost::object_pool<typename list<T>::memory_size> list<T>::pool;


        /* empty list implementation */
        struct empty_list {
            template<class T> // just for type inference, should never been instantiated
                list<T> operator+(list<T> const & s) { return s; }
            empty_list operator+(empty_list const &) { return empty_list(); }
        };

        /* list_view implementation */
        template<class T>
            list_view<T>::list_view(list<T> & other, slice const &s):
                refcount(other.refcount), data(other.data), slicing(s) {
                    ++*refcount;
                    long lower, upper;
                    if(slicing.step<0) {
                        if( slicing.lower == std::numeric_limits<long>::max() )
                            lower = data->size();
                        else
                            lower = s.lower >= 0L ? s.lower : ( s.lower + data->size());
                        slicing.lower = std::max(0L,lower);
                        upper = slicing.upper >= 0L ? slicing.upper : ( slicing.upper + data->size());
                        slicing.upper = std::min(upper, (long)data->size());
                    }
                    else {
                        lower = slicing.lower >= 0L ? slicing.lower : ( slicing.lower + data->size());
                        slicing.lower = std::max(0L,lower);
                        upper = slicing.upper >= 0L ? slicing.upper : ( slicing.upper + data->size());
                        slicing.upper = std::min(upper, (long)data->size());
                    }
                }
        template<class T>
            list_view<T>& list_view<T>::operator=(list_view<T> const & s) {
                slicing=s.slicing;
                if(data != s.data) {
                    refcount=s.refcount;
                    data=s.data;
                    ++*refcount;
                }
                return *this;
            }

        template<class T>
            list_view<T>& list_view<T>::operator=(list<T> const & seq) {
                list<T> out;
                long lower = slicing.lower >= 0L ? slicing.lower : ( slicing.lower + data->size());
                lower = std::max(0L,lower);
                long upper = slicing.upper >= 0L ? slicing.upper : ( slicing.upper + data->size());
                upper = std::min(upper, (long)data->size());
                typename list<T>::iterator it = data->begin(); 
                if( slicing.step == 1) {
                    data->erase(it+lower, it + upper);
                    data->insert(it+lower, seq.begin(), seq.end());
                }
                else {
                    assert("not implemented yet");
                }
                if( data!= seq.data ) ++*refcount;
                return *this;
            }
        template<class T>
            list<T> list_view<T>::operator+(list_view<T> const & s) {
                assert(s.data);
                assert(data);
                list<T> out(size() + s.size());
                std::copy(s.begin(), s.end(), std::copy(begin(), end(), out.begin()));
                return out;
            }

    }

}
#endif

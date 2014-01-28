#ifndef PYTHONIC_TYPES_LONG_HPP
#define PYTHONIC_TYPES_LONG_HPP

#ifndef USE_GMP
typedef long long pythran_long_t;
#define pythran_long(a) pythran_long_t(a)
#else
#include <gmpxx.h>
typedef mpz_class pythran_long_t;
#define pythran_long(a) pythran_long_t(#a)
#endif


namespace pythonic {

    /* some math overloads { */
    template<class T0, class T1>
        auto mod(T0&& t0, T1&& t1) -> decltype( t0 % t1 ) {
            return t0 % t1;
        }

    template<class T, class U>
        auto floordiv(__gmp_expr<T,U> const& a, long b) -> decltype(a/b) {
            return a/b;
        }
    template<class T, class U, class Tp, class Up>
        auto floordiv(__gmp_expr<T,U> const& a, __gmp_expr<Tp,Up> const& b) -> decltype(a/b) {
            return a/b;
        }
    /* } */

    template<class T,class U>
        struct gmp_compo;

    template<class T>
        struct gmp_type;
    template<class T, class U>
        struct assignable<__gmp_expr<T,U> >
        {
            typedef typename gmp_compo<T,U>::type type;
            static_assert(!std::is_same<type,double>::value,"Cannot combine long and float.");
        };
    template<class T, class U>
        struct lazy<__gmp_expr<T,U> >
        {
            typedef typename assignable<__gmp_expr<T,U>>::type type;
        };

    template<class T>
        struct assignable<__gmp_expr<T,T> >
        {
            typedef typename gmp_type<T>::type type;
        };

    //GMP_COMPO

    template<class T, class U>
        struct gmp_compo
        {
            typedef typename gmp_compo<typename gmp_type<T>::type, typename gmp_type<U>::type>::type type;
        };

    template<>
        struct gmp_compo<long,double>
        {
            typedef double type;
        };

    template<>
        struct gmp_compo<double,long>
        {
            typedef double type;
        };

    template<>
        struct gmp_compo<mpz_class,long>
        {
            typedef mpz_class type;
        };

    template<>
        struct gmp_compo<long,mpz_class>
        {
            typedef mpz_class type;
        };

    template<>
        struct gmp_compo<double,mpz_class>
        {
            typedef double type;
        };

    template<>
        struct gmp_compo<mpz_class,double>
        {
            typedef double type;
        };

    template<class T>
        struct gmp_compo<double,T>
        {
            typedef double type;
        };

    template<class T>
        struct gmp_compo<T,double>
        {
            typedef double type;
        };

    template<class T>
        struct gmp_compo<long,T>
        {
            typedef typename gmp_type<T>::type type;
        };

    template<class T>
        struct gmp_compo<T,long>
        {
            typedef typename gmp_type<T>::type type;
        };

    template<class T>
        struct gmp_compo<mpz_class,T>
        {
            typedef typename gmp_type<T>::type type;
        };

    template<class T>
        struct gmp_compo<T,mpz_class>
        {
            typedef typename gmp_type<T>::type type;
        };

    template<class T>
        struct gmp_compo<T,T>
        {
            typedef typename gmp_type<T>::type type;
        };

    template<>
        struct gmp_compo<mpz_class, mpz_class>
        {
            typedef mpz_class type;
        };

    template<>
        struct gmp_compo<long,long>
        {
            typedef long type;
        };

    template<>
        struct gmp_compo<double,double>
        {
            typedef double type;
        };

    //GMP_TYPE

    template<class T>
        struct gmp_type
        {
            typedef T type;
        };

    template<>
        struct gmp_type<__mpz_struct [1]>
        {
            typedef mpz_class type;
        };

    template<class T, class U, class V>
        struct gmp_type<__gmp_binary_expr<T,U,V> >
        {
            typedef typename gmp_compo<T,U>::type type;
        };

    template<class T, class V>
        struct gmp_type<__gmp_unary_expr<T,V> >
        {
            typedef typename gmp_type<T>::type type;
        };

    template<class T, class U, class V>
        struct gmp_type<__gmp_unary_expr<__gmp_expr<T,U>,V> >
        {
            typedef typename gmp_compo<T,U>::type type;
        };

    template<class T, class U>
        struct gmp_type<__gmp_expr<T,U> >
        {
            typedef typename gmp_compo<T,U>::type type;
        };

    template<class T>
        struct gmp_type<__gmp_expr<T,T> >
        {
            typedef typename gmp_type<T>::type type;
        };

}
/* compute hash of a gmp { */
namespace std {
    template <class T, class U>
        struct hash<__gmp_expr<T,U>>
        {
            size_t operator()(__gmp_expr<T,U> const & x) const
            {
                return hash<std::string>()(x.get_str());
            }
        };
}

#include <boost/functional/hash_fwd.hpp>
    template <class T, class U>
std::size_t hash_value(__gmp_expr<T,U> const & x)
{
    return std::hash<__gmp_expr<T,U> >()(x);
}

/* } */
#ifdef ENABLE_PYTHON_MODULE
#include "pythonic/python/register_once.hpp"

namespace pythonic {

    template<>
        struct python_to_pythran<mpz_class>{
            python_to_pythran(){
                static bool registered =false;
                if(not registered) {
                    registered=true;
                    boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<mpz_class>());
                }
            }
            static void* convertible(PyObject* obj_ptr){
                if(!PyLong_Check(obj_ptr)) return 0;
                return obj_ptr;
            }
            static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
                void* storage=((boost::python::converter::rvalue_from_python_storage<mpz_class>*)(data))->storage.bytes;
                auto s = PyObject_Str(obj_ptr);
                new (storage) mpz_class(PyString_AsString(s));
                Py_DECREF(s);
                data->convertible=storage;
            }
        };
    struct custom_mpz_to_long {
        static PyObject* convert(const mpz_class& v){
            auto s = PyString_FromString(v.get_str().c_str());
            auto l = PyNumber_Long(s);
            Py_DECREF(s);
            return l;
        }
    };
    template<>
        struct pythran_to_python< mpz_class > {
            pythran_to_python() {
                register_once< mpz_class, custom_mpz_to_long >();
            }
        };
}

#endif

#endif

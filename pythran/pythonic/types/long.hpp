#ifndef PYTHONIC_TYPES_LONG_HPP
#define PYTHONIC_TYPES_LONG_HPP

#include "pythonic/include/types/long.hpp"

#ifndef USE_GMP
typedef long long pythran_long_t;
#define pythran_long(a) pythran_long_t(a)
#else
#include <gmpxx.h>
typedef mpz_class pythran_long_t;
#define pythran_long(a) pythran_long_t(#a)


namespace pythonic {

    /* some math overloads { */

    namespace operator_ {
        template<class T, class U, class T1>
            auto mod(__gmp_expr<T,U> const& t0, T1 const& t1) -> decltype( t0 % t1 )
            {
                return t0 % t1;
            }

        template<class T, class U>
            auto floordiv(__gmp_expr<T,U> const& a, long b) -> decltype(a/b)
            {
                return a/b;
            }

        template<class T, class U, class Tp, class Up>
            auto floordiv(__gmp_expr<T,U> const& a, __gmp_expr<Tp,Up> const& b) -> decltype(a/b)
            {
                return a/b;
            }
    }
    /* } */

}
/* compute hash of a gmp { */
namespace std {
    template <class T, class U>
        size_t hash<__gmp_expr<T,U>>::operator()(__gmp_expr<T,U> const & x) const
        {
            return hash<std::string>()(x.get_str());
        }
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

    python_to_pythran<mpz_class>::python_to_pythran()
    {
        static bool registered =false;
        if(not registered)
        {
            registered=true;
            boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id<mpz_class>());
        }
    }

    void* python_to_pythran<mpz_class>::convertible(PyObject* obj_ptr)
    {
        if(!PyLong_Check(obj_ptr))
            return 0;
        return obj_ptr;
    }

    void python_to_pythran<mpz_class>::construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
    {
        void* storage=((boost::python::converter::rvalue_from_python_storage<mpz_class>*)(data))->storage.bytes;
        auto s = PyObject_Str(obj_ptr);
        new (storage) mpz_class(PyString_AsString(s));
        Py_DECREF(s);
        data->convertible=storage;
    }

    PyObject* custom_mpz_to_long::convert(const mpz_class& v)
    {
        auto s = PyString_FromString(v.get_str().c_str());
        auto l = PyNumber_Long(s);
        Py_DECREF(s);
        return l;
    }

    pythran_to_python< mpz_class >::pythran_to_python()
    {
        register_once< mpz_class, custom_mpz_to_long >();
    }
}

#endif

#endif

#endif

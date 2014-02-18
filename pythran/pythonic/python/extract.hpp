#ifndef PYTHONIC_PYTHON_EXTRACT_HPP
#define PYTHONIC_PYTHON_EXTRACT_HPP

#include <boost/python/extract.hpp>

namespace pythonic {
    template<class T>
        struct _extract {
            T operator()(PyObject* obj) {
                return boost::python::extract<T>(obj);
            }
        };

    template<class T>
        inline auto extract(PyObject* obj) -> decltype(_extract<T>()(obj)){
            return _extract<T>()(obj);
        }

    /* some specializations */

    template<>
        struct _extract<long> {
            long operator()(PyObject* obj) {
                return PyInt_AS_LONG(obj);
            }
        };

    template<>
        struct _extract<double> {
            double operator()(PyObject* obj) {
                if(PyFloat_Check(obj))
                    return PyFloat_AS_DOUBLE(obj);
                else
                    return PyInt_AS_LONG(obj);
            }
        };
}

#endif

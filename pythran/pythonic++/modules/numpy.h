#ifndef PYTHONIC_MODULE_NUMPY_H
#define PYTHONIC_MODULE_NUMPY_H

#include <vector>

namespace pythonic {
    namespace numpy {

        template<class T>
            struct finalType
            {
                typedef T Type;
            };

        template<class T>
            struct finalType<core::list<T>>
            {
                typedef typename finalType<T>::Type Type;
            };

        template<class type>
            struct depth
            {
                enum { Value = 0 };
            };

        template<class type>
            struct depth<core::list<type>>
            {
                enum { Value = 1 + depth<type>::Value };
            };

        template<class... T, class type>
        core::ndarray<type,sizeof...(T)> build_array(core::list<type> const& prev_l, type const& val, T const& ...l)
            {
                core::ndarray<type, sizeof...(l)> a({l...});
                for(int i=0;i<prev_l.size(); i++)
                    a(i) = prev_l[i];
                return a;
            }

        template<class... T, class type>
        core::ndarray<typename finalType<type>::Type, depth<core::list<type>>::Value + sizeof...(T)> build_array(core::list<core::list<type> > const &prev_l, core::list<type> const& l, T const& ...s)
            {
                core::list<type> accumul(0);
                for(int i=0;i<prev_l.size(); i++)
                    for(int j=0; j<l.size(); j++)
                        accumul.push_back(prev_l[i][j]);
                return build_array(accumul, l[0], s..., l.size());
            }

        template<class type>
        core::ndarray<typename finalType<type>::Type, depth<core::list<type>>::Value> array(core::list<type> const& l)
            {
                return build_array(l, l[0], l.size());
            }

        PROXY(pythonic::numpy, array);
    }
}

#endif

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

        template<class... T>
            core::ndarray<double, sizeof...(T)> build_cst_array(double val, T... t)
            {
                core::ndarray<double, sizeof...(t)> a({t...});
                long size = 1;
                for(int i=0;i<sizeof...(t);i++)
                    size *= a.shape[i];
                for(int i=0;i<size; i++)
                    a(i)=val;
                return a;
            }

        template<int N>
            struct apply_to_tuple
            {
                template<typename... T, typename... S>
                    static core::ndarray<double, sizeof...(T)> builder(double val, std::tuple<T...>& t, S... s)
                    {
                        return apply_to_tuple<N-1>::builder(val, t, std::get<N-1>(t), s...);
                    }
            };

        template<>
            struct apply_to_tuple<0>
            {
                template<typename... T, typename... S>
                    static core::ndarray<double, sizeof...(T)> builder(double val, std::tuple<T...>& t, S... s)
                    {
                        return build_cst_array(val, s...);
                    }
            };

#define CST_ARRAY(NAME, VAL)\
        template<class... T>\
            core::ndarray<double, sizeof...(T)> NAME(std::tuple<T...> t)\
            {\
                return apply_to_tuple<sizeof...(T)-1>::builder(VAL, t, std::get<sizeof...(T)-1>(t));\
            }\
\
        core::ndarray<double,1> NAME(long size)\
        {\
            core::ndarray<double, 1> a({size});\
            for(int i=0;i<size;i++)\
                a(i)=VAL;\
            return a;\
        }

        CST_ARRAY(zeros, 0)

        PROXY(pythonic::numpy, zeros);

        CST_ARRAY(ones, 1)

        PROXY(pythonic::numpy, ones);
    }
}

#endif

#ifndef PYTHONIC_MODULE_NUMPY_H
#define PYTHONIC_MODULE_NUMPY_H

#include <vector>
#include <cmath>

namespace pythonic {
    namespace numpy {

        double const pi = 3.141592653589793238462643383279502884;
        double const e = 2.718281828459045235360287471352662498;


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
                    a.data->data[i] = prev_l[i];
                return a;
            }

        template<class... T, class type>
            core::ndarray<typename finalType<type>::Type, depth<core::list<type>>::Value + sizeof...(T)> build_array(core::list<core::list<type> > const &prev_l, core::list<type> const& l, T const& ...s)
            {
                core::list<type> accumul(0);
                for(size_t i=0;i<prev_l.size(); i++)
                    for(size_t j=0; j<l.size(); j++)
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
                return core::ndarray<double, sizeof...(t)>({t...}, val);
            }

        template<int N>
            struct apply_to_tuple
            {
                template<typename... T, typename... S>
                    static core::ndarray<double, sizeof...(T)> builder(double val, std::tuple<T...> const& t, S... s)
                    {
                        return apply_to_tuple<N-1>::builder(val, t, std::get<N-1>(t), s...);
                    }
            };

        template<>
            struct apply_to_tuple<0>
            {
                template<typename... T, typename... S>
                    static core::ndarray<double, sizeof...(T)> builder(double val, std::tuple<T...> const& t, S... s)
                    {
                        return build_cst_array(val, s...);
                    }
            };

#define NOT_INIT_ARRAY(NAME)\
        template<class... T>\
            core::ndarray<double, sizeof...(T)> NAME(std::tuple<T...> const& t)\
            {\
                return apply_to_tuple<sizeof...(T)-1>::builder(0, t, std::get<sizeof...(T)-1>(t));\
            }\
\
        template<unsigned long N>\
            core::ndarray<double, N> NAME(std::array<long, N> const &t)\
            {\
                return core::ndarray<double, N>(t);\
            }\
\
        core::ndarray<double,1> NAME(size_t size)\
        {\
            return core::ndarray<double, 1>({size});\
        }

NOT_INIT_ARRAY(zeros)

NOT_INIT_ARRAY(empty)


#define CST_ARRAY(NAME, VAL)\
        template<class... T>\
            core::ndarray<double, sizeof...(T)> NAME(std::tuple<T...> const& t)\
            {\
                return apply_to_tuple<sizeof...(T)-1>::builder(VAL, t, std::get<sizeof...(T)-1>(t));\
            }\
\
        template<unsigned long N>\
            core::ndarray<double, N> NAME(std::array<long, N> const &t)\
            {\
                return core::ndarray<double, N>(t);\
            }\
\
        core::ndarray<double,1> NAME(size_t size)\
        {\
            return core::ndarray<double, 1>({size}, VAL);\
        }

        PROXY(pythonic::numpy, zeros);

        CST_ARRAY(ones, 1)

        PROXY(pythonic::numpy, ones);

        PROXY(pythonic::numpy, empty);

        template<class T=long, class U, class V>
        core::ndarray<decltype(std::declval<U>()+std::declval<V>()+std::declval<T>()), 1> arange(U begin, V end, T step=T(1))
        {
            typedef decltype(std::declval<U>()+std::declval<V>()+std::declval<T>()) combined_type;
            size_t num = std::ceil((end - begin)/step);
            core::ndarray<combined_type, 1> a({num});
            if(num>0)
            {
                a[0] = begin;
                std::transform(a.data->data, a.data->data + num - 1, a.data->data + 1, std::bind(std::plus<combined_type>(), step, std::placeholders::_1));
            }
            return a;
        }

        core::ndarray<long, 1> arange(long end)
        {
            xrange xr(end);
            return core::ndarray<long, 1>(xr.begin(), xr.end());
        }

        PROXY(pythonic::numpy, arange);

        core::ndarray<double, 1> linspace(double start, double stop, size_t num=50, bool endpoint = true)
        {
            double step = (stop - start) / (num - endpoint);
            core::ndarray<double, 1> a({num});
            if(num>0)
                a[0] = start;
            std::transform(a.data->data, a.data->data + num - 1, a.data->data + 1, std::bind(std::plus<double>(), step, std::placeholders::_1));
            return a;
        }

        PROXY(pythonic::numpy, linspace);

        template<unsigned long N, class T>
        core::ndarray<double, N> sin(core::ndarray<T, N> const& a)
        {
            return core::ndarray<double,N>(a, (double (*)(double))std::sin);
        }

        using std::sin;
        PROXY(pythonic::numpy, sin);

        template<class... T, class type>
            core::ndarray<type,sizeof...(T)> build_cst_array_from_list(type cst, core::list<type> const& prev_l, type const& val, T const& ...l)
            {
                return core::ndarray<type, sizeof...(l)>({l...}, cst);
            }

        template<class... T, class type>
            core::ndarray<typename finalType<type>::Type, depth<core::list<type>>::Value + sizeof...(T)> build_cst_array_from_list(typename finalType<type>::Type cst, core::list<core::list<type> > const &prev_l, core::list<type> const& l, T const& ...s)
            {
                return build_cst_array_from_list(cst, l, l[0], s..., (size_t)l.size());
            }

        template<class type>
            core::ndarray<typename finalType<type>::Type, depth<core::list<type>>::Value> ones_like(core::list<type> const& l)
            {
                return build_cst_array_from_list(1, l, l[0], (size_t)l.size());
            }

        PROXY(pythonic::numpy, ones_like);

        template<class... T, class type>
            core::ndarray<type,sizeof...(T)> build_not_init_array_from_list(core::list<type> const& prev_l, type const& val, T ...l)
            {
                return core::ndarray<type, sizeof...(l)>({l...});
            }

        template<class... T, class type>
            core::ndarray<typename finalType<type>::Type, depth<core::list<type>>::Value + sizeof...(T)> build_not_init_array_from_list(core::list<core::list<type> > const &prev_l, core::list<type> const& l, T ...s)
            {
                return build_not_init_array_from_list(l, l[0], s..., (size_t)l.size());
            }

#define NOT_INIT_LIKE(NAME)\
        template<class type>\
            core::ndarray<typename finalType<type>::Type, depth<core::list<type>>::Value> NAME(core::list<type> const& l)\
            {\
                return build_not_init_array_from_list(l, l[0], (size_t)l.size());\
            }

        NOT_INIT_LIKE(zeros_like)
        PROXY(pythonic::numpy, zeros_like);

        NOT_INIT_LIKE(empty_like)
        PROXY(pythonic::numpy, empty_like);

        template<class T, unsigned long N, class ...S>
            core::ndarray<T,sizeof...(S)> reshape(core::ndarray<T,N> const& array, S ...s)
            {
                long shp[] = {s...};
                return core::ndarray<T,sizeof...(s)>(array.data, 0, shp);
            }

        PROXY(pythonic::numpy, reshape);

        template<class T, unsigned long N>
            core::ndarray<T,1> cumsum(core::ndarray<T,N> const& array)
            {
                core::ndarray<T,1> a({array.data->n});
                a.data->data[0] = array.data->data[0];
                std::transform(a.begin(), a.end()-1, array.data->data + 1, a.begin()+1, std::plus<T>());
                return a;
            }

        template<class T, unsigned int N>
        struct axis_helper
        {
            static core::ndarray<T,N> axis_cumsum( core::ndarray<T,N> const& array, long axis)
            {
                if(axis<0 || axis >=N)
                    throw ValueError("axis out of bounds");

                core::ndarray<T,N> a(*array.shape);
                if(axis==0)
                {
                    std::copy(array.data->data + *array.offset_data, array.data->data + *array.offset_data + (*array.shape)[N-1], a.data->data);
                    std::transform(a.begin(), a.end()-1, array.begin() + 1, a.begin() + 1, std::plus<core::ndarray<T,N-1>>());
                }
                else
                    std::transform(array.begin(), array.end(), a.begin(), std::bind(axis_helper<T,N-1>::axis_cumsum, std::placeholders::_1, axis-1));
                return a;
            }

            static typename std::remove_reference<typename core::ndarray_helper<T,N>::result_type>::type axis_sum( core::ndarray<T,N> const& array, long axis)
            {
                if(axis<0 || axis >=N)
                    throw ValueError("axis out of bounds");

                if(axis==0)
                {
                    core::ndarray<T,N> a(*(array.shape));
                    *a.begin() = *array.begin(); 
                    return std::accumulate(array.begin() + 1, array.end(), *a.begin());
                }
                else
                {
                    std::array<T,N-1> shp;
                    std::copy(array.shape->begin(), array.shape->end() - 1, shp.begin());
                    core::ndarray<T,N-1> a(shp);
                    std::transform(array.begin(), array.end(), a.begin(), std::bind(axis_helper<T,N-1>::axis_sum, std::placeholders::_1, axis-1));
                    return a;
                }
            }

            template<class Op>
            static typename std::remove_reference<typename core::ndarray_helper<T,N>::result_type>::type axis_minmax( core::ndarray<T,N> const& array, long axis, Op op)
            {
                if(axis<0 || axis>=N)
                    throw ValueError("axis out of bounds");

                if(axis==0)
                {
                    std::array<T,N-1> shp;
                    size_t size = 1;
                    for(auto i= array.shape->begin() + 1, j = shp.begin(); i<array.shape->end(); i++, j++)
                        size*=(*j = *i);
                    core::ndarray<T,N-1> a(shp);
                    core::ndarray_flat<T,N-1> a_iter(a);
                    std::copy(array.data->data + *array.offset_data, array.data->data + *array.offset_data + size, a_iter.begin());
                    for(auto i = array.begin() + 1; i<array.end(); i++)
                    {
                        auto next_subarray = *i;  //we need this variable to keep this ndarray alive while iter is used
                        core::ndarray_flat_const<T,N-1> iter(next_subarray);
                        auto k = a_iter.begin();
                        for(auto j = iter.begin(); j<iter.end(); j++)
                        {
                            *k=op(*k,*j);
                            k++;
                        }
                    }
                    return a;
                }
                else
                {
                    std::array<T,N-1> shp;
                    std::copy(array.shape->begin(), array.shape->end() - 1, shp.begin());
                    core::ndarray<T,N-1> a(shp);
                    std::transform(array.begin(), array.end(), a.begin(), std::bind(axis_helper<T,N-1>::axis_minmax, std::placeholders::_1, axis-1, op));
                    return a;
                }
            }
        };

        template<class T>
        struct axis_helper<T,1>
        {
            static core::ndarray<T,1> axis_cumsum( core::ndarray<T,1> const& array, long axis)
            {
                if(axis!=0)
                    throw ValueError("axis out of bounds");

                core::ndarray<T,1> a(*array.shape);
                std::copy(array.begin(), array.end(), a.begin());
                std::transform(a.begin(), a.end()-1, array.begin() + 1, a.begin() + 1, std::plus<T>());
                return a;
            }

            static T axis_sum( core::ndarray<T,1> const& array, long axis)
            {
                if(axis!=0)
                    throw ValueError("axis out of bounds");

                return std::accumulate(array.begin(), array.end(), 0);
            }

            template<class Op>
            static T axis_minmax( core::ndarray<T,1> const& array, long axis, Op op)
            {
                if(axis!=0)
                    throw ValueError("axis out of bounds");

                T res = *array.begin();
                for(auto i = array.begin() + 1; i<array.end(); i++)
                    res = op(res, *i);
                return res;
            }
        };

        template<class T, unsigned long N>
            core::ndarray<T,N> cumsum( core::ndarray<T,N> const& array, long axis)
            {
                return axis_helper<T,N>::axis_cumsum(array, axis);
            }

        PROXY(pythonic::numpy, cumsum);

        template<class T, unsigned long N>
            T min(core::ndarray<T,N> const& array)
            {
                core::ndarray_flat_const<T,N> iter(array);
                T res = *iter.begin();
                for(auto i = iter.begin() + 1; i<iter.end(); i++)
                    res = std::min(res, *i);
                return res;
            }

        double __min(double a, double b) { return std::min(a,b); }
        float __min(float a, float b) { return std::min(a,b); }
        long __min(long a, long b) { return std::min(a,b); }
        long long __min(long long a, long long b) { return std::min(a,b); }
        unsigned long __min(unsigned long a, unsigned long b) { return std::min(a,b); }
        unsigned long long __min(unsigned long long a, unsigned long long b) { return std::min(a,b); }

        template<class T, unsigned long N>
            typename std::remove_reference<typename core::ndarray_helper<T,N>::result_type>::type min( core::ndarray<T,N> const& array, long axis)
            {
                return axis_helper<T,N>::axis_minmax(array, axis, (T (*)(T,T))__min);
            }

        PROXY(pythonic::numpy, min);

        template<class T, unsigned long N>
            T sum(core::ndarray<T,N> const& array)
            {
                core::ndarray_flat_const<T,N> iter(array);
                return std::accumulate(iter.begin(), iter.end(), 0);
            }

        template<class T, unsigned long N>
            typename std::remove_reference<typename core::ndarray_helper<T,N>::result_type>::type sum( core::ndarray<T,N> const& array, long axis)
            {
                return axis_helper<T,N>::axis_sum(array, axis);
            }

        PROXY(pythonic::numpy, sum);

        template<class T, unsigned long N>
            bool all(core::ndarray<T,N> const& array)
            {

                core::ndarray_flat_const<T,N> iter(array);
                return pythonic::all(iter);
            }

        PROXY(pythonic::numpy, all);
    }
}

#endif

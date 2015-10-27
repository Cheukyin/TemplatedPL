#ifndef UTILS_H_
#define UTILS_H_

namespace CYTL
{
    namespace UTIL
    {
        // ----------------------------------------------
        // Static Checker
        template<bool> struct ComileTimeCheck;
        template<> struct ComileTimeCheck<true> {};

        template<class T1, class T2> struct StaticCheckEQ;
        template<class T> struct StaticCheckEQ<T, T> {};


        // -----------------------------------------
        // Int2Type
        template<int N> 
        struct Int2Type
        { const int v = N; };


        // -----------------------------------------
        // list
        template<class T, class... T_Rest> struct List;

        // List.N
        template<class T, int N> struct ListRef;
        template<class T, class... T_Rest, int N>
        struct ListRef<List<T, T_Rest...>, N>
        {
            typedef typename ListRef<List<T_Rest...>, N-1>::value value;
        };
        template<class T, class... T_Rest>
        struct ListRef<List<T, T_Rest...>, 0>
        { typedef T value; };
    }
}

#endif //UTILS_H_
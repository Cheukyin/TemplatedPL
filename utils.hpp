#ifndef UTILS_H_
#define UTILS_H_

namespace CYTL
{
    namespace UTIL
    {
        //---------------------------------------------
        // EmptyType
        struct EmptyType;


        // ----------------------------------------------
        // Static Checker
        template<bool> struct ComileTimeCheck;
        template<> struct ComileTimeCheck<true> {};

        template<class T1, class T2> struct StaticCheckEQ;
        template<class T> struct StaticCheckEQ<T, T> {};


        // -----------------------------------------
        // IsEQ
        template<class T1, class T2> 
        struct IsEQ
        { static const bool value = false; };
        template<class T> 
        struct IsEQ<T, T>
        { static const bool value = true; };


        // -----------------------------------------
        // Int2Type
        template<int N> 
        struct Int2Type
        { static const int v = N; };


        // ------------------------------------
        // Select
        template<bool B, class T1, class T2> struct Select;
        template<class T1, class T2>
        struct Select<true, T1, T2>
        { typedef T1 value; };
        template<class T1, class T2>
        struct Select<false, T1, T2>
        { typedef T2 value; };


        // ------------------------------------
        // enable_if
        template<bool B, class T> struct enable_if;
        template<class T>
        struct enable_if<true, T>
        { typedef T type; };
    }
}

#endif //UTILS_H_
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


        // ------------------------------------------
        // NotEQ
        template<class T1, class T2>
        struct NotEQ
        { static const bool value = true; };
        template<class T>
        struct NotEQ<T, T>
        { static const bool value = false; };


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
        // Enable_If
        template<bool B, class T> struct Enable_If;
        template<class T>
        struct Enable_If<true, T>
        { typedef T type; };


        // ---------------------------------
        // Cons
        template<class Head, class Tail> struct Cons;

        // Car
        template<class Pair> struct Car;
        template<class Head, class Tail>
        struct Car< Cons<Head, Tail> >
        { typedef Head value; };

        // Cdr
        template<class Pair> struct Cdr;
        template<class Head, class Tail>
        struct Cdr< Cons<Head, Tail> >
        { typedef Tail value; };


        // -------------------------------
        // TypeList
        template<class Head, class... Tail>
        struct TypeList
        { typedef Cons< Head, typename TypeList<Tail...>::value > value; };
        template<class Head>
        struct TypeList<Head>
        { typedef Cons<Head, EmptyType> value; };
    }
}

#endif //UTILS_H_
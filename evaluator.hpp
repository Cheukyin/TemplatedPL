#include "utils.hpp"

#ifndef EVALUATOR_H_
#define EVALUATOR_H_

namespace TPL
{
    using namespace CYTL::UTIL;

    // ----------------------------
    // Data Type
    template<int N> struct Int;
    template<bool B> struct Bool;
    struct Unit;

    // -----------------------------
    // Add
    template<class T1, class T2> struct Add;
    template<int N1, int N2>
    struct Add< Int<N1>, Int<N2> >
    { typedef Int<N1+N2> value; };


    // ----------------------------------
    // Comparing
    template<class T1, class T2> struct IsGreater;
    template<int N1, int N2>
    struct IsGreater< Int<N1>, Int<N2> >
    { typedef Bool<(N1>N2)> value; };

    template<class T1, class T2> struct IsLess;
    template<int N1, int N2>
    struct IsLess< Int<N1>, Int<N2> >
    { typedef Bool<(N1<N2)> value; };

    template<class T1, class T2> struct IsEqual;
    template<int N1, int N2>
    struct IsEqual< Int<N1>, Int<N2> >
    { typedef Bool<(N1==N2)> value; };


    // ------------------------------------
    // Pair
    template<class T1, class T2> struct Pair;
    
    template<class T>struct Fst;
    template<class T1, class T2>
    struct Fst< Pair<T1, T2> >
    { typedef T1 value; };

    template<class T>struct Snd;
    template<class T1, class T2>
    struct Snd< Pair<T1, T2> >
    { typedef T2 value; };
}

#endif //EVALUATOR_H_
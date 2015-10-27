#include "utils.hpp"

#ifndef EVALUATOR_H_
#define EVALUATOR_H_

namespace TPL
{
    // ----------------------------
    // Basic Data Type
    template<int N> struct Int;
    template<bool B> struct Bool;
    template<int N> struct Var;
    struct Unit;


    // -----------------------------
    // Add
    template<class T1, class T2> struct Add;
    template<int N1, int N2>
    struct Add< Int<N1>, Int<N2> >
    { typedef Int<N1+N2> value; };


    // ----------------------------------
    // Comparing

    // >
    template<class T1, class T2> struct IsGreater;
    template<int N1, int N2>
    struct IsGreater< Int<N1>, Int<N2> >
    { typedef Bool<(N1>N2)> value; };

    // <
    template<class T1, class T2> struct IsLess;
    template<int N1, int N2>
    struct IsLess< Int<N1>, Int<N2> >
    { typedef Bool<(N1<N2)> value; };

    // ==
    template<class T1, class T2> struct IsEqual;
    template<int N1, int N2>
    struct IsEqual< Int<N1>, Int<N2> >
    { typedef Bool<(N1==N2)> value; };


    // ------------------------------------
    // Pair
    template<class T1, class T2> struct Pair;
    
    // Pair.1
    template<class T>struct Fst;
    template<class T1, class T2>
    struct Fst< Pair<T1, T2> >
    { typedef T1 value; };

    // Pair.2
    template<class T>struct Snd;
    template<class T1, class T2>
    struct Snd< Pair<T1, T2> >
    { typedef T2 value; };


    // -----------------------------------
    // List
    template<class T, class... T_Rest> struct List;

    // List.N
    template<class T, class N> struct ListRef;
    template<class T, class... T_Rest, int N>
    struct ListRef< List<T, T_Rest...>, Int<N> >
    { typedef typename ListRef< List<T_Rest...>, Int<N-1> >::value value; };
    template<class T, class... T_Rest>
    struct ListRef< List<T, T_Rest...>, Int<0> >
    { typedef T value; };
    

    // ------------------------------------
    // if-then-else
    template<class Cond, class T1, class T2> struct If_Then_Else;
    template<class T1, class T2>
    struct If_Then_Else<Bool<true>, T1, T2>
    { typedef T1 value; };
    template<class T1, class T2>
    struct If_Then_Else<Bool<false>, T1, T2>
    { typedef T2 value; };


    //--------------------------------------
    // Env
    
}

#endif //EVALUATOR_H_
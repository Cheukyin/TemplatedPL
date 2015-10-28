#include "utils.hpp"

#ifndef EVALUATOR_H_
#define EVALUATOR_H_

namespace TPL
{
    using CYTL::UTIL::enable_if;
    using CYTL::UTIL::EmptyType;

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
    template<class T, class... T_Rest> 
    struct List
    { typedef Pair< T, typename List<T_Rest...>::value > value; };
    template<class T>
    struct List<T>
    { typedef Pair<T, Unit> value; };

    //IsList
    template<class T>
    struct IsList
    { static const bool value = false; };
    template<class T1, class T2>
    struct IsList< Pair<T1, T2> >
    { static const bool value = IsList<T2>::value; };
    template<class T>
    struct IsList< Pair<T, Unit> >
    { static const bool value = true; };
    template<>
    struct IsList<Unit>
    { static const bool value = true; };

    // List.N
    template<class T, class N> struct ListRef;
    template<class T1, class T2, int N>
    struct ListRef< Pair<T1, T2>, Int<N> >
    { typedef typename ListRef< T2, Int<N-1> >::value value; };
    template<class T1, class T2>
    struct ListRef< Pair<T1, T2>, Int<0> >
    {
        typedef typename enable_if<IsList<T2>::value, T2>::type islist;
        typedef T1 value;
    };

    // ListAppend
    template<class L, class NewT> struct ListAppend;
    template<class H, class T, class NewT>
    struct ListAppend<Pair<H, T>, NewT>
    { typedef Pair< H, typename ListAppend<T, NewT>::value > value; };
    template<class NewT>
    struct ListAppend<Unit, NewT>
    { typedef Pair<NewT, Unit> value; };
    
    
    // ------------------------------------
    // if-then-else
    template<class Cond, class T1, class T2> struct If_Then_Else;
    template<class T1, class T2>
    struct If_Then_Else<Bool<true>, T1, T2>
    { typedef T1 value; };
    template<class T1, class T2>
    struct If_Then_Else<Bool<false>, T1, T2>
    { typedef T2 value; };


    // --------------------------------------
    // VarValList
    struct EmptyVarValList;
    template<class Varible, class Val, class Tail> struct VarValList;
    template<class Varible, class Val>
    struct VarValList<Varible, Val, EmptyVarValList>;

    // VarValListExtend
    template<class Varible, class Val, class L>
    struct VarValListExtend
    { typedef VarValList<Varible, Val, L> value; };

    // VarValListLookup
    template<class V, class L> struct VarValListLookup;
    template<class V, class Varible, class Val, class Tail> // Search next Node
    struct VarValListLookup< V, VarValList<Varible, Val, Tail> >
    { typedef typename VarValListLookup<V, Tail>::value value; };
    template<class V, class Val, class Tail> // V found
    struct VarValListLookup< V, VarValList<V, Val, Tail> >
    { typedef Val value; };
    template<class V> // till the end, nothing is found
    struct VarValListLookup<V, EmptyVarValList>
    { typedef EmptyType value; };


    // -------------------------------------------------
    // Env
    struct EmptyEnv;
    template<class Head, class Tail> struct Env;
    template<class T> struct Env<T, EmptyEnv>;

    // EnvExtend
    template<class Head, class E> 
    struct EnvExtend
    { typedef Env<Head, E> value; };
}

#endif //EVALUATOR_H_
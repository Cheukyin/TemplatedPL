#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "evaluator.hpp"

// Expression
namespace TPL
{
    // Eval
    using internal::Eval;          // Eval<Exp>

    // Basic Data Type
    using internal::Int;           // Int<N>
    using internal::Bool;          // Bool<N>
    using internal::Var;           // Var<N>
    using internal::Unit;          // Unit

    // Add
    using internal::Add;           // Add<E1, E2>
    // Mul
    using internal::Mul;           // Mul<E1, E2>
    // Mod
    using internal::Mod;           // Mod<E1, E2>

    // >
    using internal::IsGreater;     // IsGreater<E1, E2>
    // <
    using internal::IsLess;        // IsLess<E1, E2>
    // ==
    using internal::IsEqual;       // IsEqual<E1, E2>
    // IsUnit
    using internal::IsUnit;        // IsUnit<E>

    // Pair type
    using internal::Pair;          // Pair<E1, E2>
    // IsPair
    using internal::IsPair;        // IsPair<E>
    // Pair.1
    using internal::Fst;           // Fst<P>
    // Pair.2
    using internal::Snd;           // Snd<P>

    // List type
    using internal::List;          // List<E, ERest...>

    // If_Then_Else
    using internal::If_Then_Else;  // If_Then_Else<Cond, E1, E2>

    // ParamList
    using internal::ParamList;     // ParamList< Var<N1>, Var<N>... >
    // Lambda
    using internal::Lambda;        // Lambda< Param< Var<N1>, Var<N>... >,
                                   //         Body >

    // Call
    using internal::Call;          // Call< Func, Val0, ValRest... >

    // CallCC
    using internal::CallCC;        // CallCC< Lambda< ParamList< Var<K> >,
                                   //                 BOdy > >

} // namespace TPL

#endif //EXPRESSION_H_
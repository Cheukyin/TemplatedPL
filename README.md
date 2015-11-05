# TemlatedPL
TemplatedPL(TPL) is a DSL built upon C++ template,  
therefore, all evaluations of expressions in TPL would be accomplished at compile time.  
  
Essentially, TPL is a simple Lisp Interpreter,  
which supports `Lexical Closure`, `Multi-Parameter Lambda Expression`  
and `First Class Continuation(call/cc)`.  
   
TPL, however, doesn't support `Named Function`,  
so you must write a `Y-Combinator` to implement recursive functions.  
Fortunately, the common higher-order functions(`YCombinator, Map, Reduce, Filter`, etc)  
and some frequently-used recursive functions have been provided as library functions in `lib.hpp`.  
  
Because the code of the interpreter is heavily written in `Continuation-Passing-Style(CPS)`,  
you may find it difficult to understand if you have no experience in writing a lisp-like interpreter,  
I recommend you to read Chapter 4 in `SICP` && Chapter 5 in `EOPL`.  
If you want to learn more Template-Meta-Programming skills, you should read Chapter 2&&3 in `Modern C++ Design`.

## Source Code Structure
* `evaluator.hpp`: the core of the interpreter of TPL
* `evaluator-test.hpp`: unittest of the interpreter
* `lib.hpp`: provides some common higher-order functions and recursive functions(`Y-Combinator, Map, Reduce, Filter`, etc)
* `examples.cpp`: example codes of TPL

## Sample Codes of TPL
* Sum of Even Numbers Between 1 to 10: `Sum( Filter( Range(1, 10), (λx. x%2 == 0) ) )`
```C++
cout<< Eval< Call< Lib::Sum, Call< Lib::Filter,
                                   Call< Lib::Range, Int<1>, Int<10> >,
                                   Lambda< ParamList< Var<0> >,
                                           IsEqual< Mod< Var<0>, Int<2> >,
                                                    Int<0> > > > > >::value::value;
```

* Definition of `Y-Combinator`: `λf.( λx.(f λy. ((x x) y)) λx.(f λy.((x x) y)) )` 
```C++
typedef Lambda< ParamList< Var<0> >,
                Call< Lambda< ParamList< Var<1> >,
                              Call< Var<0>,
                                    Lambda< ParamList< Var<2> >,
                                            Call< Call< Var<1>, Var<1> >,
                                                  Var<2> > > > >,
                      Lambda< ParamList< Var<1> >,
                              Call< Var<0>,
                                    Lambda< ParamList< Var<2> >,
                                            Call< Call< Var<1>, Var<1> >,
                                                  Var<2> > > > > > >
        YCombinater;
```

* `call/cc` Example: `((λk. (k λk.2)) (call/cc λk.k))` = 2
```C++
cout<< Eval< Call< Lambda< ParamList< Var<0> >,
                           Call< Var<0>,
                                 Lambda< ParamList< Var<0> >,
                                         Int<2> > > >,
                   CallCC< Lambda< ParamList< Var<0> >,
                                   Var<0> > > > >::value::value;
```

## Build && Dependency
* Header Only，see `examples.cpp` for specific usage
* The compiler must support `C++11`, codes have been tested on `g++ 4.8.4` and `clang++ 3.4`
* Since TPL is totally built on C++ template, the default template-recursion-depth is not enough,  
  you should set `-ftemplate-depth-2000` flag if you use g++ or clang++ to make sure  
  the template-recursion-depth is deep enough for the example codes.
* `Linux`: After `git clone`，`cmake . && make`，then `./bin/examples` to run the example code
* `Windows`: It may work in VS if there's no template-recursion-depth limit in VS, but I have not tried it yet
 
## Basic Types
* Interger: `Int<N>`
* Bool:     `Bool<B>`
* Variable: `Var<N>`
* Pair:     `Pair<E1, E2>`
* List:     `List<E0, EN...>`(equivalent to `<Pair E1 Pair<..., Pair<Ek, Unit>...>`)
* Unit:     `Unit`(equivalent to `void` in other languages)
* Lambda:   `Lambda< ParamList< Var<0>, Var<N>... >, Body >`

## Basic Expressions
* +: `Add<E1, E2>`
* *:  `Mul<E1, E2>`
* %: `Mod<E1, E2>`
* >: `IsGreater<E1, E2>`
* <: `IsLess<E1, E2>`
* =: `IsEqual<E1, E2>`
* Pair.1: `Fst<E>`
* Pair.2: `Snd<E>`
* Conditional Branching: `If_Then_Else<Cond, E1, E2>`
* Test if it's a Pair: `IsPair<E>`
* Test if it's a Unit: `IsUnit<E>`
* Function Call: `Call<Func, Val0, ValN...>`
* call/cc: `CallCC< Lambda< ParamList< Var<K> >, Body > >`, used to capture the current continuation

## Library Functions
The Following Functions are provided in `lib.hpp`:
* `YCombinator`: The famous Y-Combinator which is used to implement anonymous recursions
* `Reduce`: Combine the elements of a list under the specific operation
* `Map`: Apply an operation to each element in a list, then return the resulted list
* `Filter`: Filter the elements of a list under the specific condition
* `Range`: Generate a list containing 1 to N
* `Sum`: Calculate the sum of the list
* `IsList`: Test if it is a List
* `ListRef`: Return the Nth element of a list(starts from 0)
* `ListAppend`: Append an element to a list
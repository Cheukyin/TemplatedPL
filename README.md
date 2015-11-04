# TemlatedPL
master分支已实现call/cc, 并采用CPS变换重写整个解释器, 请切换至该分支查看.  
  
TemplatedPL简称TPL，是一门构建在C++模板上的DSL，  
因此, TPL所有表达式的计算均在编译期完成.  
  
TPL本质上是一个极简的lisp解释器，支持词法闭包, 多参匿名函数，  
不支持具名函数, 不过可通过构造`Y-Combinator`实现递归，   
常用的高阶函数(如`Y-Combinator, Map, Reduce, Filter`等)均已在`lib.hpp`以库的形式提供

## 源码主要结构
* `evaluator.hpp`: 解释器实现核心
* `evaluator-test.hpp`: 解释器单元测试
* `lib.hpp`: 实现常用的高阶函数(如`Y-Combinator, Map, Reduce, Filter`等)
* `examples.cpp`: TemplatedPL代码示例

## TPL示例
计算1到10偶数的和: 等价于`Sum( Filter( Range(1, 10), (λx. x%2 == 0) ) )`
```C++
cout<< Eval< Call< Lib::Sum, Call< Lib::Filter,
                                   Call< Lib::Range, Int<1>, Int<10> >,
                                   Lambda< ParamList< Var<0> >,
                                           IsEqual< Mod< Var<0>, Int<2> >,
                                                    Int<0> > > > > >::value::value;
```
定义`Y-Combinator`: 等价于`λf.( λx.(f λy. ((x x) y)) λx.(f λy.((x x) y)) )` 
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

## Build && Dependency
* Header Only，具体用法参见`examples.cpp`
* 编译器需要支持C++11，除此之外无其他(已在`VS2013, g++ 4.8.2, clang++ 3.4`上通过测试)
* `git clone`后，可 `cmake . && make`，然后`./bin/examples`运行示例程序
 
## 基本类型
* Interger: `Int<N>`
* Bool:     `Bool<B>`
* Variable: `Var<N>`
* Pair:     `Pair<E1, E2>`
* List:     `List<E0, EN...>`
* Unit:     `Unit`
* Lambda:   `Lambda< ParamList< Var<0>, Var<N>... >, Body >`

## 基本表达式
* +: `Add<E1, E2>`
* *:  `Mul<E1, E2>`
* %: `Mod<E1, E2>`
* >: `IsGreater<E1, E2>`
* <: `IsLess<E1, E2>`
* =: `IsEqual<E1, E2>`
* Pair.1: `Fst<E>`
* Pair.2: `Snd<E>`
* List.N: `ListRef<L, N>`
* ListAppend: `ListAppend<L, E>`
* Conditional Branching: `If_Then_Else<Cond, E1, E2>`
* Test is a List: `IsList<E>`
* Test is a Unit: `IsUnit<E>`
* Function Call: `Call<Func, Val0, ValN...>`

## 库函数
`lib.hpp`主要实现了常用的高阶函数：
* `YCombinater`: Y组合子，用于实现匿名递归
* `Reduce`: 归约
* `Map`: 映射
* `Filter`: 过滤
* `Range`: 生成从1到N的List
* `Sum`: 计算List的和

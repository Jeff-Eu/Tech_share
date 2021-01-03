# Kotlin
* [Scope Functions](https://kotlinlang.org/docs/reference/scope-functions.html#let)
    * There are five of them: `let`, `run`, `with`, `apply`, and `also`.
    * The scope functions do not introduce any new technical capabilities, but they can make your code more concise and readable.
    * `this`
        * `run`, `with`, and `apply` refer to the context object as a lambda receiver - by keyword `this`.
        * 這類scope function裡面寫的程式，如果需要存取物件的members，就可以當作平常寫class存取members的寫法一樣，this就是參照自己物件的members，並且this也可以省略，但它的this是指這被初始化的物件，而非外部的物件，所以不熟的人可能會搞混。)
            ```java kotlin
            val adam = Person("Adam").apply { 
                age = 20  // same as this.age = 20 or adam.age = 20
                city = "London"
            }
            println(adam)
            ```
    * `it`
        * ...

* data, class, object 差異

* 函數的參數初始化 (跟 C#很像)
    ```java kotlin
    fun test(a: Int = 22, b: Int = 44) {
        println("a: ${a}, b: ${b}")
    }

    test()
    test(b = 33, a = 11) // 指定參數 a與 b的值，不一定要按照函式參數的先後順序

    /* output:
        a: 22, b: 44
        a: 11, b: 33
    */
    ```
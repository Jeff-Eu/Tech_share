# [C++ Inheritance](https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm)
* 這節介紹會跟 C++ Virtual Table有關，下面有reference可參考
    * https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/
    * https://en.wikipedia.org/wiki/Virtual_method_table

* Code
    ```c++
    class derived-class: access-specifier base-class
    ```
    Where access-specifier is one of `public`, `protected`, or `private`, and base-class is the name of a previously defined class. If the access-specifier is not used, then it is private by default.

* Code: 一般的繼承
    ```c++
    #include <iostream>
    using namespace std;

    class Base {
        public:
            void print() { cout<<"Base"<<endl; }
    };

    class Child : public Base {
        public:
            void print() { cout<<"Child"<<endl; }
    };

    int main()
    {
        Child c;
        Base b = c, *b1 = &c, *b2 = new Child();

        b.print(); // Base
        b1->print(); // Base
        b2->print(); // Base
        
        return 0;
    }
    ```
    
* Code: 承上，將 Base的 print 前面加 `virtual`
    ```c++
    #include <iostream>
    using namespace std;

    class Base {
        public:
            virtual void print() { cout<<"Base"<<endl; }
    };

    class Child : public Base {
        public:
            void print() { cout<<"Child"<<endl; }
    };

    int main()
    {
        Child c;
        Base b = c, *b1 = &c, *b2 = new Child();

        b.print(); // Base
        b1->print(); // Child
        b2->print(); // Child
        
        return 0;
    }
    ```
* Code: constructor/destructor問題
    ```c++
    #include <iostream>

    using namespace std;

    class Base {
        public:
            Base() { cout<<"Base construct"<<endl; }
            ~Base() { cout<<"Base destruct"<<endl; }
    };

    class Child : public Base {
        public:
            Child() { cout<<"Child construct"<<endl; }
            ~Child() { cout<<"Child destruct"<<endl; }
    };

    int main()
    {
        Base* b = new Child();
        delete b;
        
        return 0;
    }
    // 此程式碼會印出:
    // Base construct
    // Child construct
    // Base destruct
    ``` 
    造成 memory leak，正確的寫法應該要在 ~Base() 前面加 virtual，這樣 ~Child()才會被呼叫

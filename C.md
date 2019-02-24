# C Language
- swprintf_s 是比 sprintf 還安全的寫法，它會跳錯誤訊息
	- ex: [int 轉 wchar_t](https://stackoverflow.com/a/15109886/1613961)

- malloc與 calloc的差異 ( 這兩連結可以學到陣列有兩種取值的方法 arr[i] 及 *(arr + i) )
	- https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm
	- https://openhome.cc/Gossip/CGossip/MallocFree.html

- What is the purpose of the keyword typedef?
	=> It is used to alias the existing type. Also used to simplify the complex declaration of the type.
- What is the difference between variable declaration and variable definition?
	=> Declaration associates type to the variable whereas definition gives the value to the variable.

- 位元運算
	- 在位元運算上，C 還有左移（<<）與右移（>>）兩個運算子，左移運算子會將所有的位元往左移指定的位數，左邊被擠出去的位元會被丟棄，而右邊會補上 0；右移運算則是相反，會將所有 的位元往右移指定的位數，右邊被擠出去的位元會被丟棄，至於左邊位元補 0 或補 1 則不一定，When >> performed on a signed type, the result is technically undefined and compiler dependant, however most compilers will perform an arithmetic shift, causing the blank to be filled with the sign bit of the left operand.
	- 題目: http://www.sanfoundry.com/tricky-c-questions-bitwise-operators/
		- 有做錯的
			- 第1節: 4有陷阱; 
				- [第6題解釋](https://stackoverflow.com/questions/8225776/why-does-sizeofx-not-increment-x)
				- [第8題解釋(重要)](https://stackoverflow.com/questions/3238482/pointer-subtraction-confusion)
			- 第2節: 1,2,5, 6沒錯;但跟5有關, 
	- 一個負數的二補數就是其對應的正數

- Operation
	- [LHS first v.s. RHS first](https://books.google.com.tw/books?id=8fXCn3E864sC&pg=PA173&lpg=PA173&dq=c%2B%2B+left-hand+operand+first&source=bl&ots=BG1vBNpbzT&sig=ZjDSSBP7FtEG9R27wsMxyOvYzX4&hl=zh-TW&sa=X&ved=0ahUKEwiQxIqg6a7VAhVCJ5QKHeEIBxQQ6AEIUTAF#v=onepage&q=c%2B%2B%20left-hand%20operand%20first&f=false)

- Does a built-in header file contains built-in function definition?
  =>No, the header file only declares function. The definition is in library which is linked by the linker.

- What is a preprocessor?
  => Preprocessor is a directive to the compiler to perform certain things before the actual compilation process begins.

- Threading:
	- what are processes ?
		- ref: https://www.codeproject.com/Articles/26148/Beginners-Guide-to-Threading-in-NET-Part-of-n
		- [摘錄] An application may launch more than one process. It's important to note that applications and processes are not the same thing at all.
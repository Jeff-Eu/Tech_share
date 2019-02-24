# C++ Language

### 在C++使用UWP API
UWP C++會大量使用非同步寫法，這之中包含許多以C++11標準為主的較新技術，這邊列出閱讀參考的先後順序：
  
  - C++預備知識
    - [What is this weird colon-member (“ : ”) syntax in the constructor?](https://stackoverflow.com/questions/1711990/what-is-this-weird-colon-member-syntax-in-the-constructor)
    - [Meaning of “const” last in a C++ method declaration?](https://stackoverflow.com/questions/751681/meaning-of-const-last-in-a-c-method-declaration)
  - C++ Functors
    - [C++ TUTORIAL - FUNCTORS(FUNCTION OBJECTS) I](http://www.bogotobogo.com/cplusplus/functor_function_object_stl_intro.php)，關於Functors，這作者用三篇文章討論
        - 上面這篇的最後會用到`std::transform`這STL的函式當例子，[這篇文章](https://www.fluentcpp.com/2017/02/13/transform-central-algorithm/)解釋的不錯

  - Lambda Expression
    - [C++11 Lambda Expression 語法教學與範例](https://blog.gtwang.org/programming/lambda-expression-in-c11/)
    - [Examples of Lambda Expressions](https://docs.microsoft.com/en-us/cpp/cpp/examples-of-lambda-expressions)
  
  - C++非同步呼叫
    - [UWP上c#, js, c++的非同步寫法比較](https://docs.microsoft.com/en-us/windows/uwp/threading-async/asynchronous-programming-universal-windows-platform-apps)，看裡面的語言比較表格即可
    - [js上使用Promise, then的非同步寫法](http://huli.logdown.com/posts/292655-javascript-promise-generator-async-es6)
    

    - [Asynchronous programming in C++](https://docs.microsoft.com/en-us/windows/uwp/threading-async/asynchronous-programming-in-cpp-universal-windows-platform-apps)
    - [Async programming patterns and tips in Hilo (Windows Store apps using C++ and XAML)](https://msdn.microsoft.com/library/windows/apps/jj160321.aspx)

### 在Win32上使用UWP API

- [Calling Windows 10 APIs From a Desktop Application](https://blogs.windows.com/buildingapps/2017/01/25/calling-windows-10-apis-desktop-application/#yZRleFvuhkBzpVFy.97)

注意如果出現 *Error msg: '/clr' and '/ZW' command-line options are incompatible* ，可以將使用到 UWP 的 api 程式碼獨立抽出來放到新的cpp，並且只針對該cpp設定檔的 `C/C++` &rarr; `General` &rarr; `Consume Windows Runtime Extension` 改設成 `Yes(/ZW)`

### 使用 DLL
* 快速回憶/建立C++ dynamic dll及C++的Test_dll.exe專案
    * C++ dynamic dll專案：
        * 直接新增c++空白專案即可
        * Configuration Type 從 Application.exe 改為 Dynamic Library (.dll)
        * C/C++ => Preprocessor => Preprocessor Definitions
        * 記得加上post script，複製dll到使用他們的project
    * Test_dll.exe 專案：修改3個屬性設定
        1. C/C++ => General => Additional Include Directories // 這項不設也可從code中去設，加相對路徑，會有intelligence也很方便(比從屬性加更快一點，也不用各別設定x86/x64及debug/release)
        2. Linker => General => Additional Library Directories
        3. Linker => Input => Additional Dependencies
        * 注意因為要分別設定 Debug/Release 與 x86/x64 共四種組合，所以可以先從All Configurations 及 All Platforms 開始設定(1,)3，降子的話這些最少只要設一次，但2就要分別去對All Configurations的 x86 及 x64 設定不同的folder位置，因此最少會兩次。
    * [Reference] C++常用屬性設定:
    ```
    	Configuration Properties
            General //...............................(1)
                # Output Directory
            C/C++
                General
                    # Additional Include Directories
                    # Additional #using Directories
                    # Consume Windows Runtime Extension
                Precompiled Headers
                    # Precompiled Header
                Code Generation
                    # Enable Minimal Rebuild
            Linker
                General
                    # Output File  // default 設定的 $(OutDir)\$(TargetName)$(TargetExt) 這裡每個變數都是從 (1) 來
                    # Additional Library Directories
                Input
                    * Additional Dependencies
    ```
- [[YouTube] Create a DLL in VC++](https://www.youtube.com/watch?v=yEqRyQhhto8)
- [關於DLL匯入](http://ypyp.pixnet.net/blog/post/23348150-%5B%E7%AD%86%E8%A8%98%5D-%E9%97%9C%E6%96%BCdll%E5%8C%AF%E5%85%A5)
- [Importing into an Application Using __declspec(dllimport)](https://docs.microsoft.com/en-us/cpp/build/importing-into-an-application-using-declspec-dllimport)

### 使用 Unit Test

- Reference
  - [Writing Unit tests for C/C++ with the Microsoft Unit Testing Framework](https://docs.microsoft.com/en-us/visualstudio/test/writing-unit-tests-for-c-cpp-with-the-microsoft-unit-testing-framework-for-cpp)
  - [Hilo C++ Unit Tests for Windows SDK Sample](https://hilo.codeplex.com/releases/view/97977) (Chrome can't open the download link)
  - Alternative way to unit test the task-then by using `get()` and `wait()`: [Task Parallelism (Concurrency Runtime)](https://msdn.microsoft.com/en-us/library/dd492427.aspx)

  - Totally obsolete links
    - [[Obsolete] Asynchronous calls in C++ Windows Store Unit Tests](https://blogs.msdn.microsoft.com/devops/2012/12/10/asynchronous-calls-in-c-windows-store-unit-tests/)


### How to check if privacy setting is on/off ?
- Prerequisite
    - [To handle errors and cancellation in a task chain...](https://docs.microsoft.com/en-us/windows/uwp/threading-async/asynchronous-programming-in-cpp-universal-windows-platform-apps#handling-errors-in-a-task-chain)
- Reference
    - [There is no API to access to get app Privacy settings](https://social.msdn.microsoft.com/Forums/windowsapps/en-US/5b94bb6a-43fe-41e8-8658-7c8f1b0b6195/api-to-access-to-get-app-privacy-settings-in-windows-10?forum=wpdevelop)
    
In the calendar `Appointments` case, you should use `nullptr` to check. See code example,

```c++
Calendar^ cal = ref new Calendar();

cal->Year = 2017;
cal->Month = 9;
cal->Day = 1;

TimeSpan timeSpan;
timeSpan.Duration = 25920000000000; // new TimeSpan(30, 0, 0, 0) in C#

auto task1 = create_task(AppointmentManager::RequestStoreAsync(AppointmentStoreAccessType::AllCalendarsReadOnly));
task1.then([cal, timeSpan](AppointmentStore^ store)->IAsyncOperation<IVectorView<Appointment^>^>^ {
    
    DateTime d = cal->GetDateTime();

    // If the privacy setting of Calendar is turn off for the app, the store parameter would be nullptr; 
    // however, if there are no user calendars in device, the store isn't nullptr.
    if (store == nullptr)
        throw std::runtime_error("null ptr");

    return store->FindAppointmentsAsync(d, timeSpan);
}).then([refMyTxt](task<void> t)
{

    try
    {
        t.get();
        // .get() didn' t throw, so we succeeded.
        OutputDebugString(L"File deleted.");
    }
    // If the "Appointments" capability isn't set, you'll get excpetion here
    catch (Platform::AccessDeniedException^ e) {

        OutputDebugString(e->Message->Data());
        refMyTxt->Text = L"Exception Catched";
    }
    catch (Platform::COMException^ e) // AccessDeniedException is a kind of COMException
    {
        //Example output: The system cannot find the specified file.
        OutputDebugString(e->Message->Data());
    }
    catch (std::runtime_error e)
    {
        //OutputDebugString(e);
        refMyTxt->Text = L"Exception null ptr";
    }

});
```

### 使用 STL
- [[C++] STL 容器 (一) - 基本介紹](http://larry850806.github.io/2016/06/06/STL1/)

### Polymorphism
- [Polymorphism in C++](https://www.tutorialspoint.com/cplusplus/cpp_polymorphism.htm)
- [虛擬函式](https://openhome.cc/Gossip/CppGossip/VirtualFunction.html)

### Output Debug String to DebugView
Use `OutputDebugString(...)`

### SendMessage
* 沒有admin的視窗SendMessage給有admin的會收不到，除非代入某個參數；但反過來收得到
* 若要傳數字給 WPF 的話
    * 要用 0x0112 的參數；若是傳字串的話要用 0x04A
    * 記得window的handle要抓對
* c#/c++ SendMessage to WinForm
    * 不一定要用0x0112的參數傳數字
    * 記得window的handle要抓對
* 補充：測實印output時
    * Debug.WriteLine() 是印在 DebugView
    * Console.WriteLine() 是印在 visual studio的output

### Service
* 移除指令: `sc delete "ServiceName"`
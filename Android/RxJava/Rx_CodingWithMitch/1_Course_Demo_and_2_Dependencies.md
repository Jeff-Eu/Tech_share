# RxJava from [CodingWithMitch](https://codingwithmitch.com/courses/rxjava-rxandroid-for-beginners/)

## Course Demo
* Simply put, an observable object is an object that can be observed by something else. This is the same idea as with LiveData and the MVVM architecture.
    * LiveData is the observable.
![img](https://codingwithmitch.s3.amazonaws.com/static/courses/9/live_data_universe_center.png)

    * 但是有些地方用 LiveData 會比 RxJava的 Observable還要好
* RxJava and RxAndroid is still very worth knowing about! It has very powerful operators and threading functionality.

## RxJava and RxAndroid Dependencies
* RxJava vs RxAndroid: 最早是先有RxJava，RxAndroid 則是為了在Android方便使用 RxJava 的而設計的擴充功能 (擴充功能是我看完影片後的解讀)。
* RxJava 與 RxAndroid 的主要差別:
    * RxAndroid contains reactive components that make using RxJava in Android easier and hassle free. More specifically it provides a `Scheduler` that can schedule tasks on the main thread or any other looper - aka any thread. (**It makes threading on Android very simple**).
    
    * You could use just the RxAndroid dependency, but the releases of RxAndroid updates are less frequent. To make sure you're up-to-date with the newest RxJava components, use the newest RxJava dependency.
* 兩個 Dependency 都要納入，降子就可以用RxJava，也可以用RxAndroid的 `Scheduler`

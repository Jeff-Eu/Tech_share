# Lesseon 4: Activity & Fragment Lifecycle

* 9. Activity Lifecycle States and Callbacks Summary (這節重要!也有講義)
    * from https://classroom.udacity.com/courses/ud9012/lessons/e487c600-ed68-4576-a35a-12f211cf032e/concepts/4c1503f9-2de5-45ea-88ae-2138b0482ecc
    * Activity跟Fragment 有共同的states，但是callbacks不一樣
    * onStop: Stop logic that updates the UI. This should not be running when the activity is off-screen; it's a waste of resources. ==> 注意不會 crash
    
    * Important Fragment Callbacks to Implement
        * 請同時也參考這連結的講解圖片，重要！
            * https://medium.com/androiddevelopers/the-android-lifecycle-cheat-sheet-part-iii-fragments-afc87d4f37fd

        * onCreate: Similar to the Activity’s onCreate callback. This is when the fragment is created. This will only get called once. Here you should:
            * Initialize anything essential for you fragment.
            * DO NOT inflate XML, do that in onCreateView, when the system is first drawing the fragment, NOT reference the activity, it is still being created. Do this in onActivityCreated (reference activity).

        * onCreateView: This is called between onCreate and onActivityCreated. when the system will draw the fragment for the first time or when the fragment becomes visible again. You must return a view in this callback if your fragment has a UI. Here you should:
            * Create your views by inflating your XML.

        * onActivityCreated:
            * Execute any code that requires an activity instance

        * onDestroyView: Unlike activities, fragment views are destroyed every time they go off screen. This is called after the view is no longer visible.
            * Do not refer to views in this callback, since they are destroyed

        * onDestroy: Called when the Activity’s onDestroy is called.

        * onDetach: Called when the association between the fragment and the activity is destroyed.

    * Lifecycle Cheat Sheets
        * from https://github.com/JoseAlcerreca/android-lifecycles
            * [done] Single activity
            * Multiple activities
            * Fragments
            * Translucent activities
            * Single Top / Single Task
            * ViewModels
            
* 13. Introduction to the Lifecycle Library
    * [Handling Lifecycles with Lifecycle-Aware Components](https://developer.android.com/topic/libraries/architecture/lifecycle)
    
* 14. Lifecycle Observation
    You're going to use Lifecycle Observation to start and stop the timer.

    1. Make DessertTimer a LifecycleObserver:
    In order to achieve this, DessertTimer should implement a LifecycleObserver, take in a Lifecycle as a parameter and establish observer relationship in init block.
        ```java kotlin
        class DessertTimer(lifecycle: Lifecycle) : LifecycleObserver {
            init {
                lifecycle.addObserver(this)
            }
        }
        ```

    2. Annotate startTimer and stopTimer with @OnLifecycleEvent and the correct event:
        ```kotlin
        @OnLifecycleEvent(Lifecycle.Event.ON_START)
        fun startTimer() {...}
        ```

        ```kotlin
        @OnLifecycleEvent(Lifecycle.Event.ON_STOP)
        fun stopTimer() {...}
        ```

    3. Pass in 'this' MainActivity's lifecycle so that it is observed:
        ```kotlin
        dessertTimer = DessertTimer(this.lifecycle)
        ```
* 16. Process Shutdown Demo
    * 這邊可以學到如何設定adb path，讓 terminal 可以使用 adb 
    * 刪除在背景的 Process
        ```
        // am 是指 activity manager
        adb shell am kill com.example.android.dessertpusher
        ```
        刪除完點下最近使用app會發現它還在清單之中，但是實際點開它會發現它重新被 create了(參考 9 的 lifecycle cheat sheet)

* 17. Exercise: onSaveInstanceState  
    * 儲存在 onSaveInstanceState 的bundle資訊應該要遠小於 100KB, or you'll risk crashing your app with the transaction too large exception.
    * Retrieve and use the bundled data in onCreate or onRestoreInstanceState，但大部分時候用 onCreate 裡的 bundle 就好；onRestoreInstanceState會在 onStart後面呼叫，所以只有需要在 onStart後去使用 bundle時再覆寫利用 onRestoreInstanceState即可。
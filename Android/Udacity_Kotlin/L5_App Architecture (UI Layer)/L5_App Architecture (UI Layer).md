# L5_App Architecture (UI Layer)

* 5. What is Architecture
    * 每一次 Architecture Pattern 都有它的優缺點，MVVM也是。
    - [Code Sample - Android Architecture Blueprints](https://github.com/android/architecture-samples)
        - 同一個ap用各種Architecture Pattern來實作，值得研究：Blueprints v1 had a collection of samples that are not maintained anymore, but can still be useful. [See all project branches](https://github.com/android/architecture-samples/branches).
    - Talk - Android Jetpack: what's new in Architecture Components (Google I/O '18)
    - Talk - Droidcon NYC 2016 - A Journey Through MV Wonderland
    - Blog Post - Android Architecture Patterns Part 2: Model-View-Presenter
    - Documentation - Guide to App Architecture
Blog Post - Android and Architecture

* 6. Our App Architecture
    * UI-Controller & ViewModel & LiveData
        * UI controller is the word that I'm using to describe what activities and fragments are.
        * UI controller is responsible for any user interface related tasks

* 7. ViewModel
    * 為了解決像rotate會需要Fragment跟Activity去重建的狀況，會利用 onSaveInstanceState寫在Fragment中，如果裡面做很多複雜的事，這種寫法會變很複雜，這時候可以把這些邏輯寫進ViewModel
    * The ViewModel survives configuration changes.
    * Unlike the onSaveInstanceState bundle, the ViewModel has no restrictions on size!

* 8. Exercise: Create the GameViewModel (重要)
    * 將 Fragment 與 ViewModel 做關聯
        * You never construct ViewModels yourself.
        * If you did, you'd end up constructing a ViewModel every time the fragment was recreated,
        * which wouldn't solve our rotation issue.
        * Instead the lifecycle library creates the ViewModel for you.
    * 在 Fragment 的 onCreateView 裡面，創建 ViewModel 並與 Fragment 作關聯
        ```java kotlin
        viewModel = ViewModelProviders.of(this).get(GameViewModel::class.java)
        ```
        * When ViewModelProviders is called again,
        * it'll return a reference to
        * a pre-existed GameViewModel associated with this UI controller.
    * 
        ```java kotlin
        class GameViewModel : ViewModel() {

            init {
                Log.i("GameViewModel", "GameViewModel created!")
            }
            // 這會在 Fragment 被 destroy 的前後，就會被呼叫 (目前還不曉得前後順序)
            override fun onCleared() {
                super.onCleared()
                Log.i("GameViewModel", "GameViewModel destroyed!")
            }
        }
        ```
    *  Run your code, and make sure you see the expected logs. Rotate your device a few times and notice how the `GameViewModel` does not get created again.

* 9. What Belongs in the GameViewModel? 
    * What should be moved to the ViewModel? Keep in mind:
        * The ViewModel is a stable place to store the data to display in the associated UI controller.
        * The Fragment draws the data on screen and captures input events. It should not decide what to display on screen or process what happens during an input event.
        * The ViewModel never contains references to activities, fragments, or views.

* 10. Exercise: Populate the GameViewModel
    * 
        * The viewModel should never contain references to activities, fragments, or views.
        * Now, you might be wondering about the reasoning for that last rule.
        * Remember that a big reason for us using viewModels is that they survive configuration changes.
        * By nature, activities, fragments, and views don't survive configuration changes.
    * 
        * Nav controller is found by passing in a viewer fragment, (第74行，gameFinished的函式裡面)
        * which are things that we do not want in the viewModel.
        * So basically, any navigation that you do is going to need to be done in the fragment.

* 11. The Benefits of a Good Architecture
    * First, the code is more organized, manageable, and debuggable.
    * Second, by moving code to the viewModel, you protect yourself from having to worry about life cycle problems and bugs.
    * 第三是ViewModel因為沒有參考Android Framework，所以可以在Android Studio直接使用基本的unit test來做測試，而不用跑需要模擬器的 AndroidTest
    * 總結優點:
        * Organized
        * Easier to debug
        * Fewer Lifecycle issues
        * Modular
        * Testable

* 12. The Power and Limits of the ViewModel
    - Documentation - Saving states
        - from https://developer.android.com/topic/libraries/architecture/saving-states
    - Blog post - ViewModels: Persistence, onSaveInstanceState(), Restoring UI State and Loaders
        - from https://medium.com/androiddevelopers/viewmodels-persistence-onsaveinstancestate-restoring-ui-state-and-loaders-fc7cc4a6c090

* 13. LiveData
    * LiveData is an observable data holder class that is lifecycle-aware.
    * LiveData is UI data and kept in ViewModel.
    * example
        ```java kotlin
        // 1. 注意這LiveData可宣告成val，因為只有裡面的資料會改變
        // 2. Nullable
        val score = MutableLiveData<Int>()
        ```

* 15. Lifecycle Awareness
    * Remember back when you set up the observation connection in onCreateView
        ```java kotlin
        viewModel.word.observe(this, Observer { newWord ->
            binding.wordText.text = newWord
        })
        ```
    * Well, you never actually cleaned up that connection in onDestroyView, and you don't need to. That's because LiveData is lifecycle-aware

* 16. Exercise: Add LiveData Encapsulation to GameViewModel
    * 封裝ViewModel的一些properties讓UI-Controller(Fragment)無法set他們，使得程式更OOP
        ```java kotlin
        private val _score = MutableLiveData<Int>()
        val score: LiveData<Int>
            get() = _score
        ```

* 18. Exercise: Add End Game event
    ```java kotlin
    // Sets up event listening to navigate the player when the game is finished
    viewModel.eventGameFinish.observe(this, Observer { isFinished ->
        if (isFinished) {
            gameFinished()
            // 為了不要在旋轉後又跑進來這個if case，主要這行是會將ViewModel裡面的_eventGameFinish.value設為false
            viewModel.onGameFinishComplete()
        }
    })
    ```

* 21. Exercise: Add CountDownTimer

    ```java kotlin
    timer = object : CountDownTimer(COUNTDOWN_TIME, ONE_SECOND) {

        override fun onTick(millisUntilFinished: Long) {
            // TODO implement what should happen each tick of the timer
        }

        override fun onFinish() {
            // TODO implement what should happen when the timer finishes
        }
    }

    timer.start()
    ```

    * Cancel the timer in onCleared:
        * To avoid memory leaks, you should always cancel a CountDownTimer if you no longer need it. To do that, you can call this in ViewModel:
        ```java kotlin
        override fun onCleared() {
            super.onCleared()
            timer.cancel()
        }
        ```

* 22. Exercise: Add a ViewModelFactory
    * 請參考程式碼裡 score package 裡面的檔案，是如何創建有參數的 ViewModel，但這需要用配合 ViewModelProvider.Factory 以及 ViewModelProvider，看起來挺麻煩的，這一切的Android設計都是為了LifeCycle！

* 23. Exercise: Add ViewModel to Data Binding
    * View - UI Controller (Fragment) - ViewModel
        * 使用 DataBinding 就可以將上面的 UI Controller 拿掉
    * 在xml加了<data>,<variable> 的tag之後要記得rebuild

* 24. Exercise: Add LiveData Data Binding
    * Data binding isn't just built to work well with ViewModel, it's also built to work well with LiveData.
    * reassign ViewModel的確也可以改變View的值，但這樣效率不好
    * DataBinding Library 也有提供一些方法讓資料可以bind到View上
        * 例如讓你的資料class實作 BaseObservable
        * ref https://developer.android.com/topic/libraries/data-binding/observability
    * 承上，使用LiveData就不需要去學上面 DataBinding Libary裡面的 Observable系列的方法了
    * 如何使用LiveData的 DataBinding？在 GameFragment裡面的 onCreate()裡面
        ```java kotlin
        binding.gameViewModel = viewModel
        binding.setLifecycleOwner(this) // 主要就是要加這行
        ```
    * 這節介紹如何binding到ViewModel的資料，並且用strings.xml寫的格式去format字串結果。

        game_fragment.xml
        ```xml
        android:text="@{@string/score_format(gameViewModel.score)}"
        ```

        values/strings.xml
        ```xml
        <string name="score_format">Current Score: %d</string>
        ```

* 25. Exercise: LiveData Map Transformation
    * Code in ViewModel
        ```java kotlin
        // The String version of the current time
        val currentTimeString = Transformations.map(_currentTime) { time ->
            DateUtils.formatElapsedTime(time)
        }
        ```
    * For more complicated transformations, you might end up using a SwitchMap or even a class called MediatorLiveData.
    These methods and classes allow you to manipulate and combine data from one or more LiveData.

* 26. Optional Exercise: Adding the Buzzer
    * 這邊可以學到Kotlin的Enum class，看起來可以傳資料進去，並且之後撈出來使用，e.g.
        * 在ViewModel中:
            ```java kotlin
            private val CORRECT_BUZZ_PATTERN = longArrayOf(100, 100, 100, 100, 100, 100)
            private val PANIC_BUZZ_PATTERN = longArrayOf(0, 200)
            private val GAME_OVER_BUZZ_PATTERN = longArrayOf(0, 2000)
            private val NO_BUZZ_PATTERN = longArrayOf(0)

            ...

            enum class BuzzType(val pattern: LongArray) {
                CORRECT(CORRECT_BUZZ_PATTERN),
                GAME_OVER(GAME_OVER_BUZZ_PATTERN),
                COUNTDOWN_PANIC(PANIC_BUZZ_PATTERN),
                NO_BUZZ(NO_BUZZ_PATTERN)
            }
            ```

        * 在UI Controller中
            ```java kotlin
            // Buzzes when triggered with different buzz events
            viewModel.eventBuzz.observe(viewLifecycleOwner, Observer { buzzType ->
                if (buzzType != GameViewModel.BuzzType.NO_BUZZ) {
                    // 可以看到這裡傳的pattern就是long的array
                    buzz(buzzType.pattern)
                    viewModel.onBuzzComplete()
                }
            })

            ...

            /**
            * Given a pattern, this method makes sure the device buzzes
            */
            private fun buzz(pattern: LongArray) {
                val buzzer = activity?.getSystemService<Vibrator>()
                buzzer?.let {
                    // Vibrate for 500 milliseconds
                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                        buzzer.vibrate(VibrationEffect.createWaveform(pattern, -1))
                    } else {
                        //deprecated in API 26
                        buzzer.vibrate(pattern, -1)
                    }
                }
            }
            ```

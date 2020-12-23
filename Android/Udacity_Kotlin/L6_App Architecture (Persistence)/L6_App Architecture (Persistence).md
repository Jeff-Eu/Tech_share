# Lesson 6: App Architecture (Persistence)

* 6. Data Access Object (DAO)
    * `@Query`的 Annotation 需要寫 SQL 語法
    * 下面回傳的是 LiveData ，所以當資料改變時，會直接update給 UI Controller
        ```java kotlin
        @Query("SELECT * FROM daily_sleep_quality_table ORDER BY nightId DESC")
        fun getAllNights(): LiveData<List<SleepNight>>
        ```
    * Compiler會檢查SQL annotation的syntax error

* 7. Exercise: DAO - SleepDatabaseDao
    * Create an interface SleepDatabaseDao and annotate it with `@Dao`，再把所有Query的 DAO方法寫在裡面:
        ```java kotlin
        @Dao
        interface SleepDatabaseDao {
            @Insert
            fun insert(night: SleepNight)
            ...
        }
        ```
    * 影片提到但程式沒有的
        ```java kotlin
        @Delete
        fun deleteAllNights(nights: List<SleepNight>): Int
        ```
    * Code
        ```java kotlin
        @Query("SELECT * FROM daily_sleep_quality_table ORDER BY nightId DESC")
        fun getAllNights(): LiveData<List<SleepNight>>
        ```
        * Notice, in the query, we are using ORDER BY to sort the results by the nightID.
        * We cannot assume that the nights are in the table in the order inserted as this is not guaranteed, but the general ideas are ascending.
        * The return value is live data. Now, this is one of the amazing features of room, that we can get back live data. Room makes sure that this live data is updated whenever the database is updated. This means that we only have to get this list of AllNights once.

* 8. Creating a Room Database
    * 這節是簡單介紹會有一個繼承自 RoomDatabase 的 class 用來存取一個 db，並且它裡面會合成一個前面設計的 DAO 物件，用來操作 db 裡面的 table。影片最後提到雖然這裡面程式碼做的事有點難懂難寫，但這class是可以重覆利用的，之後寫db相關的程式只需要c/p這裡面的內部稍微再修改一下即可。

* 9. Exercise: Creating a Room Database
    * Code
        ```java kotlin
        // 1. We have only one table so we supply the SleepNight class, if you have more than one table, add them all to this list.
        // 2. Whenever you change the schema, you will have to up the version number, if you forget to do that, your app will not work anymore.
        // 3. Export schema is true by default and saves the schema of the database to a folder, this provides you with a version history of your database, which can be very helpful for complex databases that change often. For this app, we don't need to do this, so we set it to false.
        @Database(entities = [SleepNight::class], version = 1,  exportSchema = false)abstract class SleepDatabase : RoomDatabase() {
            
            // In this app, we only have one table and one Dao but you can, of course, have multiple tables and multiple Daos as well.
            // ? abstract field 的意義
            abstract val sleepDatabaseDao: SleepDatabaseDao

            // We define a companion object, the companion object allows clients to access the methods without instantiating the class.
            companion object {

                // @Volatile helps us make sure the value of INSTANCE is always up to date and the same to all execution threats. The value of a volatile variable will never be cached, and all writes and reads will be done to and from the main memory, it means that changes made by one thread to INSTANCE are visible to all other threads immediately.
                @Volatile
                private var INSTANCE: SleepDatabase? = null

                fun getInstance(context: Context): SleepDatabase {
                    
                    synchronized(this) {
                        // Copy the current value of INSTANCE to a local variable so Kotlin can smart cast.
                        // Smart cast is only available to local variables.
                        var instance = INSTANCE
                        
                        // If instance is `null` make a new database instance.
                        if (instance == null) {
                            instance = Room.databaseBuilder(
                                    context.applicationContext,
                                    SleepDatabase::class.java,
                                    "sleep_history_database"
                            )
                                    // Wipes and rebuilds instead of migrating if no Migration object.
                                    // Migration is not part of this lesson. You can learn more about
                                    // migration with Room in this blog post:
                                    // https://medium.com/androiddevelopers/understanding-migrations-with-room-f01e04b07929
                                    .fallbackToDestructiveMigration()
                                    .build()
                            
                            INSTANCE = instance
                        }
                        // Return instance; smart cast to be non-null.
                        return instance
                    }
                }
            }
        }
        ```

* 10. Testing the Room Database
    * 它是 Instrumental Test，實測發現無法跑起來，會跳 "test framework quit unexpectedly"，我做了一些修改在 Step.03-Solution，已經可以跑了。

* 13. Exercise: Adding a ViewModel
    * 在 onCreateView 裡面
        ```java kotlin
        // Get a reference to the binding object and inflate the fragment views.
        val binding: FragmentSleepTrackerBinding = DataBindingUtil.inflate(
                inflater, R.layout.fragment_sleep_tracker, container, false)

        val application = requireNotNull(this.activity).application
        // 注意這邊從 SleepDatabase 裡取得 Dao 物件，在 XxxDatabase 裡可以有多個 Dao，基本上一個 Table 對應一個 Dao
        val dataSource = SleepDatabase.getInstance(application).sleepDatabaseDao
        // 會透過工廠來產生 ViewModel，雖然在這裡有點多餘，但可供未來參考
        val viewModelFactory = SleepTrackerViewModelFactory(dataSource, application)

        val sleepTrackerViewModel =
                ViewModelProvider(
                        this, viewModelFactory).get(SleepTrackerViewModel::class.java)

        binding.sleepTrackerViewModel = sleepTrackerViewModel

        binding.lifecycleOwner = this
        ```

* 14. Multithreading and Coroutines
    * Multi-Processing vs Multi-Threading
    * Scheduler & Dispatcher
    * The callback code will run at some asynchronous time in the future. In addition, callbacks don't allow the use of some language features, such as exceptions. There is no way to signal an error from a long-running task with exceptions when coding in the callback style, as flow control has already left the function that registered to the callback.
    * Be aware that the suspend keyword does not specify this thread code runs on. Suspend functions may run on a background thread or the main thread.
    * Coroutine References
        * 在FB看到台灣人分享的自學心得
            * https://waynestalk.com/kotlin-coroutine-tutorial/?fbclid=IwAR1iV1e2BP5uj5IiY9Mk_R_z8o_yKCTKTvEPqgYZBMH9ul554bRl7WgEkkQ
        * https://codelabs.developers.google.com/codelabs/kotlin-coroutines/#0
        * https://kotlinlang.org/docs/reference/coroutines-overview.html
    * Job, Dispatcher and Scope
        * Job
            * A job is anything that can be canceled. All coroutines have a job, and you can use it to cancel the coroutine. Jobs can be arranged into parent-child hierarchies so that cancellation of a parent leads to an immediate cancellation of all its children, which is a lot more convenient than if we had to do this manually for each coroutine.
        * Dispatcher
            * The dispatcher sends off coroutines to run on various threads. For example, dispatcher.main will run tasks on the main thread, and dispatcher.IO is for offloading blocking IO tasks to a shared pool of threads.
        * Scope
            * The scope combines information, including a job and dispatcher, to define the context in which the coroutine runs.
            * Scopes, keep track of coroutines. When you launch a coroutine, it's in scope, which means that you've said which scope will keep track of the coroutine.

        * Youtube有人推文的另一種說法
            1. We need a Job - just like a person assigned some task to do - that we can call to cancel.
            2. We need a Dispatcher - this guy decide which thread to run on - UI ...IO etc
            3. Scope  - it just combines Job and dispatcher -- Imagine him to be a guy who helps the above two work together.

* 15. 直接看程式碼，有太多 coroutine的語法

* 16. Googler Interview: Florina Muntenescu
    * Room 最棒的優點：
        * migration db 變得容易
        * 容易 test db
    * Room 缺點
        * 不支援加密 db 

* 18. Exercise: Recording Sleep Quality
    * 在 navigation.xml 中，注意下面這 fragment tag 裡有 argument 的 tag，用來傳進參數
        ```xml
        <fragment android:id="@+id/sleep_quality_fragment"
            android:name="com.example.android.trackmysleepquality.sleepquality.SleepQualityFragment"
            android:label="@string/sleep_quality_fragment"
            tools:layout="@layout/fragment_sleep_quality">
            <argument android:name="sleepNightKey"
                app:argType="long" />
            <action android:id="@+id/action_sleepQualityFragment_to_sleepTrackerFragment"
                app:destination="@id/sleep_tracker_fragment"
                app:launchSingleTop="false"
                app:popUpTo="@+id/sleep_tracker_fragment"
                app:popUpToInclusive="true" />
        </fragment>
        ```
    * 注意每次有修改到 binding的layout，可能會需要先 clean 再 rebuild project (至少講者是這麼演示的)
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
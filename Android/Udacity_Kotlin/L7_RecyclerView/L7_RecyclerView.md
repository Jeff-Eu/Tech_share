# Lesson 7: RecyclerView
* 2. Introduction 
    * RecyclerView 是用到 Adapter Pattern
    * 不同的資料數量適用的layout： RecyclerView > ListView, GridView > LinearLayout 
    * RecyclerView 如何透過 Adapter Pattern 秀資料？
        ![2020-12-23_182640.png](img\2020-12-23_182640.png)
        * Our app has a list of items which the adapter will adapt into something that can be drawn on the screen.
        * RecyclerView will find out how many items there are by asking the adapter,
        then for each item RecyclerView wants to put on the screen,
        * it will ask the adapter for a new ViewHolder and draw an item into this ViewHolder. For efficiency, RecyclerView will reuse or recycle ViewHolders that are scrolled off the screen whenever it can.
        * Reusing views is done by keeping the view but just resetting the value
        after we have used contents such as changing the text shown or images displayed.
* 5. Exercise: Display SleepQuality Data
    * Code
        ```java kotlin
        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): TextItemViewHolder {
            val layoutInflater = LayoutInflater.from(parent.context)

            // 講者說第三個參數 false 是因為現在 root 還沒造出來?，所以如果直接 attach 會跳 exception；下面這段在 RecyclerView 的 onCreateViewHolder 裡的寫法都是一樣的，不懂沒關係
            val view = layoutInflater
                    .inflate(R.layout.text_item_view, parent, false) as TextView
            
            return TextItemViewHolder(view)
        }
        ```
        * A ViewGroup is a type of view that holds a group of views. In reality, this will always be the RecyclerView. RecyclerView hands us the parent, because it turns out you'll need that to actually create a view holder.
        * The view type is used when there are multiple different views in the same RecyclerView.
        For example, you could put a list of text views and an image or even a video,
        * Here we are saying LayoutInflater.from parent.context.
        * You will create a LayoutInflater based on the parent view. It's somewhat important to use the right context. LayoutInflater uses View's information to inflate new views correctly. If you just pass a random context here,for example, the application context, you might get views with unexpected colors, forms or even sizes.
* 6. Exercise: Recycling ViewHolders
    * Code
        ```java kotlin
        override fun onBindViewHolder(holder: TextItemViewHolder, position: Int) {
            val item = data[position]
            holder.textView.text = item.sleepQuality.toString()

            if (item.sleepQuality <= 1)
                holder.textView.setTextColor(Color.RED) // red
            else // reset
                holder.textView.setTextColor(Color.BLACK) // black
        }
        ```
* 9. Exercise: Refactor onBindViewHolder
    * 這節可以學到用 Android Studio 的 refactor 將一般 method 改成 extension method
    * 這節最重要的觀念是重構了 onBindViewHolder(...)
    * Code
        ```java kotlin
        override fun onBindViewHolder(holder: ViewHolder, position: Int) {
            val item = data[position]
            // 將 ViewHolder 產生 View 的行為封裝在 bind(item) 裡，這樣未來如果有多種不同 ViewHolder的 type 的話，寫起來更加簡潔容易
            holder.bind(item)
        }
        ```

* 10. Exercise: Refactor onCreateViewHolder
    * 這節再次refactor code，將原本在 onCreateViewHolder(...) 裡 new出 ViewHolder(...) 的code，用static method封裝到 ViewHolder的 class裡去創建它，並且將 ViewHolder裡的 constructor 設為 private，有點類似 factory pattern的概念。加上前一節refactor好的 onBindViewHolder(...)，讓 SleepNightAdapter裡需要 override 的 methods 都變得很乾淨。

    * 注意這節可學到 Kotlin的 private constructor寫法。
        ```java kotlin
        class ViewHolder private constructor (itemView: View) : RecyclerView.ViewHolder(itemView) {
            ...
        }
        ```

* 11. Improving Data Refresh
    * 一個不錯的觀念，做完了前面介紹的 refactor後，現在的程式，就可以把 ViewHolder想像成是我們所要的 RecyclerView的實作細節。
    * notifyDataSetChanged() 可能會在 View 變得複雜時，在 scrolling時產生 flicking，看起來會像是每次scroll in一個新的element時就閃一下。
    * 這節預告了一個重要觀念，將使用實作了 Myer's Diff algorithm 的 DiffUtil，讓 RecyclerView 只去改變有差異的 item，使得 RecyclerView的更新更有效率。
        * [Leetcode](https://leetcode.com/problems/delete-operation-for-two-strings/)
        * [Google](https://www.google.com/search?sxsrf=ALeKk0311-UY7ygT2odC_ZbwhBf5A24kRg%3A1608977826591&ei=og3nX5bMI_qVr7wPhdiloAE&q=wiki+myer%27s+diff+algorithm&oq=wiki+myer%27s+diff+algorithm&gs_lcp=CgZwc3ktYWIQAzoECAAQRzoHCCMQsAIQJzoGCAAQDRAeUOieAljQowJgtKUCaABwA3gAgAFPiAHAApIBATWYAQCgAQGqAQdnd3Mtd2l6yAEIwAEB&sclient=psy-ab&ved=0ahUKEwiWpbi-tevtAhX6yosBHQVsCRQQ4dUDCA0&uact=5)

* 12. Exercise: Refresh Data with DiffUtil
    * 這節利用 DiffUtil 改善程式效率也同時 Refactor code！
        ```java kotlin
        class SleepNightAdapter : ListAdapter<SleepNight, SleepNightAdapter.ViewHolder>(SleepNightDiffCallback()) {
            ...
        }

        class SleepNightDiffCallback : DiffUtil.ItemCallback<SleepNight>() {
            override fun areItemsTheSame(oldItem: SleepNight, newItem: SleepNight): Boolean {
                return oldItem.nightId == newItem.nightId
            }

            override fun areContentsTheSame(oldItem: SleepNight, newItem: SleepNight): Boolean {
                return oldItem == newItem
            }
        }
        ```
        * 注意 `areContentsTheSame(...)` 裡面為何可以直接寫成 `oldItem == newItem`，因為 SleepNight 是一個 data class，所以它會比較裡面每一個 member是否相等。
            ```java kotlin
            data class SleepNight(
                @PrimaryKey(autoGenerate = true)
                var nightId: Long = 0L,

                @ColumnInfo(name = "start_time_milli")
                val startTimeMilli: Long = System.currentTimeMillis(),

                @ColumnInfo(name = "end_time_milli")
                var endTimeMilli: Long = startTimeMilli,

                @ColumnInfo(name = "quality_rating")
                var sleepQuality: Int = -1
            )
            ```
    * 在 SleepTrackerFragment.kt 裡，
        ```java kotlin
        val adapter = SleepNightAdapter()
        binding.sleepList.adapter = adapter

        sleepTrackerViewModel.nights.observe(viewLifecycleOwner, Observer {
            it?.let {
                // 注意這行 ListAdapter 特有的 submitList 函式，它會自動去更新兩個不同 list之間的 diff (只要內部你有實作好)
                adapter.submitList(it)
            }
        })
        ```

* 13. Exercise: Add DataBinding to the Adapter
    * 新技能，在 layout xml 的 parent裡按 Alt-Enter，就可選擇變成 data-binding 的 layout。
    * Rebuild project 之後就能使用 binding object，如果還是不行，就 go to file, invalidate caches/restart.
    * 新技能，在 4:38 介紹如何使用 Alt-Enter 將函式的參數 refactor成另外一種type。
    * 注意下面程式的 binding parameter 前面加上 val，或是依需求可寫 var；這是class的constructor特有的寫法，能同時宣告 member variables；與 method 的參數不需要加 var/val 的寫法不同。
        ```java kotlin
        class ViewHolder private constructor(val binding: ListItemSleepNightBinding)
                : RecyclerView.ViewHolder(binding.root) {
            ...
        }
        ```
    * 新技能，從 field 透過 Alt-Enter 變成 inline 呼叫，field就可以省略，同時也比較好理解code (只要inline不要太多層呼叫的話) 

* 14. Exercise: Add Binding Adapters
    * 在 ViewHolder 的 class中，bind()函式被改寫如下
        ```java kotlin
        fun bind(item: SleepNight) {
            binding.sleep = item // sleep 是 xml 中用 data 宣告的變數
            binding.executePendingBindings() // 這看起來是要做 binding 的話必須加的，不知用處為何
        }
        ```
    * 在 BindingUtils.kt 中，寫data轉換為view的函式，每個函式上面要加上 `@BindingAdapter(名稱)`
    * 在 list_item_sleep_night.xml 中，就可以 bind資料了，例如
        ```xml
        <data>
            <variable
                name="sleep"
                type="com.example.android.trackmysleepquality.database.SleepNight" />
        </data>
        <androidx.constraintlayout.widget.ConstraintLayout ...>
            <ImageView
                android:id="@+id/quality_image"
                ...
                app:sleepImage="@{sleep}"/>

            <TextView
                android:id="@+id/sleep_length"
                ...
                app:sleepDurationFormatted="@{sleep}"/>

            <TextView
                android:id="@+id/quality_string"
                ...
                app:sleepQualityString="@{sleep}"/>
        </androidx.constraintlayout.widget.ConstraintLayout>
        ```
        xml中強制將原本TextView設定text或ImageView設定image的屬性都給蓋掉了，這種binding寫法看起來有點牽強阿！

* 19. Interacting with List Items
    * 講者說有很多方法可實作 RecyclerView 的 click listeners，各有優缺點，這裡將介紹其中一種，不一定總是最好的。

* 20. Exercise: Implement a Click Listener
    * 比較 exercise跟 solution的 branch，就知道 click listener是加何加進去，值得注意的是，這裡在 xml直接將 sleep object 傳進去 onClick的 function，不像以前寫 view的 click都只能在 fragment裡面去寫function而且只有 view當參數，而且這裡 xml中每個view都可以加 onClick，就都可以參照 sleep object。
    * 回傳 Unit ，在 Kotlin 意思就是回傳 Void
        ```java kotlin
        val clickListener: (sleepId: Long) -> Unit
        ```

* 21. Exercise: Navigate on Click
    * 這節改進的功能是在 click睡眠品質 icon後，進到 detail畫面，值得注意有用到下面這個陌生的code,
        ```java kotlin
        // 我發現寫成降也是可以的，不一定要用後面的 MediatorLiveData
        //     private val night = database.getNightWithId(sleepNightKey)
        private val night = MediatorLiveData<SleepNight>()
        fun getNight() = night
        init {
            night.addSource(database.getNightWithId(sleepNightKey), night::setValue)
        }
        ```
        這裡的 MediatorLiveData 可以在 [stackoverflow得到解說](https://stackoverflow.com/a/48828237/1613961)。
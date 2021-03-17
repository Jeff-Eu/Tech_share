# Lesson 8. andfun-kotlin-mars-real-estate
* 5. App Walkthrough and Starter Code
    * 關於下面這段ViewModel初始化的code有兩點注意：    
        ```java kotlin
        private val viewModel: OverviewViewModel by lazy {
            ViewModelProvider(this).get(OverviewViewModel::class.java)
        }
        ```
        * 若 ViewModel 的 constructor是空的；亦即，不用提供其他參數來建構該VM，那用ViewModelProvider來創建該VM時只需傳入this；否則就還要傳入factory(詳見L7跟L6的code)。
        * 學會使用 lazy 應用在 property 上

* 6. Exercise: Connecting to the Internet
    * Gradle
        ```m
        implementation "com.squareup.retrofit2:retrofit: $version_retrofit"
        implementation "com.squareup.retrofit2:converter-scalars:$version_retrofit"
        ```
    * MarsApiService.kt
        * Use Retrofit.Builder to create the Retrofit object.
            ```java kotlin
            private val retrofit = Retrofit.Builder()
                .addConverterFactory(ScalarsConverterFactory.create())
                .baseUrl(BASE_URL) //"https://mars.udacity.com/"
                .build()
            ```
        * Create a `MarsApiService` interface, and define a `getProperties()` method to request the JSON response string.
            ```java kotlin
            // Returns a Retrofit callback that delivers a String.
            // The @GET annotation indicates that the "realestate" endpoint will be requested with the GET HTTP method. i.e. https://mars.udacity.com/realestate
            interface MarsApiService {
                @GET("realestate")
                fun getProperties(): Call<String>
            }
            ```
        * Passing in the service API you just defined, create a public object called MarsApi to expose the Retrofit service to the rest of the app:
            ```java kotlin
            // A public Api object that exposes the lazy-initialized Retrofit service
            object MarsApi {
                val retrofitService : MarsApiService by lazy { 
                    retrofit.create(MarsApiService::class.java) 
                }
            }
            ```
    * OverviewViewModel.kt
        ```java kotlin
        init {
            getMarsRealEstateProperties()
        }

        /**
            * Sets the value of the response LiveData to the Mars API status or the successful number of
            * Mars properties retrieved.
            */
        private fun getMarsRealEstateProperties() {
            MarsApi.retrofitService.getProperties().enqueue( object: Callback<List<MarsProperty>> {
                override fun onFailure(call: Call<List<MarsProperty>>, t: Throwable) {
                    _response.value = "Failure: " + t.message
                }

                override fun onResponse(call: Call<List<MarsProperty>>, response: Response<List<MarsProperty>>) {
                    _response.value = "Success: ${response.body()?.size} Mars properties retrieved"
                }
            })
        }
        ```
    * Add permission on manifest
        ```m
        <uses-permission android:name="android.permission.INTERNET" />
        ```

* 8. Exercise: Parsing the JSON Response
    * 把原本的json converter從轉成string換成轉成自己的物件
        ```java kotlin
        private val moshi = Moshi.Builder()
                //.addConverterFactory(ScalarsConverterFactory.create()) // 轉成字串的converter
                .add(KotlinJsonAdapterFactory()) // 轉成自己物件的converter
                .build()
        ```
    * 記得要先加上兩個gradle dependencies
        ```m
        // Moshi
        implementation "com.squareup.moshi:moshi:$version_moshi"
        implementation "com.squareup.moshi:moshi-kotlin:$version_moshi"

        // Retrofit with Moshi Converter
        implementation "com.squareup.retrofit2:converter-moshi:$version_retrofit"        
        ```
* 11. Exercise: Display an Internet Image
    * 注意 BindingAdapters.kt 這邊有個將 string url 轉成 https URI 的code
    ```java kotlin
    fun bindImage(imgView: ImageView, imgUrl: String?) {
        imgUrl?.let {
            val imgUri = imgUrl.toUri().buildUpon().scheme("https").build()
            ...
        }
    }
    ```

* 14. Parcel and Parcelables
    * [重要] The writeToParcel method writes all of the objects properties out to the parcel. The order of the parcel operations in the writeToParcel, createFromParcel, and the constructor must match.
    * 利用 Kotlin Android Extension 來輕鬆實作 Parcelables 的寫法，就不用去手動維護個別屬性及順序的一致性 (影片 3:15 ~ 3:49)
## Android
* Q: 為何寫ViewPager時，若要做到recycle的機制，用正規的 FragmentStatePagerAdapter 寫法，也不會像 ListView 的 adapter會有官網建議的 ViewHolder 寫法來做到 recycle 的機制？
    * A: 我推測是因為UI的操作不同，ListView需要即時快速的滑動，所以一定要 ViewHolder 的支援才能達到快速 recycle；但 ViewPager 每次只滑動一頁，UI還有時間緩衝去重新創建新的 Page ，因此不用特別做 ViewHolder。
    * 其他參考 [view-holder-pattern-for-viewpager](https://stackoverflow.com/questions/12367433/view-holder-pattern-for-viewpager)
* Instrumental Unit Test
    * Instrumental test 應該是會修改到真正 ap 的 sqlite 
    * Timber.x 這套 library 無法印出東西
    * System.out.println(...) 是在run的情況下印出
    * Log.x 是在debug的情況下印出
* [How to enable Google Play App Signing](https://stackoverflow.com/questions/44103024/how-to-enable-google-play-app-signing)
* [Implementation Vs Api in Android Gradle plugin 3.0](https://medium.com/mindorks/implementation-vs-api-in-gradle-3-0-494c817a6fa)
* AdView (which is supported by `com.google.android.gms:play-services-ads`) needs to be compiled when network is connected.
* [Swipe to refresh](https://www.google.com.tw/search?ei=z2fRWo3SLYXN0AS8gpWQAg&q=android+Swipe-to-Refresh&oq=android+Swipe-to-Refresh&gs_l=psy-ab.3..0i7i30k1l3j0i7i10i30k1j0i7i30k1l6.2151.3541.0.4232.8.8.0.0.0.0.141.718.6j2.8.0....0...1.1.64.psy-ab..2.6.501...35i39k1.0.4HYOXtZLNX8)
* [Use Gson to convert object from/to Json format](https://github.com/google/gson/blob/master/UserGuide.md) => Well written !
* [Apache HttpClient or Android HttpsURLConnection ?
](https://stackoverflow.com/a/7742936/1613961)
* Http GET POST
    * [Android HTTP Get 及 Post](http://fiend1120.pixnet.net/blog/post/193711428-android-http-get-%E5%8F%8A-post-)
    * [Tony Blog - Android 如何使用 GET & POST 取得資料](http://blog.tonycube.com/2011/11/androidget-post.html)
- [How Android ListView's recycling mechanism works](https://stackoverflow.com/questions/11945563/how-listviews-recycling-mechanism-works)
- [How to make flip animation](https://stackoverflow.com/a/43560782/1613961)
- [如何使用TabLayout](http://givemepass-blog.logdown.com/posts/288943-how-to-use-tablayout)
- Facebook Login
    - 建議採用這篇教學[Quick Tip: Add Facebook Login to Your Android App](https://code.tutsplus.com/tutorials/quick-tip-add-facebook-login-to-your-android-app--cms-23837)。如果是照[官網-Facebook Login for Android - Quickstart](https://developers.facebook.com/docs/facebook-login/android/?locale=en_US&sdk=maven)的做，會在第一次**Build your project**的地方產生錯誤，問題是出在這行，
      ```gradle
      compile 'com.facebook.android:facebook-login:[4,5)'
      ```

    - 在windows環境下，到了**Add your development and release key hashes**這步驟時，又會遇到麻煩，本來要執行裡面這指令
      ```
      keytool -exportcert -alias androiddebugkey -keystore %HOMEPATH%\.android\debug.keystore | openssl sha1 -binary | openssl base64
      ```
        cmd會說找不到 keytool的cmd工具，答案 [jdk裡面](https://stackoverflow.com/questions/5488339/how-can-i-find-and-run-the-keytool)。
          
        接下來第二個麻煩是OpenSSL，所以再執行一次命令還是會錯，請到[這裡](https://slproweb.com/products/Win32OpenSSL.html) 下載安裝完OpenSSL之後，到windows的cmd再執行一次，注意指令裡面的openssl要換成安裝所在的路徑，還有[不要在powershell執行](https://stackoverflow.com/questions/33340242/keytool-generates-32-character-long-key-hash-instead-of-28)，否則不會產生28字元的字串。
        * [補充] 官網教的使用command prompt的方式產生HashKey會有問題，正確解法如本篇所述 [Android facebook integration invalid key hash](https://stackoverflow.com/questions/23674131/android-facebook-integration-invalid-key-hash)
    - 記得在gradle設定完之後，要按sync gradle，Android才會把facebook的sdk載入。

    - Coding遇到並解決的問題
        - [Error inflating class com.facebook.widget.LoginButton with Facebook SDK ](https://stackoverflow.com/a/33733713/1613961)

    - Other Reference 
        - 一開始gradle設定我是照這篇[Integrate the Facebook API with Android](https://www.sitepoint.com/integrating-the-facebook-api-with-android/)，但寫code的地方這篇教的太複雜，不太推。
        * 產生release apk時，也需要用release的 key store去產生新的hash key，將hash key新增到facebook developer console的 Key Hashes 裡面，產生hash key的解法，[可參考這篇用coding印出的方法](https://stackoverflow.com/a/9600642/1613961)，會比較快。

## 資料同步演算法
### 1) 第一種，資料流稍大，但邏輯較簡易
* 手機端client部分，記錄`新增`、`刪除`與`修改`的snapshot，同步時先post snapshot的部分(亦即，有修改的部分)，再get全部的資料下來。
    * 順序: Add phrases => Delete phrases => Update phrases => Download phrases => Download translations
    * 手機端新增phrase的情形 (目前只有透過SharedActivity新增)：
        * ~~在有網路的情況下，會呼叫Add的REST API新增phrase到server，再將回傳的id給local端創建Record存入PhraseTable；不會存入DiffTable。~~
        * ~~在沒有網路的情況下，會~~直接在local端自行新增不重覆local db的id來創建Record，再將Record存入PhraseTable及DiffTable，等下次從主ap進去跟server做同步時，才會利用DiffTable去做同步的動作。
            * 承上，Local DB 還是可以使用 ServerId 當作 primary key，只要在insert時不指定 ServerId，那Sqlite就會自動幫你產生不重覆的Id，[參見此教學文](http://www.sqlitetutorial.net/sqlite-autoincrement/)。
            * DiffTable裡面的Record因為還沒同步過，因此該"新增的Record"的ServerId不會跟server一樣，只有當跟Server同步後，從Server產生的ServerId才會是真的，這時候再同步下來local端就會拿到真的serverId。

### 2) 第二種，資料流小，但邏輯較複雜(但也沒有很難)
這邊要討論同步的處理方式，首先資料的同步有分成
- 網站前端與server
- 手機(或平板)前端與server

與網站前端不同的是，手機前端因為有offline需求，可能會有一段offline的時間後才與server同步，所以手機端需要sqlite資料庫做offline的儲存，目前想到一個方法來解決同步問題，目標是
- 讓同步的網路傳輸資料流盡量少
- 邏輯不複雜

有個前提是，手機端雖然能從app編輯及刪除每筆Record資料，但必須是在連線狀態下才能(即時)更新。

如下圖所示，其中Client1,Client2可能是手機及平板，或是desktop app，先看上半部，Server軸線的每個數字代表新增、刪除或是修改的記錄，Client1及Client2分別以綠線及藍線表示**有連線**的時段，對Client1來說，左邊綠線最後更新到4號，因此client1的local db就記錄到4號時間的整筆server資料，等到下次又連線到右邊的綠線，client1只要跟server要5,6號兩筆的資料，再更新到local db即可。

但這樣有個缺點是刪除及修改的**歷史記錄**也都要儲存到server，隨著時間拉長同步次數累積愈多，即使Record的資料不多，但server卻留著許多的歷史記錄。

![MyPhrase_data_sync](\imgs\MyPhrase_data_sync.jpg)

因此為了省儲存在server的資料量，做了一點折衷是，將前面累積一定數量的歷史記錄都往前刪除，並留下Snapshot，如果client要同步時，之前記錄的時間是比server的Snapshot時間還要早，因為Client2距離上次更新的時段，在server上的歷史記錄已經不完整，因此就選擇直接下載全部的Record資料做同步，如上圖的下半部所示，Client2在右邊的藍線一開始要做同步時，只能下載全部的Record資料；但Client1的在右邊的綠線一開始要做同步時，只要更新2,3號Record的歷史資料。

### Server端資料儲存方式

前面已講解同步演算法，因此Server端的資料儲存方式就會以Snapshot加上diff history(差異的歷史記錄)組合而成，舉例，diff history 每多了300筆就一個snapshot，但一開始要從第500筆才開始算，因此要等到最新歷史記錄為第800筆的時候，會在第300筆資料做snapshot。

### 手機/平板前端資料儲存方式

手機前端的local資料儲存方式很單純，因為做資料的刪除/修改(新增只有在網站前端做)都需要在網路有連線的情況下，因此能即時修改到server端的資料。手機local db的資料可以用sqlite，以一個table去包含全部的Record，若沒有要write資料，local db的資料可能比server舊；但若要write資料，local db的資料就會與server上一樣保持在最新狀態, 注意server的資料不單純只有一個table，如果以sql資料庫的述語來說的話，主要會是snapshot加上diff history兩個table。


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
* [Use enhanced for loop syntax](https://developer.android.com/training/articles/perf-tips#Loops)
* [Android Material Design working with Tabs](https://www.androidhive.info/2015/09/android-material-design-working-with-tabs/)
* [Android Sliding Menu using Navigation Drawer](https://www.androidhive.info/2013/11/android-sliding-menu-using-navigation-drawer/)

* Tool Windows - Device File Explorer
    * sdcard/Android/data/yourPackageName
	* Build variants
	    * [Tutorial from Udacity](https://classroom.udacity.com/courses/ud867/lessons/4020658782/concepts/43254185720923)

* Check Webview version:

```java
PackageManager pm = getPackageManager();
try {
    // PackageInfo pi = pm.getPackageInfo("com.android.webview", 0);
    PackageInfo pi = pm.getPackageInfo("com.google.android.webview", 0);
    Log.d(TAG, "version name: " + pi.versionName);
//			Log.d(TAG, "version code: " + pi.versionCode);
    long longVersionCode= PackageInfoCompat.getLongVersionCode(pi);
    int versionCode = (int) longVersionCode; // avoid huge version numbers and you will be ok
    Log.d(TAG, "version code: " + versionCode);

} catch (PackageManager.NameNotFoundException e) {
    Log.e(TAG, "Android System WebView is not found");
}
```
* publish 更新程序:
    * 在 Android studio
        * 先更新 version code
        * 選擇完 build variants之後，再 build signed apk
            * [待研究] 如果直接選 build signed apk是否就不用再選 build variants?

    * 在 Play Console網頁
        * 先選擇 Release management
        * 選擇 New Release
        * 將 Android 的release的 free跟 paid 資料夾內的apk複製到 Console網頁的upload頁面
            * [注意] 如果Android studio 做完build signed apk後只過了短暫時間又手動再build signed apk一次，那 release的 free跟 paid 資料夾內的apk並不會被更新到，這是 可能是Android Studio的bug，必須要先將該檔案移除後再重新build才會成功產生新的apk

* searchView
    * as a MenuItem
        * https://youtu.be/9OWmnYPX1uc?t=92
    * searchable config
        * https://youtu.be/9OWmnYPX1uc?t=156
    * how to change android SearchView text
        * https://stackoverflow.com/questions/14426769/how-to-change-android-searchview-text
    * How do I open the SearchView programmatically?
        * https://stackoverflow.com/questions/14235677/how-do-i-open-the-searchview-programmatically/14235987#14235987

* Custom ActionBar
    * https://stackoverflow.com/questions/27670684/how-to-set-a-custom-view-in-actionbar-in-android
    * https://www.tutorialspoint.com/how-to-create-custom-actionbar-in-android
    * https://www.journaldev.com/9952/android-custom-action-bar-example-tutorial

* Getting ActionBar Title TextView with AppCompat v7 r21
    * https://stackoverflow.com/questions/26455595/getting-actionbar-title-textview-with-appcompat-v7-r21

* Instance State:
	* https://www.intertech.com/Blog/saving-and-retrieving-android-instance-state-part-2/
    
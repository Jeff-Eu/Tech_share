# [Android](https://github.com/derekargueta/Android-Interview-Questions)
## Core Java
* Explain object serialization and how to implement it in Java\
	Ans: [solution](https://www.tutorialspoint.com/java/java_serialization.htm)
## Core Android
* How can two distinct Android apps interact? \
	Ans: intent-filter
	* An Activity with a matching intent-filter tag in the manifest
	* One or more ChooserTarget objects returned by your ChooserTargetService
	* Sharing Shortcuts published by your app. These supersede ChooserTarget objects. Sharing Shortcuts are only available if your app is running Android 10 (API level 29).

* [Launch Mode](https://android.jlelse.eu/android-activity-launch-mode-e0df1aa72242)
	* 種類:
		* standard
		* singleTop: 永遠都創建一個新的在最上面，除非最上面已經是一樣的activity，才會用 onNewIntent()把資訊傳過去，所以這種模式可能會有多個相同的activity。
		* singleTask: 永遠只有唯一一個 activity, 無論 task有幾個，注意如果創建在在同一個task，原本它後面的 activity 都會被destroy。
		* singleInstance: 跟 singleTask很像，只是總是建立在新的task, 並且只有它一個 activity。
	* [補充] 若會呼叫到 onNewIntent() (此時就不會叫onCreate()), 呼叫順序如下:
		* onPause()
		* onNewIntent()
		* onResume()

* [Parcelable vs Serializable](https://stackoverflow.com/a/50114007/497132)

* Activity vs Fragment\
	Ans:
	* Activity is not dependent on fragment.but The fragment is dependent on Activity, it can't exist independently.
	* without using fragment in Activity we can't create multi-pane UI. but using multiple fragments in a single activity we can create multi-pane UI.
	* If we create a project using only Activity then its difficult to manage but if we use fragments then the project structure will be good and we can handle it easily.
	* An activity may contain 0 or multiple numbers of fragments. A fragment can be reused in multiple activities, so it acts like a reusable component in activities.
	* The activity has own life cycle but fragment has there own life cycle.
For Activity, we just need to mention in Manifest but for fragment its not required.

* Activity Lifecycle
	* Note that it is important to save persistent data in onPause() instead of onSaveInstanceState(Bundle) because the latter is not part of the lifecycle callbacks, so will not be called in every situation as described in its documentation.

	*	
		看了[這篇](https://stackoverflow.com/questions/20831826/when-exactly-are-onsaveinstancestate-and-onrestoreinstancestate-called/20831956#20831956)後終於了解 onSaveInstance() 為何跟onPause或onStop等狀態是否為 Killable有密切關係，從[官網Activity的介紹](https://developer.android.com/reference/android/app/Activity.html#ProcessLifecycle)有個表格標註各種狀態是否為 Killable，例如 onStop() 有標 Killalbe，系統就會在該app做完 onStop()到invisible後，才會強制將它刪掉，也就是說，到了Killable的狀態後，系統刪掉app就不會讓app再有機會儲存目前狀態，但若沒有標註Killable狀態，系統刪掉該app時，app還有機會留下遺言在下次重生時繼續未完成的事。

		onSaveInstance() 呼叫時機:
		```
		if v < Android HONEYCOMB (sdk 11):
			before onPause()
		else:
			if v >= Android P (sdk 28):
				after onStop()
			else:
				before onStop()
		```
		* 小記，
		[sdk 28 後的改變](https://stackoverflow.com/a/49230811/1613961) :\
		看到上面程式的 onSaveInstance 演進，感覺 Android 發展的目標是要讓 onSaveInstance() 能盡量往後推愈接近 Destroyed state 來呼叫愈好(像是onStop 後的invisible)，這代表在 onSaveInstance 之前的狀態都能被 Android 記錄起來，隨著版本演進，能記錄到愈後面的狀態了，這是一個技術突破。若app被系統刪掉還可以記錄 state的話，那app就能獲取更多資訊。

		onRestoreInstanceState() 呼叫時機:
		```
		onStart() -> onRestoreInstanceState () -> onPostCreate(Bundle).
		```
	* Starting Activities and Getting Results
		* 使用函式:
			1. startActivityForResult(Intent, int)
			2. setResult (int resultCode, Intent data)
			3. onActivityResult(int requestCode, int resultCode, Intent data)
			* 說明:\
			act1 叫 act2 用 1.式。act2離開回 act1之前若想攜帶資料回來，叫2.式。回到act1並處理攜帶回來的資料，用3.式。
		* [stackoverflow](https://stackoverflow.com/questions/10407159/how-to-manage-startactivityforresult-on-android)
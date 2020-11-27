# Debug in Android
## Debug on Chromebook
* [The development environment](https://developer.android.com/topic/arc/development-environment)
* [How To Turn On Developer Mode On A Chromebook](https://www.youtube.com/watch?v=oWEIpCJMkBQ&ab_channel=DavidHarry)
    * 新的ChromeOS已經不需要進developer mode就可以debug，但還是要看機種(意思是有的機種在新的OS下不管怎樣都不能debug了e.g.ASUS C223N and ASUS C214M)，舊的ChromeOS只能在developer mode下才能debug Android app，以下介紹如何設定進入developer mode：
        1. 關機後，按下esc + refresh + power鍵啟動
        2. 秀出要插入USB跟SD卡的畫面後，不要管它，按下ctrl + D
        3. 接下來秀出開啟OS驗證的畫面，按下 Enter
        4. 秀出OS驗證被關閉的畫面，不要管它，按下ctrl + D
        5. 秀出系統將進入Develop Mode畫面，不要管它，它會繼續下去，最後重開機
        6. 又秀出OS驗證被關閉的畫面，不要管它，按下ctrl + D直接進下一步，最後會直接進入ChromeOS系統
        7. 輸入基本資訊，登入一個google帳號才有機會進入debug app的階段
        8. 進入設定頁，到app

* [How To Turn Off Developer Mode On A Chromebook](https://www.youtube.com/watch?v=K62agbgzwKo&ab_channel=DavidHarry)
    1. 秀出OS驗證被關閉的畫面，按下空白鍵
    2. 秀出OS驗證被關閉需按下Enter才能開啟驗證的畫面，按下Enter，跑不久就會進入ChromeOS了
    
* [Debugging through USB is not supported on many ASUS Chromebook models. **Only wifi debugging is available.**](https://www.chromium.org/chromium-os/chrome-os-systems-supporting-adb-debugging-over-usb)
## 環境變數路徑整理
* `%LocalAppdata%\Packages\`
    * 存放各個UWP app設定，ScreenPadToolbar也是存放在這
    * 如果使用`GetEnvironmentVariable(L"AppData", buff, sizeof(buff))`去取得buff的路徑，buff的路徑會是在 %LocalAppdata%\Packages 下，主程式所在的 `LocalCache\Roaming\` 下面。
* 華碩PM要求把暫存檔放在 `%ProgramData%\Asus\`，但除非我們能取得移除的api，在移除之前呼叫才能把它清掉。
* UWP app is installed in `%ProgramFiles%\WindowsApps`


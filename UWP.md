## Localization
* [Global Ready formats](https://docs.microsoft.com/en-us/windows/uwp/design/globalizing/use-global-ready-formats)
* [Understand user profile languages and app manifest languages](https://docs.microsoft.com/en-us/windows/uwp/design/globalizing/manage-language-and-region)
* [DateTimeFormatter Class](https://docs.microsoft.com/en-us/uwp/api/windows.globalization.datetimeformatting.datetimeformatter)
```c++
DateTime st = ap->StartTime;
DateTimeFormatter^ shortDateFormatter = ref new DateTimeFormatter("shortdate", GlobalizationPreferences::Languages);
String^ startShortDate = shortDateFormatter->Format(st);
```
* [Date and time formatting sample](https://github.com/Microsoft/Windows-universal-samples/tree/master/Samples/DateTimeFormatting)
* [Globalization preferences sample](https://github.com/Microsoft/Windows-universal-samples/tree/master/Samples/GlobalizationPreferences)
* [Impact Locale Table](https://www.science.co.il/language/Locale-codes.php)
    * [Locale ID value](https://msdn.microsoft.com/en-us/library/ms912047(v=winembedded.10).aspx)
    * [Language Strings](https://msdn.microsoft.com/en-us/library/39cwe7zf.aspx?f=255&MSPPError=-2147217396)

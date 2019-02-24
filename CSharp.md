# C# Language

## Table of Contents
- [Date and Time](#date-and-time)
    - [Domain knowledge about calendar](#domain-knowledge-about-calendar)
    - [Know about `DateTime`](#know-about-datetime)
    - [Know about `DateTimeOffset`](#know-about-datetimeoffset)
    - [Know about `TimeSpan`](#know-about-timespan)
    - [Know about `Calendar`](#know-about-calendar)
- [UWP](#uwp)

### Date and Time

#### Domain knowledge about calendar
- What is [TimeZone](https://zh.wikipedia.org/zh-tw/%E6%97%B6%E5%8C%BA) ?
- What is [PST](https://zh.wikipedia.org/zh-tw/%E5%A4%AA%E5%B9%B3%E6%B4%8B%E6%97%B6%E5%8C%BA) ?
- What is [DST](https://en.wikipedia.org/wiki/Daylight_saving_time) ?
- [Gregorian Calendar](https://en.wikipedia.org/wiki/Gregorian_calendar) is [公曆](https://zh.wikipedia.org/zh-tw/%E5%85%AC%E5%8E%86)
- [Wiki解釋西元前後的縮寫](https://zh.wikipedia.org/wiki/%E5%85%AC%E5%85%83)
    - 紀元後=西元=公元 的英語縮寫:
        - A.D. (拉丁文- Anno Domini, 主的年份)
        - C.E. (較常用。Common Era，後延伸為Christian Era)
    - 紀元前
        - B.C. (Before Christ)
        - B.C.E. (Before Common Era)
- The most accurate way to express date:
    - 2:00:00 midnight on January 1, 1601 CE, **UTC time**.

#### Know about `DateTime`
- [Creating a DateTime in a specific Time Zone](https://stackoverflow.com/a/246529/1613961)
    - From [When Would You Prefer DateTime Over DateTimeOffset
](https://stackoverflow.com/a/264643/1613961)
- MSDN [DateTime.Kind](https://msdn.microsoft.com/en-us/library/system.datetime.kind(v=vs.110).aspx?cs-save-lang=1&cs-lang=csharp#code-snippet-1) Property has good examples :
    - Notice the case where the `DateTime.Kind` is set to `Unspecified` (also as default value), which is often misleading.
- [DateTime Compare Ignores Kind](https://stackoverflow.com/questions/28602941/datetime-compare-ignores-kind)
- [This reply](https://stackoverflow.com/a/14245132/1613961) gives good explanation about DateTime (and a little about DateTimeOffset).
- *"When saving or sharing `DateTime` data, UTC should be used and the `DateTime` value's `Kind` property should be set to `DateTimeKind.Utc`"*.\
― [MSDN, Choosing between DateTime, DateTimeOffset, TimeSpan, and TimeZoneInfo](https://docs.microsoft.com/en-us/dotnet/standard/datetime/choosing-between-datetime)
- Be careful, the [`DateTime` in UWP C++](https://msdn.microsoft.com/en-us/library/vs/alm/br205770.aspx) is much different from the [`DateTime` in C#](https://docs.microsoft.com/en-us/dotnet/api/system.datetime?view=netframework-4.7). 
    - DateTime in C++ only has a `UniversalTime` member, which is *the number of 100-nanosecond intervals that have elapsed since 12:00:00 midnight on **January 1, 1601 CE**, UTC time*.
    - DateTime in C# has a similar member called [`DateTime.Ticks`](https://docs.microsoft.com/en-us/dotnet/api/system.datetime.ticks?view=netframework-4.7#System_DateTime_Ticks), which represents *the number of 100-nanosecond intervals that have elapsed since 12:00:00 midnight, **January 1, 0001 CE**, UTC time.*

#### Know about `DateTimeOffset`
- [MSDN `DateTimeOffset`](https://docs.microsoft.com/en-us/dotnet/api/system.datetimeoffset?view=netframework-4.7) gives great explanation. Must read it !! Which includes
    - `DateTime` property
    - `Offset` property
    - Have no `Kind` property !

#### Know about `TimeSpan`
- `TimeSpan.Ticks`
    - The smallest unit of time is the tick, which is equal to **100 nanosecond**.
    - The value of the Ticks property can be negative or positive to represent a negative or positive time interval.

#### Know about [`Calendar`](https://docs.microsoft.com/en-us/dotnet/standard/datetime/working-with-calendars)
We represent date and time whose strings depend on the conventions used for displaying date and time values by a specific culture. 
- Each culture has a default calendar, which is defined by the `CultureInfo.Calendar` property. 

### UWP
- [Calling Windows 10 APIs From a Desktop Application](https://blogs.windows.com/buildingapps/2017/01/25/calling-windows-10-apis-desktop-application/#RmbvB6bFbuRZSSvW.97)
- [Install certificate to run the packaged app](https://docs.microsoft.com/en-us/windows/uwp/porting/desktop-to-uwp-run-desktop-app-converter#run-app)
- [Package an app using the Desktop App Converter (Desktop Bridge)](https://docs.microsoft.com/en-us/windows/uwp/porting/desktop-to-uwp-run-desktop-app-converter)
- [An easier way to generate the packages for a Desktop Bridge converted app](https://blogs.msdn.microsoft.com/appconsult/2017/02/21/an-easier-way-to-generate-the-packages-for-a-desktop-bridge-converted-app/)
- [Globalize your date/time/number formats](https://docs.microsoft.com/en-us/windows/uwp/design/globalizing/use-global-ready-formats)
# Tricks

* 如果一個檔案裡面或一個function中有很多if condition，若要快速跑出程式印出trace資訊，可以用像降的寫法
    ```python
    s = ""
    if case_1:
        s+="1"
        if case_2:
            s+="2"
        elif case_3:
            s+="3"
        else:
            s+="4"
    else:
        s+="5"

    print s
    ```
    
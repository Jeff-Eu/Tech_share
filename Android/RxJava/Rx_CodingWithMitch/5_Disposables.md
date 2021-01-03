## Disposables
* disposables.clear() 與 disposables.dispose() 差異是，disposed() will no longer allow anything to subscribe to the observable.

* 這裡提到一個小重點，他提到 Observer的形式有多種，像下面 Snippet 2的 Consumer就是另一種，它還可以回傳 Disposable；反之 Snippet 1就只有回傳 void，這兩個差異是，只要 Observer的形式是有 override onSubscribe(Disposable d)的，那就不再需要回傳 Disposable了，降講滿有道理的。
    ```java kotlin
    // Snippet 1:
    taskObservable.subscribe(new Observer<Task>() {
        @Override
        public void onSubscribe(Disposable d) {
            Log.d(TAG, "onSubscribe: called.");
            disposables.add(d);
        }
        ...
    });

    // Snippet 2:
    Disposable d = taskObservable.subscribe(new Consumer<Task>() {
        @Override
        public void accept(Task task) throws Exception {
            ...        
        }
    });
    disposables.add(d);
    ```

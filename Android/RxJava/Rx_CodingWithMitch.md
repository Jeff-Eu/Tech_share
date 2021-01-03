# RxJava from [CodingWithMitch](https://codingwithmitch.com/courses/rxjava-rxandroid-for-beginners/)

## Course Demo
* Simply put, an observable object is an object that can be observed by something else. This is the same idea as with LiveData and the MVVM architecture.
    * LiveData is the observable.
![img](https://codingwithmitch.s3.amazonaws.com/static/courses/9/live_data_universe_center.png)

    * 但是有些地方用 LiveData 會比 RxJava的 Observable還要好
* RxJava and RxAndroid is still very worth knowing about! It has very powerful operators and threading functionality.

## RxJava and RxAndroid Dependencies
* RxJava vs RxAndroid: 最早是先有RxJava，RxAndroid 則是為了在Android方便使用 RxJava 的而設計的擴充功能 (擴充功能是我看完影片後的解讀)。
* RxJava 與 RxAndroid 的主要差別:
    * RxAndroid contains reactive components that make using RxJava in Android easier and hassle free. More specifically it provides a `Scheduler` that can schedule tasks on the main thread or any other looper - aka any thread. (**It makes threading on Android very simple**).
    
    * You could use just the RxAndroid dependency, but the releases of RxAndroid updates are less frequent. To make sure you're up-to-date with the newest RxJava components, use the newest RxJava dependency.
* 兩個 Dependency 都要納入，降子就可以用RxJava，也可以用RxAndroid的 `Scheduler`

## Introduction to Observables and Observers (重要！)
* 下面這個範例會在每1秒印出`DataSource.createTasksList`裡面的項目，去實際跑sample code較好理解
* 注意 `taskObservable` 算是list，不是list item

DataSource.java
```java
public class DataSource {

	public static List<Task> createTasksList() {
		List<Task> tasks = new ArrayList<>();
		tasks.add(new Task("1.Take out the trash", true, 3));
		tasks.add(new Task("2.Walk the dog", false, 2));
		tasks.add(new Task("3.Make my bed", true, 1));
		tasks.add(new Task("4.Unload the dishwasher", false, 0));
		tasks.add(new Task("5.Make dinner", true, 5));
		return tasks;
	}
}
```
MainActivity.java
```java
// Create an Observable Task object:
Observable<Task> taskObservable = Observable
        .fromIterable(DataSource.createTasksList())
        // working on background thread which RxJava uses Schedulers for
        .subscribeOn(Schedulers.io())
        .filter(new Predicate<Task>() {
            @Override
            public boolean test(@NonNull Task task) {
                // This will work on background thread
                Log.d(TAG, "filter: " + Thread.currentThread().getName());
                try {
                    Thread.sleep(1000);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                // filter the items which return true
                return task.isComplete();
            }
        })
        // show the result on UI thread which RxAndroid uses AndroidSchedulers for
        .observeOn(AndroidSchedulers.mainThread());

// Subscribing to an Observable:
taskObservable.subscribe(new Observer<Task>() {
    @Override
    public void onSubscribe(Disposable d) {
        Log.d(TAG, "onSubscribe: called.");
    }

    @Override
    public void onNext(Task task) {
        Log.d(TAG, "onNext: " + Thread.currentThread().getName());
        Log.d(TAG, "onNext: " + task.getDescription());
    }

    @Override
    public void onError(Throwable e) {
        Log.e(TAG, "onError: ", e);
    }

    @Override
    public void onComplete() {
        Log.d(TAG, "onComplete: called.");
    }
});

// Output (第一排是時間): 
// 12:13:08: onSubscribe: called.
// 12:13:08: filter: Thread:RxCachedThreadScheduler-1 task: 1.Take out the trash
// 12:13:09: filter: Thread:RxCachedThreadScheduler-1 task: 2.Walk the dog
// 12:13:09: onNext: Thread: main task: 1.Take out the trash
// 12:13:10: filter: Thread:RxCachedThreadScheduler-1 task: 3.Make my bed
// 12:13:11: filter: Thread:RxCachedThreadScheduler-1 task: 4.Unload the dishwasher
// 12:13:11: onNext: Thread: main task: 3.Make my bed
// 12:13:12: filter: Thread:RxCachedThreadScheduler-1 task: 5.Make dinner
// 12:13:14: onNext: Thread: main task: 5.Make dinner
// 12:13:14: onComplete: called.
```

## Flowables
### What is a Flowable?
* in RxJava2 you have two 'Observable' object classes instead of one:
    * Observable
    * And Flowable

* The property that distinguishes one from the other is backpressure.
    * Observables are not backpressure-aware 
    * Flowables are backpressure-aware 

### Backpressure
* Definition of Backpressure from the Rx docs:

    > Backpressure is when in a Flowable processing pipeline can't process the values fast enough and need a way to tell the upstream producer to slow down.
* Two ways to treat Backpressure
    * Hot sources:

        The Observables continue pushing objects towards the Observers regardless of if they can keep up or not. Basically it's up to the Observers to keep up with the objects.

        If and when the Observers are not able to keep up with the emitted objects, they need to be buffered or handled in some way.

    * Cold sources:

        The objects emitted by the Observables are said to be emitted lazily. Meaning: The Observables begin emitting objects when the Observers want and at a rate suitable to the Observer.

        The objects emitted by the Observables do not need to be buffered because the whole process is basically at the discretion of the Observer.

### Backpressure Strategies for Hot sources
There's a number of backpressure operators you can apply to Flowables to implement different buffering strategies.

* Strategy 1: onBackpressureBuffer() for Hot sources
    ```java
    Flowable<Integer> flowable = Flowable.range(0, 1000000);

    flowable.onBackpressureBuffer()
            .observeOn(Schedulers.computation())
            .subscribe(new FlowableSubscriber<Integer>() {
                @Override
                public void onSubscribe(Subscription s) {

                }

                @Override
                public void onNext(Integer integer) {
                    Log.d(TAG, "onNext: " + integer);
                }

                @Override
                public void onError(Throwable t) {
                    Log.e(TAG, "onError: ", t);
                }

                @Override
                public void onComplete() {

                }
            });
    ```
* [todo] [Other Strategies For Refs](https://github.com/ReactiveX/RxJava/wiki/Backpressure-(2.0))
### Other
* 剩下就是講Flowables and Observables互相轉換的方法，以及提供一些 References [todo]
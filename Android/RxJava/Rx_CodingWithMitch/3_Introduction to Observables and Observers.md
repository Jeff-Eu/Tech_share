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

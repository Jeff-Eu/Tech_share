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

# RxJava
## Quick Learning Guide
1. On [CodingWithMitch](https://codingwithmitch.com/courses/rxjava-rxandroid-for-beginners/) from beginning to the "Backpressure Strategies" chapter.
2. 
## Resources
* [Documentation from official site](https://github.com/ReactiveX/RxJava/wiki): Not detailed in Java language
* [RxJava from TutorialsPoint](https://www.tutorialspoint.com/rxjava/)
    * RxJava is a Java based extension of ReactiveX. ReactiveX is a project which aims to provide reactive programming concept to various programming languages. Reactive Programming refers to the scenario where program reacts as and when data appears. It is a event based programming concept and events can propagate to observers. ReactiveX which implements Reactive Programming is a combination of the best ideas from the Observer pattern, the Iterator pattern, and functional programming.


### Hello World !
```java
public static void hello(String... args) {
  Flowable.fromArray(args).subscribe(s -> System.out.println("Hello " + s + "!"));
}
```
output
```
hello("Ben", "George");
Hello Ben!
Hello George!
```

### Subject ([Ref](http://reactivex.io/documentation/subject.html))
There are four varieties of Subject that are designed for particular use cases.
1. [PublishSubject](https://www.tutorialspoint.com/rxjava/rxjava_publishsubject.htm)
```java
import io.reactivex.subjects.PublishSubject;
public class ObservableTester  {
   public static void main(String[] args) {   
      final StringBuilder result1 = new StringBuilder();
      final StringBuilder result2 = new StringBuilder();         

      PublishSubject<String> subject = PublishSubject.create(); 
      subject.subscribe(value -> result1.append(value) ); 
      subject.onNext("a"); 
      subject.onNext("b"); 
      subject.onNext("c"); 
      subject.subscribe(value -> result2.append(value)); 
      subject.onNext("d"); 
      subject.onComplete();

      //Output will be abcd 
      System.out.println(result1);
      //Output will be d only
      //as subscribed after c item emitted.
      System.out.println(result2);
   }
}

// Output:
// abcd
// d
```
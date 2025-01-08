//
//  main.cpp
//  jrx
//
//  Created by Jonas Johansson on 12/17/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

#include "jrx.h"
#include <string>
#include <cassert>


using namespace std;


void quickStart() {
    // Create a BehaviorSubject seeded with an initial value
    auto observable1 = BehaviorSubject<int>::seeded(5);
    int value1 = 0;

    // Subscribe to the observable
    observable1->subscribe([&](int value) {
        value1 = value;
        std::cout << "Got value: " << value << "\n";
    });

    // BehaviorSubject immediately emits its current value
    // Output: "Got value: 5"

    // Create a PublishSubject
    auto observable2 = PublishSubject<int>::create();
    int value2 = 0;

    // Map, filter, and subscribe to the observable
    observable2
        ->map<int>([](int value) { return value * 2; }) // Multiply by 2
        ->filter([](int value) { return value > 10; })  // Only allow values > 10
        ->subscribe([&](int value) {
            value2 = value;
            std::cout << "Got value: " << value << "\n";
        });

    // Emit values
    observable2->onNext(5);  // Filtered out (10 is not > 10)
    observable2->onNext(10); // Output: "Got value: 20"

}

void bigTest(bool print) {
    
    struct Person {
        string firstName;
        string lastName;
        int age;
    };
    
    // Create two observables that will serve the data
    auto observable1 = Observable<string>::just("David");
    auto observable2 = Observable<string>::just("Smith");
    auto observable3 = ReplaySubject<int>::create(); // let's say this value is delivered at some other point
    
    // Combining two streams into a new stream that contains the age and name of a person
    auto ptr = Observable<Person>::combineLatest({
        { observable1, &Person::firstName },
        { observable2, &Person::lastName },
        { observable3, &Person::age },
    })
    // Ensure we're only receiving signals where the age is above 5
    ->filter([](Person value) {
        return value.age > 5.0f;
    })
    // Convert the person into a string for display
    ->map<string>([](Person value){
        return value.firstName + value.lastName + string(", ") + to_string(value.age) + string(" years old");
    })
    ->subscribe([print](auto value) {
        if (print) {
            std::cout << "Got a person '" << value << "'\n";
        }
    });
    
    // Merge three observables into one (omitting in order):
    Observable<int>::merge({
        Observable<int>::just(8),
        Observable<int>::just(9),
        Observable<int>::just(13),
        Observable<int>::just(17)
    })
    ->subscribe([&](int value) {
        observable3->onNext(value);
    });
    
    // Or use the forEach method to send values to the observable
    Observable<int>::forEach({8,9,13,17})
    ->subscribe([&](int value) {
        observable3->onNext(value);
    });
    
    /*
    Observable<int>::forEach({8,9,13,17})
    ->subscribe([&](int value) {
        observable3->onNext(value);
    });*/
    
    observable3->onNext(12);
    observable3->onNext(13);
}


int main(int argc, const char * argv[]) {
    
    quickStart();
    // smallTest();
    // test();
    bigTest(true);
    
    std::cout << "---- Running memory leaks test\n";
    
    testLeakage(10000, [](){
        bigTest(false);
    });
    
    std::cout << "---- Program ended\n";
    
    return 0;
}


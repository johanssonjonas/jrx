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



void test() {
    
    // Test behavior subjects
    auto observable1 = BehaviorSubject<int>::seeded(5);
    bool isSubscribed1 = false;
    int value1 = 0;
    
    observable1->observeOnSubscribe([&] {
        isSubscribed1 = true;
    });
    assert(!isSubscribed1);
    
    auto tmp = observable1->subscribe([&] (int value) {
        value1 = value;
        std::cout << "Got value: " << value << "\n";
    });
    assert(value1 == 5);
    assert(isSubscribed1);
    
    // Test published subject
    auto observable2 = PublishSubject<int>::create();
    bool isSubscribed2 = false;
    int value2 = 0;
    
    observable2->observeOnSubscribe([&] {
        isSubscribed2 = true;
    });
    assert(!isSubscribed2);
    
    auto tmp2 = observable2
    ->map<int>([](int value) {
        return value * 2;
    })
    ->filter([](int value) {
        return value > 10;
    })
    ->subscribe([&] (int value) {
        value2 = value;
        std::cout << "Got value: " << value << "\n";
    });
    assert(value2 == 0);
    assert(isSubscribed2);
    
    observable2->onNext(5);
    observable2->onNext(10);
    assert(value2 == 20);
    
    // All done
    std::cout << "Test passed\n";
}


void smallTest() {
    auto observable1 = BehaviorSubject<int>::seeded(5);
    auto tmp = observable1->subscribe([&] (int value) {
        std::cout << "Got value: " << value << "\n";
    });
}

void bigTest(bool print) {
    struct Person {
        int age;
        std::string name;
    };
    
    // Create two observables that will serve the data
    auto observable0 = BehaviorSubject<int>::seeded(5);
    auto observable1 = Observable<string>::just("David");
    
    // Update the default value
    observable0->onNext(10);
    
    // Combining two streams into a new stream that contains the age and name of a person
    auto ptr = Observable<Person>::combineLatest({
        { observable0, &Person::age },
        { observable1, &Person::name },
    });
    /*
    
    ->filter([](Person value) {
        return value.age > 5.0f;
    })
    ->map<string>([](Person value){
        return value.name + string(value.name.length() > 0,' ') + to_string(value.age);
    })
    ->subscribe([print](auto value) {
        if (print) {
            // std::cout << "Got a person '" << value << "'\n";
        }
    });*/
    
    observable0->named = "Seeded";
    observable1->named = "Just";
    ptr->named = "CombineLatest";
    
    observable0->onNext(12);
    
    if (print) {
        std::cout << "---- Program ended\n";
    }
    
    std::cout << "Living count: " << RetainedObject::getAliveObjectCount() << "\n";
    
    ptr.destroy();
    observable0.destroy();
    observable1.destroy();
    
    std::cout << "Living count: " << RetainedObject::getAliveObjectCount() << "\n";
    
}


int main(int argc, const char * argv[]) {
    /*
    testLeakage(10, [](){
        volatile char *test = new char[1000];
        // put a random number
        for (int i = 0; i < 1000; i++) {
            test[i] = i % 255;
        }
        std::cout << "test[0]" << test[0] << "\n";
    });
    
    testLeakage(1, [](){
        smallTest();
        test();
    });
    */
    testLeakage(10000, [](){
        bigTest(false);
    });
    
    return 0;
}


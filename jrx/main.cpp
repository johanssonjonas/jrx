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



void test() {
    
    // Test behavior subjects
    auto observable1 = BehaviorSubject<int>::seeded(5);
    bool isSubscribed1 = false;
    int value1 = 0;
    
    observable1->observeOnSubscribe([&] {
        isSubscribed1 = true;
    });
    assert(!isSubscribed1);
    
    observable1->subscribe([&] (int &value) {
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
    
    observable2
    ->map<int>([](int value) {
        return value * 2;
    })
    ->subscribe([&] (int value) {
        value2 = value;
        std::cout << "Got value: " << value << "\n";
    });
    assert(value2 == 0);
    assert(isSubscribed2);
    
    observable2->onNext(10);
    assert(value2 == 20);
    
    // All done
    std::cout << "Test passed\n";
}


int main(int argc, const char * argv[]) {
    
    test();
    // UntypedSubscrinber = ColdObservable
    // TypedSubscriber = ColdObservable
    // ReplayTypedSubscriber = HotObservable // New
    // PartialValueHolder = ReplayTypedSubscriber
    
    struct Person {
        int age;
        std::string name;
    };
    auto observable0 = Observable<int>::just(5);
    auto observable2 = Observable<std::string>::just("David");
    
    // Combining two streams intoa  new stream that contains the age and name of a person
    Observable<Person>::combineLatest({
        { observable0, &Person::age },
        { observable2, &Person::name }
    })/*
    ->filter([](Person &value) {
        return value.age > 3.0f;
    })*/
    ->map<std::string>([](Person value){
        return value.name + std::string(value.name.length() > 0,' ') + std::to_string(value.age);
    })
    ->subscribe([](std::string value) {
        std::cout << "Got a person '" << value << "\n";
    });
    
    std::cout << "---- Program ended\n";
    
    return 0;
}


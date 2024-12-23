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

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))

#define canDoMemoryTest 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach/mach.h>

    // printf("System is POSIX-compliant. POSIX version: %ld\n", _POSIX_VERSION);
    size_t get_memory_usage() {
        struct task_basic_info info;
        mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;

        if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &infoCount) != KERN_SUCCESS) {
            return 0; // Failed to retrieve info
        }

        return info.resident_size; // Memory in bytes
    }
#else
#warning Could not determine memory usage of the test for this system. This should be all fine though!
#endif

void bigTest(bool print) {
    struct Person {
        int age;
        std::string name;
    };
    
    // Create two observables that will serve the data
    auto observable0 = BehaviorSubject<int>::seeded(5);
    auto observable2 = Observable<string>::just("David");
    
    // Update the default value
    observable0->onNext(10);
    
    // Combining two streams into a new stream that contains the age and name of a person
    auto ptr = Observable<Person>::combineLatest({
        { observable0, &Person::age },
        { observable2, &Person::name },
    })
    ->filter([](Person value) {
        return value.age > 5.0f;
    })
    ->map<string>([](Person value){
        return value.name + string(value.name.length() > 0,' ') + to_string(value.age);
    })
    ->subscribe([print](string value) {
        if (print) {
            std::cout << "Got a person '" << value << "'\n";
        }
    });
    
    observable0->onNext(12);
    
    if (print) {
        std::cout << "---- Program ended\n";
    }
     
}

int main(int argc, const char * argv[]) {
    
    smallTest();
    test();
    
#ifdef canDoMemoryTest
    auto bytesUsed = get_memory_usage();
#endif
    
    for (int i = 0; i < 10000; i++) {
        bigTest(false);
    }
    
#ifdef canDoMemoryTest
    auto diff = get_memory_usage() - bytesUsed;
    std::cout << "Memory leak: " << diff << " bytes \n";
#endif
    
    
    return 0;
}


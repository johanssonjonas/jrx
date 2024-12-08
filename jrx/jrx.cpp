//
//  jorx.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#include "jrx.h"
#include <string>




int main(int argc, const char * argv[]) {
    
    struct Person {
        int age;
        std::string name;
    };
    auto observable1 = BehaviorRelay<int>::seeded(23);
    auto observable2 = Observable<std::string>::just("David");
    
    Observable<Person>::combineLatest({
        { std::static_pointer_cast<Observable<int>>(observable1), &Person::age },
        // { test, &Person::age },
        // { observable1, &Person::age },
        { observable2, &Person::name }
    })
    ->filter([](Person &value) {
        return value.age > 3.0f;
    })
    ->map<std::string>([](Person &value){
        return value.name + std::string(value.name.length() > 0,' ') + std::to_string(value.age);
    })
    ->subscribe([](std::string &value) {
        std::cout << "Got data for person: " << value << "\n";
    });
    
    std::cout << "cool\n";
    
    return 0;
}

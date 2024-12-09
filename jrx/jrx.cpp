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
    auto observable0 = Observable<int>::just(5);
    // auto observable1 = BehaviorRelay<int>::seeded(5);
    auto observable2 = Observable<std::string>::just("David");
    
    observable0->subscribe([](int &value) {
        std::cout << "There is person named: " << value << "\n";
    });
    
    // Listening to the age of a person directly
    observable2->subscribe([](std::string &value) {
        std::cout << "There is person named: " << value << "\n";
    });
    
    // Combining two streams intoa  new stream that contains the age and name of a person
    Observable<Person>::combineLatest({
        { observable0, &Person::age },
        // { observable1.toObservable<int>(), &Person::age },
        { observable2, &Person::name }
    })
    /*
    ->filter([](Person &value) {
        return value.age > 3.0f;
    })
    ->map<std::string>([](Person &value){
        return value.name + std::string(value.name.length() > 0,' ') + std::to_string(value.age);
    })*/
    ->subscribe([](Person &value) {
        std::cout << "Got a person with a name and age: " << value.name << "\n";
    });
    
    std::cout << "---- Program ended\n";
    
    return 0;
}

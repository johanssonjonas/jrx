//
//  main.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-01.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#include "jrx.h"
#include <string>


int main(int argc, const char * argv[]) {
    
    struct Person {
        int age;
        std::string name;
    };
	
    auto observable1 = Observable<int>::just(23);
    auto observable2 = Observable<std::string>::just("David");
	
    Observable<Person>::combineLatest({
        {observable1, &Person::age},
        {observable2, &Person::name}
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
    
    return 0;
}

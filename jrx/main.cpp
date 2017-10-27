//
//  main.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-01.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#include "jrx.h"


#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;
//using namespace std::literals;
//using namespace std::chrono_literals;
//using namespace std::literals::chrono_literals;

//template <class Combined, class Y>
//auto makePartialObservable(std::shared_ptr<Observable<Y>> _pObservable, Y Combined::* valueSetter) {
//    return std::shared_ptr<PartialValueHolder<Combined>>{
//        new PartialValueObserver<Y, Combined> { _pObservable, valueSetter }
//    };
//}





//template<class Result>
//auto testFunc(std::vector<PartialValueObserverPtrFactory<Result>> blargs) -> void
//{
//
//}


int main(int argc, const char * argv[]) {

    struct SomeClass {
        float x;
        std::string y;
    };

    auto observable1 = Observable<float>::just(5.0f);
    auto observable2 = Observable<std::string>::just("hello");
    
//    testFunc<SomeClass>({
//        {observable1, &SomeClass::x}
//    });

    Observable<SomeClass>::combineLatest({
        {observable1, &SomeClass::x},
        {observable2, &SomeClass::y}
    })
    ->filter([](SomeClass &value) {
        return value.x > 3.0f;
    })
    ->subscribe([](SomeClass &value) {
        std::cout << "value: " << value.y << "\n";
    });

//    Observable<int>::forEach({5, 2, 1, 3})
//        ->filter([](int &value){ return value > 2; })
//        ->on([](int &value) {
//            // print here
//            std::cout << "here: " << value << "\n";
//            std::this_thread::sleep_for(5s);
//        })
//        ->map<std::string>([](int &value) {
//            return std::to_string(value);
//        })
//        ->subscribe([](std::string &value) {
//            std::cout << "value: " << value << "\n";
//        });
    
    // insert code here...
//    std::cout << "Hello, World!\n";
    return 0;
}











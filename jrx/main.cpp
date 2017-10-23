//
//  main.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-01.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#include "jrx.h"







int main(int argc, const char * argv[]) {
    
//    auto tmp = Observable<int, int>::forEach({5, 2, 1, 3});
//        ->filter([](int &value){ return value > 2; });
//        ->subscribe([](int &value) {
//            std::cout << "value: " << value << "\n";
//        });


//    std::shared_ptr<Observable<int, std::string>> ptr {
//        new Map<int, std::string>{
//            [](int &value) -> std::string {
//                return "";
//            }
//        }
//    };

//
//    struct CombiningMap {
//        float x;
//        std::string y;
//    };
//
//    auto observable1 = Observable<float>::just(5.0f);
//    auto observable2 = Observable<std::string>::just("hello");
//
//    CombineLatest<CombiningMap> combined {
//        {
//            PartialValueObserver<float, CombiningMap> { observable1, &CombiningMap::x },
//            PartialValueObserver<std::string, CombiningMap> { observable2, &CombiningMap::y }
//        }
//    };

    
    /*
    CombineLatest<CombiningMap, float, std::string> tmp {
        [](float value, CombiningMap hurp) {
            hurp.x = value;
        },
        [](std::string value, CombiningMap hurp) {
            hurp.y = value;
        }
    };*/
    
    Observable<int>::forEach({5, 2, 1, 3})
        ->filter([](int &value){ return value > 2; })
    	->on([](int &value) {
			// print here
            std::cout << "here: " << value << "\n";
    	})
        ->map<std::string>([](int &value) {
            return std::to_string(value);
        })
        ->subscribe([](std::string &value) {
            std::cout << "value: " << value << "\n";
        });
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}











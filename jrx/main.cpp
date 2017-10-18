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
//    auto ptr2 = std::static_pointer_cast<BaseObservable<int>>(ptr);

//    tmp->m_vChildren.push_back(ptr2);

    
    
    Observable<int>::forEach({5, 2, 1, 3})
        ->filter([](int &value){ return value > 2; })
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











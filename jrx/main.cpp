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
    
    struct CombiningMap {
        float x;
        std::string y;
    };

    auto observable1 = Observable<float>::just(5.0f);
    auto observable2 = Observable<std::string>::just("hello");

    CombineLatest<CombiningMap> combined {
        {
            PartialValueObserver<float, CombiningMap> { observable1, &CombiningMap::x },
            PartialValueObserver<std::string, CombiningMap> { observable2, &CombiningMap::y }
        }
    };



//    auto values = Observable<CombiningMap>::combineLatest<CombiningMap, float, std::string>(observable1,
//                                                                                   observable2,
//                                                                                   &CombiningMap::x,
//                                                                                   &CombiningMap::y);


    auto untyped1 = observable1->map<float>([](float value){
        return value;
    });

    auto untyped2 = untyped1->untyped(untyped1);




//    auto values = Observable<CombiningMap>::combineLatest<CombiningMap, float, std::string>(
//        std::make_pair(observable1, [](float value, CombiningMap obj) { obj.x = value; }),
//        std::make_pair(observable2, [](std::string value, CombiningMap obj) { obj.y = value; })
//    );

    CombiningMap helpisdf;
    
    
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











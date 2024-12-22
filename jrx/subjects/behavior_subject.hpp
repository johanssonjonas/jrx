//
//  jrx_behavior_relay.cpp
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

template <class _SenderType> auto jrx::subjects::BehaviorSubject<_SenderType>
::seeded(_SenderType value) -> ObservablePtr<_SenderType> {
    auto obj = new BehaviorSubject<_SenderType>();
    auto ptr = obj->template getPtr<Observable<_SenderType>>();
    ptr->onNext(value);
    return ptr;
    
    /*
    Showing Recent Messages
    No viable conversion from returned value of type
        'RetainablePointer<jrx::core::BehaviorSubject<int>>' to function return type
        'RetainablePointer<Observable<BehaviorSubject<int, int>, BehaviorSubject<int, int>>>'
    */
}

template <class _SenderType> jrx::subjects::BehaviorSubject<_SenderType>
::BehaviorSubject() {
    
}

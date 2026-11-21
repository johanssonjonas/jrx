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
}

template <class _SenderType> jrx::subjects::BehaviorSubject<_SenderType>
::BehaviorSubject() {
    
}

//
//  jrx_behavior_relay.cpp
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

template <class _SenderType> auto jrx::core::PublishSubject<_SenderType>
::create() -> ObservablePtr<_SenderType> {
    auto obj = new PublishSubject<_SenderType>();
    auto ptr = obj->template getPtr<Observable<_SenderType>>();
    return ptr;
}

template <class _SenderType> jrx::core::PublishSubject<_SenderType>
::PublishSubject() : Observable<_SenderType>() {
    
}

template <class _SenderType> auto jrx::core::PublishSubject<_SenderType>
::onNext(_SenderType _tyValue) -> void {
    if (!_bStarted) {
        _bStarted = true;
        TypedSubscriber<_SenderType>::onStart();
    }
    TypedSubscriber<_SenderType>::onNext(_tyValue);
}

template <class _SenderType> auto jrx::core::PublishSubject<_SenderType>
::subscribe(std::function<void(_SenderType)> _pFunc) -> ObservableDisposer {
    return TypedSubscriber<_SenderType>::subscribe(_pFunc);
}

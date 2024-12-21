//
//  jrx_behavior_relay.cpp
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

template <class _SenderType, class _ChildrenType> auto jrx::core::BehaviorSubject<_SenderType, _ChildrenType>
::seeded(_SenderType value) -> ObservablePtr<BehaviorSubject<_SenderType>> {
    auto res = ObservablePtr<BehaviorSubject<_SenderType>> {
        new BehaviorSubject<_SenderType>()
    };
    res->onNext(value);
    return res;
}

template <class _SenderType, class _ChildrenType> jrx::core::BehaviorSubject<_SenderType, _ChildrenType>
::BehaviorSubject() {
    
}

template <class _SenderType, class _ChildrenType> auto jrx::core::BehaviorSubject<_SenderType, _ChildrenType>
::onNext(_SenderType _tyValue) -> void {
    if (!_bStarted) {
        _bStarted = true;
        TypedSubscriber<_SenderType>::onStart();
    }
    value = _tyValue;
    TypedSubscriber<_SenderType>::onNext(value);
}

template <class _SenderType, class _ChildrenType> auto jrx::core::BehaviorSubject<_SenderType, _ChildrenType>
::subscribe(func_t<void(_SenderType &)> _pFunc) -> void {
    if (_bStarted) {
        _pFunc(value);
    }
    TypedSubscriber<_SenderType>::subscribe(_pFunc);
}

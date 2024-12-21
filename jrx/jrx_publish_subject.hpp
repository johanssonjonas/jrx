//
//  jrx_behavior_relay.cpp
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

template <class _SenderType, class _ChildrenType> auto jrx::core::PublishSubject<_SenderType, _ChildrenType>
::create() -> ObservablePtr<PublishSubject<_SenderType>> {
    auto res = ObservablePtr<PublishSubject<_SenderType>> {
        new PublishSubject<_SenderType>()
    };
    return res;
}

template <class _SenderType, class _ChildrenType> jrx::core::PublishSubject<_SenderType, _ChildrenType>
::PublishSubject() {
    
}

template <class _SenderType, class _ChildrenType> auto jrx::core::PublishSubject<_SenderType, _ChildrenType>
::onNext(_SenderType _tyValue) -> void {
    if (!_bStarted) {
        _bStarted = true;
        TypedSubscriber<_SenderType>::onStart();
    }
    TypedSubscriber<_SenderType>::onNext(_tyValue);
}

template <class _SenderType, class _ChildrenType> auto jrx::core::PublishSubject<_SenderType, _ChildrenType>
::subscribe(func_t<void(_SenderType &)> _pFunc) -> void {
    TypedSubscriber<_SenderType>::subscribe(_pFunc);
}

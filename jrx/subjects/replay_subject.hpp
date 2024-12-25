//
//  jrx_replay_subject.hpp
//  jrx
//
//  Created by Jonas Johansson on 12/21/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

template <class _SenderType> auto jrx::subjects::ReplaySubject<_SenderType>
::create() -> ObservablePtr<_SenderType> {
    auto obj = new ReplaySubject<_SenderType>();
    auto ptr = obj->template getPtr<Observable<_SenderType>>();
    return ptr;
}

template <class _SenderType> jrx::subjects::ReplaySubject<_SenderType>
::ReplaySubject() {
    
}

template <class _SenderType> auto jrx::subjects::ReplaySubject<_SenderType>
::onNext(_SenderType _tyValue) -> void {
    if (!_bStarted) {
        _bStarted = true;
        TypedSubscriber<_SenderType>::onStart();
    }
    value = _tyValue;
    TypedSubscriber<_SenderType>::onNext(value);
}

template <class _SenderType> auto jrx::subjects::ReplaySubject<_SenderType>
::subscribe(std::function<void(_SenderType)> _pFunc) -> ObservableDisposer {
    if (_bStarted) {
        _pFunc(value);
    }
    return TypedSubscriber<_SenderType>::subscribe(_pFunc);
}

template <class _SenderType> auto jrx::subjects::ReplaySubject<_SenderType>
::observeOnNext(std::function<void()> _pFunc) -> void {
    if (_bStarted) {
        _pFunc();
    }
    TypedSubscriber<_SenderType>::observeOnNext(_pFunc);
}

//
//  jrx_behavior_relay.cpp
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

template <class _SenderType, class _ChildrenType>
jrx::core::BehaviorRelay<_SenderType, _ChildrenType>::BehaviorRelay(typename Observable<_SenderType>::value_factory_t _pOnSubscribe)
: Observable<_SenderType, _ChildrenType>(_pOnSubscribe) {
}

template <class _SenderType, class _ChildrenType>
auto jrx::core::BehaviorRelay<_SenderType, _ChildrenType>::seeded(_SenderType value) -> ObservablePtr<BehaviorRelay<_SenderType, _ChildrenType>> {
    std::shared_ptr<BehaviorRelay<_SenderType>> observable = std::shared_ptr<BehaviorRelay<_SenderType>> {
        new BehaviorRelay<_SenderType>([&] {
        })
    };
    observable->add(value);
    return observable;
}

template <class _SenderType, class _ChildrenType>
auto jrx::core::BehaviorRelay<_SenderType, _ChildrenType>::add(_SenderType value) -> void {
    this->subject = value;
    this->onNext(value);
}

template <class _SenderType, class _ChildrenType>
auto jrx::core::BehaviorRelay<_SenderType, _ChildrenType>::replay(std::function<void(_ChildrenType &)> _pFunc) -> void {
    _pFunc(this->subject);
}

//
//  jrx_subscriber.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-09.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

template <class _Ty> auto jrx::core::TypedSubscriber<_Ty>
::onNext(_Ty _tyValue) -> void {
    
    UntypedSubscriber::onNextValue();
    
    for (auto func : m_vSubscribersOnNext) {
        func(_tyValue);
    }
    
    for (int i = 0; i < m_vTypedChildren.size(); i++) {
        m_vTypedChildren[i]->onNext(_tyValue);
    }
}

template <class _Ty> auto jrx::core::TypedSubscriber<_Ty>
::subscribe(func_t<void(_Ty &)> _pFunc) -> void {
    if (!_bSubscribed) {
        _bSubscribed = true;
        UntypedSubscriber::onSubscribe();
    }
    m_vSubscribersOnNext.push_back(_pFunc);
}


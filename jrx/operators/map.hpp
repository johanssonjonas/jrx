//
//  jorx_operator_map.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _SenderType, class _ParentType> jrx::operators::Map<_SenderType, _ParentType>
::Map(Observable<_ParentType> *_pParent, std::function<_SenderType(_ParentType &)> _pPreducate) {
    _pParent->observeOnNextValue([=](auto value) {
        this->onNext(_pPreducate(value));
    });
}

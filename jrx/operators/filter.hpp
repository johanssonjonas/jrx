//
//  jorx_operator_where.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _Ty> jrx::operators::Filter<_Ty>
::Filter(Observable<_Ty> *_pParent, std::function<bool(_Ty &)> _pPreducate)
: m_pPreducate(_pPreducate) {
    _pParent->observeOnNextValue([=](auto value) {
        if (_pPreducate(value)) {
            this->onNext(value);
        }
    });
}

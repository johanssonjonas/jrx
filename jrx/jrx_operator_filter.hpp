//
//  jorx_operator_where.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _Ty, class _Ty2>
Filter<_Ty, _Ty2>::Filter(std::function<bool(_Ty &)> _pPreducate) {
    m_pPreducate = _pPreducate;
}

template <class _Ty, class _Ty2>
auto Filter<_Ty, _Ty2>::onNext(_Ty &value) -> void {
    
    if (m_pPreducate(value)) {
        Observable<_Ty, _Ty2>::onNext(value);
    }
}

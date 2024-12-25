//
//  jorx_operator_where.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _Ty>
Filter<_Ty>::Filter(std::function<bool(_Ty &)> _pPreducate) {
    m_pPreducate = _pPreducate;
}

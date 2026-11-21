//
//  jrx_partial_value_holder.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _Ty> jrx::factories::fragments::PartialValueHolder<_Ty>
::PartialValueHolder() {
    m_pSharedObject = nullptr;
}

template <class _Ty> auto jrx::factories::fragments::PartialValueHolder<_Ty>
::setSharedObject(_Ty *_pSharedObject) -> void {
    m_pSharedObject = _pSharedObject;
}

template <class _Ty> auto jrx::factories::fragments::PartialValueHolder<_Ty>
::getSharedObject() -> _Ty * {
    return m_pSharedObject;
}

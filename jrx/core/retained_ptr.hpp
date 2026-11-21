//
//  jrx_retained_ptr.hpp
//  jrx
//
//  Created by Jonas Johansson on 12/22/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template <class _Ty> jrx::core::RetainedPtr<_Ty>
::RetainedPtr()
: m_bManuallyDestroyed(false) {

}

template <class _Ty> jrx::core::RetainedPtr<_Ty>
::RetainedPtr(const RetainedPtr<_Ty> &ptr)
: m_bManuallyDestroyed(false) {
    m_pPtr = ptr.m_pPtr;
    retain();
}

template <class _Ty> jrx::core::RetainedPtr<_Ty>
::RetainedPtr(_Ty *_pPtr)
: m_bManuallyDestroyed(false) {
    m_pPtr = _pPtr;
    retain();
}

template <class _Ty> jrx::core::RetainedPtr<_Ty>
::~RetainedPtr() {
    if (!m_bManuallyDestroyed) {
        release();
    }
}

template <class _Ty> auto jrx::core::RetainedPtr<_Ty>
::destroy() -> void {
    release();
    m_bManuallyDestroyed = true;
    m_pPtr = nullptr;
}

template <class _Ty> auto jrx::core::RetainedPtr<_Ty>
::operator=(const RetainedPtr<_Ty> &ptr) -> RetainedPtr<_Ty> & {
    if (this != &ptr) {
        if (m_pPtr != nullptr) {
            release();
        }
        m_pPtr = ptr.m_pPtr;
        retain();
    }
    return *this;
}

template <class _Ty> auto jrx::core::RetainedPtr<_Ty>
::operator->() -> _Ty * {
    return m_pPtr;
}

template <class _Ty> auto jrx::core::RetainedPtr<_Ty>
::operator->() const -> _Ty * {
    return m_pPtr;
}

template <class _Ty> auto jrx::core::RetainedPtr<_Ty>
::c_ptr() -> _Ty * {
    return m_pPtr;
}

template <class _Ty> auto jrx::core::RetainedPtr<_Ty>
::retain() -> void {
    assert(m_pPtr != nullptr);
    
    m_pPtr->retain();
}

template <class _Ty> auto jrx::core::RetainedPtr<_Ty>
::release() -> void {
    assert(m_pPtr != nullptr);
    
    if (m_pPtr->release()) {
        m_pPtr = nullptr;
    }
}

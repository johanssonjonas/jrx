//
//  jrx_observable_ptr.hpp
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template <class _Ty>
class jrx::core
    ::RetainedPtr {
public:
    
    RetainedPtr();
    RetainedPtr(const RetainedPtr<_Ty> &ptr);
    ~RetainedPtr();
    
    explicit RetainedPtr(_Ty *_pPtr);
    
    auto destroy() -> void;
    auto operator=(const RetainedPtr<_Ty> &ptr) -> RetainedPtr<_Ty> &;
    auto operator->() -> _Ty *;
    auto operator->() const -> _Ty *;
    auto c_ptr() -> _Ty *;
    
private:
    
    auto retain() -> void;
    auto release() -> void;
    
    _Ty *m_pPtr;
    bool m_bManuallyDestroyed = false;
};

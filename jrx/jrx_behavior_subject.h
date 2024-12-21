//
//  jrx_behavior_relay.h
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template <class _SenderType, class _ChildrenType = _SenderType>
class jrx::core::BehaviorSubject
    : public jrx::core::Observable<_SenderType, _ChildrenType> {
public:
    
    static auto seeded(_SenderType value) -> ObservablePtr<BehaviorSubject<_SenderType>>;
    
    virtual auto onNext(_SenderType _tyValue) -> void override;
    virtual auto subscribe(func_t<void(_SenderType &)> _pFunc) -> void override;
    
private:
    BehaviorSubject();
    
    _SenderType value;
    bool _bStarted;
};

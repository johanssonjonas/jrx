//
//  jrx_behavior_relay.h
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template <class _SenderType, class _ChildrenType = _SenderType>
class jrx::core::BehaviorRelay
    : public jrx::core::Observable<_SenderType, _ChildrenType> {
public:
    
    static auto seeded(_SenderType value) -> ObservablePtr<BehaviorRelay<_SenderType, _ChildrenType>>;
    
    BehaviorRelay(typename Observable<_SenderType>::value_factory_t _pOnSubscribe);
    
    auto add(_SenderType value) -> void;
        
    auto replay(std::function<void(_ChildrenType &)> _pFunc) -> void override;

private:
    _SenderType subject;
};

//
//  jrx_behavior_relay.h
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template <class _SenderType>
class jrx::core::BehaviorSubject
    : public jrx::core::ReplaySubject<_SenderType> {
public:
    
    static auto seeded(_SenderType value) -> ObservablePtr<_SenderType>;
    
private:
    BehaviorSubject();
};

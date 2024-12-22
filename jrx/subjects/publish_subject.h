//
//  jrx_behavior_relay.h
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template <class _SenderType>
class jrx::subjects::PublishSubject
    : public jrx::core::Observable<_SenderType> {
public:
    
    static auto create() -> ObservablePtr<_SenderType>;
    
    PublishSubject();
        
    virtual auto onNext(_SenderType _tyValue) -> void override;
    virtual auto subscribe(std::function<void(_SenderType)> _pFunc) -> ObservableDisposer override;
    
private:
    
    bool _bStarted;
};

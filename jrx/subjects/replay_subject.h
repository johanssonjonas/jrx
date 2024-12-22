//
//  jrx_replay_subject.h
//  jrx
//
//  Created by Jonas Johansson on 12/21/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template <class _SenderType>
class jrx::subjects::ReplaySubject
    : public jrx::core::Observable<_SenderType> {
public:
    
    ReplaySubject();
    
    virtual auto onNext(_SenderType _tyValue) -> void override;
    virtual auto subscribe(std::function<void(_SenderType)> _pFunc) -> ObservableDisposer override;
    virtual auto observeOnNext(std::function<void()> _pFunc) -> void override;
        
private:
    
    _SenderType value;
    bool _bStarted;
};

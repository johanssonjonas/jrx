//
//  jrx_subscriber.hpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-09.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jrx_subscriber_hpp
#define jrx_subscriber_hpp

template <class _Ty>
class jrx::core::TypedSubscriber
    : public jrx::core::UntypedSubscriber {
public:
    
    virtual ~TypedSubscriber() { }
    
    virtual auto onNext(_Ty _tyValue) -> void = 0;
    virtual auto subscribe(std::function<void(_Ty)> _pFunc) -> ObservableDisposer;
    virtual auto observeOnNextValue(std::function<void(_Ty)> _pFunc) -> void;
    
protected:
    
    std::vector<std::function<void(_Ty &)>> m_vSubscribersOnNext;
    std::vector<std::function<void(_Ty)>> m_vOnNextValueObservers;
    std::vector<RetainedPtr<TypedSubscriber<_Ty>>> m_vTypedChildren;
    bool m_bSubscribed = false;
};

#endif /* jrx_subscriber_hpp */

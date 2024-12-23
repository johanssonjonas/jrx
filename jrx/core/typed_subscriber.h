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
    template<class _Func> using func_t = std::function<_Func>;
        
    virtual ~TypedSubscriber() { }
    
    virtual auto onNext(_Ty _tyValue) -> void = 0; // TODO: should be pure virtual and implemented in PublishedSubject/BehaviourSubject
    virtual auto subscribe(std::function<void(_Ty)> _pFunc) -> ObservableDisposer;
    virtual auto observeOnNextValue(std::function<void(_Ty)> _pFunc) -> void;
    
protected:
    
    std::vector<func_t<void(_Ty &)>> m_vSubscribersOnNext;
    std::vector<std::function<void(_Ty)>> m_vOnNextValueObservers;
    std::vector<RetainedPtr<TypedSubscriber<_Ty>>> m_vTypedChildren;

    bool _bSubscribed = false;
};

#endif /* jrx_subscriber_hpp */

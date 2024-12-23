//
//  jrx_untyped_subscriber.hpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jrx_untyped_subscriber_h
#define jrx_untyped_subscriber_h




class jrx::core::UntypedSubscriber : public jrx::core::RetainedObject {
public:
    
    template<typename T, typename Y>
    friend class PartialValueObserver;
    
    UntypedSubscriber();
    virtual ~UntypedSubscriber() { }
    
    virtual auto observeOnStart(std::function<void()> func) -> void;
    virtual auto observeOnSubscribe(std::function<void()> func) -> void;
    virtual auto observeOnNext(std::function<void()> func) -> void;
    virtual auto observeOnPreviousOrNextValue(std::function<void()> func) -> void;
    virtual auto observeOnCompleted(std::function<void()> func) -> void;
    virtual auto observeOnError(std::function<void()> func) -> void;
    
    UntypedSubscriber *m_pParent; // TODO: Make this protected
    // ObservableDisposer m_pDisposer;
    
    auto onStart() -> void;       // When first value is posted
    auto onSubscribe() -> void;   // When someone starts observing this
    auto onNextValue() -> void;   // When a value is posted
    auto onCompleted() -> void;   // When the stream is done
    auto onError() -> void;       // When there is an error
    
protected:
    
    std::vector<RetainedPtr<UntypedSubscriber>> m_vChildren;
    
    auto getRoot() -> UntypedSubscriber *;
    
private:
    std::vector<std::function<void()>> m_vStartObservers;
    std::vector<std::function<void()>> m_vSubscribeObservers;
    std::vector<std::function<void()>> m_vOnNextObservers;
    std::vector<std::function<void()>> m_vOnAnyObservers;
    std::vector<std::function<void()>> m_vCompletedObservers;
    std::vector<std::function<void()>> m_vErrorObservers;
    
    bool m_bAnyValueSent;
};



#endif /* jrx_untyped_subscriber_h */

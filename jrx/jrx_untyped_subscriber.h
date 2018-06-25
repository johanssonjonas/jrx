//
//  jrx_untyped_subscriber.hpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jrx_untyped_subscriber_h
#define jrx_untyped_subscriber_h

class jrx::core::UntypedSubscriber {
public:

    template<typename T, typename Y>
    friend class PartialValueObserver;
	
    auto start() -> void;
    auto onNextValue(std::function<void()> func) -> void;
    virtual auto onValuePosted() -> void;
    
protected:

    virtual auto onStart() -> void;

private:
    std::vector<std::function<void()>> m_vPostObservers;
};



#endif /* jrx_untyped_subscriber_h */

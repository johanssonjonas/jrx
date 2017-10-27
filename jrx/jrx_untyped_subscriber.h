//
//  jrx_untyped_subscriber.hpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jrx_untyped_subscriber_hpp
#define jrx_untyped_subscriber_hpp


class jrx::core::UntypedSubscriber {
public:

    template<typename T, typename Y>
    friend class PartialValueObserver; // every B<T> is a friend of A

    auto start() -> void {
        onStart();
    }

    auto onNextValue(std::function<void()> func) -> void {
        m_vPostObservers.push_back(func);
    }

    virtual auto onValuePosted() -> void {
        for (auto func : m_vPostObservers) {
            func();
        }
    }
    
protected:

    virtual auto onStart() -> void {

    }

private:
    std::vector<std::function<void()>> m_vPostObservers;
};



#endif /* jrx_untyped_subscriber_hpp */

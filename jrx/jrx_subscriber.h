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
class jrx::core::Subscriber {
public:

    virtual auto onNext(_Ty &value) -> void = 0;

    // should be protected:
    std::function<void(void)> m_pOnSubscribeRoot;

protected:

};





#endif /* jrx_subscriber_hpp */

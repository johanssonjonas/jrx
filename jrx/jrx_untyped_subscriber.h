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
    template<typename T>
    friend class B; // every B<T> is a friend of A

protected:

    virtual auto start() -> void {

    }


};



#endif /* jrx_untyped_subscriber_hpp */

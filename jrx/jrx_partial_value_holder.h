//
//  jrx_partial_value_holder.hpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jrx_partial_value_holder_hpp
#define jrx_partial_value_holder_hpp


template <class _Ty>
class PartialValueHolder : public UntypedSubscriber {
public:

    _Ty *m_pSharedObject;

    PartialValueHolder() {
        m_pSharedObject = nullptr;
    }
};


#endif /* jrx_partial_value_holder_hpp */

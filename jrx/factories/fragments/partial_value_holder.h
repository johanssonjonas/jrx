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
class jrx::factories::fragments::PartialValueHolder
    : public UntypedSubscriber {
public:
	
    PartialValueHolder();
        
    auto setSharedObject(_Ty *_pSharedObject) -> void;
    auto getSharedObject() -> _Ty *;
    
private:
    _Ty *m_pSharedObject;
};

#endif /* jrx_partial_value_holder_hpp */

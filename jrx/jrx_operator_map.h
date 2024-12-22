//
//  jorx_operator_map.hpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jorx_operator_map_hpp
#define jorx_operator_map_hpp

template <class _SenderType>
class jrx::operators::Map
    : public Observable<_SenderType> {
public:
    
    Map(/*std::function<_NewChildType(_SenderType &)> _pPreducate*/);

    virtual auto onNext(_SenderType value) -> void override;
    
private:
    // std::function<_NewChildType(_SenderType &)> m_pPreducate;
};


#endif /* jorx_operator_map_hpp */

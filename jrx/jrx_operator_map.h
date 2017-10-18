//
//  jorx_operator_map.hpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jorx_operator_map_hpp
#define jorx_operator_map_hpp

template <class _SenderType, class _NewChildType>
class Map : public Observable<_SenderType, _NewChildType> {
public:
    
    Map(std::function<_NewChildType(_SenderType &)> _pPreducate);
    
    auto onNext(_SenderType &value) -> void override;
    
private:
    
    std::function<_NewChildType(_SenderType &)> m_pPreducate;
};


#endif /* jorx_operator_map_hpp */

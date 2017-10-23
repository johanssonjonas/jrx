//
//  jrx_operator_do.hpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jrx_operator_do_hpp
#define jrx_operator_do_hpp

template <class _SenderType, class _NewChildType>
class jrx::operators::Do : public Observable<_SenderType, _NewChildType> {
public:

    Do(std::function<void(_SenderType &)> _pPreducate);

    auto onNext(_SenderType &value) -> void override;

private:

    std::function<void(_SenderType &)> m_pPreducate;
};


#endif /* jrx_operator_do_hpp */

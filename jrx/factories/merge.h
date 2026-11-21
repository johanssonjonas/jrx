//
//  merge.h
//  jrx
//
//  Created by Jonas Johansson on 12/26/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template<class _SenderType>
class jrx::factories::Merge
    : public jrx::subjects::ReplaySubject<_SenderType> {
public:
    
    Merge(std::initializer_list<jrx::core::ObservablePtr<_SenderType>> _lstObservables);
    Merge(std::vector<jrx::core::ObservablePtr<_SenderType>> _lstObservables);
    
    std::vector<jrx::core::ObservablePtr<_SenderType>> m_lstObservables;
};

//
//  jrx_observable_ptr.hpp
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template <class _Type>
class jrx::core::ObservablePtr
    : public std::shared_ptr<_Type> {
public:
    ObservablePtr(_Type *ptr) : std::shared_ptr<_Type>(ptr) {}
    ObservablePtr(std::shared_ptr<_Type> ptr) : std::shared_ptr<_Type>(ptr) {}
    ObservablePtr(const ObservablePtr<_Type> &ptr) : std::shared_ptr<_Type>(ptr) {}
    
    template <class T = _Type, class U = T>
        ObservablePtr<Observable<T, U>> toObservable() {
            return std::static_pointer_cast<Observable<T, U>>(*this);
        }
};

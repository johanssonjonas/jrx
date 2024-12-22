//
//  jrx_observable_ptr.hpp
//  jrx
//
//  Created by Jonas Johansson on 12/8/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//
/*
template <class _Type>
class jrx::core::ObservablePtr
    : public RetainablePointer<Observable<_Type>> {
public:
    
    ObservablePtr(_Type *ptr) : std::shared_ptr<_Type>(ptr) {}
    ObservablePtr(std::shared_ptr<_Type> ptr) : std::shared_ptr<_Type>(ptr) {}
    ObservablePtr(const ObservablePtr<_Type> &ptr) : std::shared_ptr<_Type>(ptr) {}
    
    
};*/





template <class T>
class jrx::core::RetainedPtr {
public:
    /*
    template <class NT = T, class U = T>
        ObservablePtr<Observable<NT, U>> toObservable() {
            return std::dynamic_pointer_cast<Observable<NT, U>>(*this);
        }*/
    
    // Ensure T inherits from RetainableObject
    // static_assert(std::is_base_of<RetainableObject, T>::value, "T must inherit from RetainableObject");

    RetainedPtr() {
        
    }
    
    // Make copy constructor
    RetainedPtr(const RetainedPtr<T> &ptr) {
        m_pPtr = ptr.m_pPtr;
    }
    
    explicit RetainedPtr(T *_pPtr) {
        m_pPtr = _pPtr;
    }
    
    ~RetainedPtr() {
        
    }
    
    // Overload the -> operator
    T *operator->() {
        return m_pPtr;
    }
    
    T *operator->() const {
        return m_pPtr;
    }
    
private:
    T *m_pPtr;
};

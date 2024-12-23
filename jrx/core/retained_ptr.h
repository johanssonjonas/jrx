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
        manuallyDestroyed = false;
        retain();
    }
    
    explicit RetainedPtr(T *_pPtr) {
        m_pPtr = _pPtr;
        manuallyDestroyed = false;
        retain();
    }
    
    ~RetainedPtr() {
        if (!manuallyDestroyed) {
            release();
        }
    }
    
    void destroy() {
        release();
        manuallyDestroyed = true;
        m_pPtr = nullptr;
    }
    
    // = operator
    /*
    RetainedPtr<T> &operator=(const RetainedPtr<T> &ptr) {
        if (this != &ptr) {
            m_pPtr->release();
            m_pPtr = ptr.m_pPtr;
        }
    }*/
    
    RetainedPtr<T> &operator=(const T *ptr) {
        release();
        m_pPtr = ptr;
        retain();
        manuallyDestroyed = false;
    }
    
    // Overload the -> operator
    T *operator->() {
        return m_pPtr;
    }
    
    T *operator->() const {
        return m_pPtr;
    }
    
    T *c_ptr() {
        return m_pPtr;
    }
    
private:
    
    bool manuallyDestroyed = false;
    
    void retain() {
        assert(m_pPtr != nullptr);
        
        m_pPtr->retain();
    }
    
    void release() {
        assert(m_pPtr != nullptr);
        
        if (m_pPtr->release()) {
            m_pPtr = nullptr;
        }
    }
    
    T *m_pPtr;
};

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



class jrx::core::RetainableObject {
public:
    virtual ~RetainableObject() {
        std::cout << "here";
    }
    
    RetainableObject() {
        
    }
    
    
    int counter = 0;
    
    void retain() {
        counter++;
    }
    
    bool release() {
        counter--;
        
        if (counter == 0) {
            // delete this;
            return true;
        }
        return false;
    }
    
    template <class T>
        auto getPtr() -> RetainablePointer<T> {
            return RetainablePointer<T>((T *)this);
        }
};


template <class T>
class jrx::core::RetainablePointer {
public:
    /*
    template <class NT = T, class U = T>
        ObservablePtr<Observable<NT, U>> toObservable() {
            return std::dynamic_pointer_cast<Observable<NT, U>>(*this);
        }*/
    
    // Ensure T inherits from RetainableObject
    // static_assert(std::is_base_of<RetainableObject, T>::value, "T must inherit from RetainableObject");

    RetainablePointer() {
        
    }
    
    // Make copy constructor
    RetainablePointer(const RetainablePointer<T> &ptr) {
        m_pPtr = ptr.m_pPtr;
    }
    
    explicit RetainablePointer(T *_pPtr) {
        m_pPtr = _pPtr;
    }
    
    ~RetainablePointer() {
        
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

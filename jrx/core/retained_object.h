//
//  retained_object.h
//  jrx
//
//  Created by Jonas Johansson on 12/22/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

class jrx::core
    ::RetainedObject {
public:
        
    bool tracked = false;
    
    virtual ~RetainedObject() {
        s_iObjectCount--;
        
        if (tracked) {
            std::cout << "objects: " << s_iObjectCount << "\n";
        }
    }
    
    void retain() {
        m_iCounter++;
        
        if (tracked) {
            std::cout << "retain count: " << m_iCounter << "\n";
        }
    }
    
    bool release() {
        m_iCounter--;
        
        if (tracked) {
            std::cout << "retain count: " << m_iCounter << "\n";
        }
        
        assert(m_iCounter >= 0);
        
        if (m_iCounter == 0) {
            if (jrx::config::automaticMemoryManagement) {
                delete this;
            }
            return true;
        }
        return false;
    }
    
    template <class T>
    auto getPtr() -> RetainedPtr<T> {
            return RetainedPtr<T>((T *)this);
        }
        
protected:
    
    RetainedObject() {
        s_iObjectCount++;
    }
    
private:
        
    static int s_iObjectCount;
        
    int m_iCounter = 0;
        
};

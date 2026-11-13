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
        
    static auto getAliveObjectCount() -> size_t;
        
    template <class T> auto getPtr() -> RetainedPtr<T>;
    auto retain() -> void;
    auto release() -> bool;
        
    std::string named;
    bool tracked = false;
    
protected:
    
    RetainedObject();
    
    virtual ~RetainedObject();
    
private:
        
    static size_t s_iObjectCount;
    int m_iCounter = 0;
        
};

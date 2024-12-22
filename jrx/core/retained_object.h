//
//  retained_object.h
//  jrx
//
//  Created by Jonas Johansson on 12/22/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

class jrx::core::RetainedObject {
public:
    virtual ~RetainedObject() {
        std::cout << "here";
    }
    
    RetainedObject() {
        
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
    auto getPtr() -> RetainedPtr<T> {
            return RetainedPtr<T>((T *)this);
        }
};

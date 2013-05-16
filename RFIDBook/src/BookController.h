//
//  BookController.h
//  RFIDBook
//
//  Created by Cameron Browning on 5/16/13.
//
//

#ifndef __RFIDBook__BookController__
#define __RFIDBook__BookController__

#include <iostream>

#include "DeviceController.h"

class BookController{
    
public:
    BookController();
    ~BookController();
    
    void setup(DeviceController * deviceController_in);
    void update();
    bool isPageLanded();
    
private:
    DeviceController * deviceController;
    bool isSetup;
    
};


#endif /* defined(__RFIDBook__BookController__) */

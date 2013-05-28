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
#include "BookView.h"
#include "DeviceController.h"

class BookController{
    
public:
    BookController();
    ~BookController();
    
    void setup(DeviceController * deviceController_in, BookView * bookView_in);
    void update();
    bool isPageLanded();
    string getReport();
    string whatSituation();
    
private:
    DeviceController * deviceController;
    BookView * bookView;
    bool isSetup;
    
};


#endif /* defined(__RFIDBook__BookController__) */

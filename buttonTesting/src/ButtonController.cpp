//
//  ButtonController.cpp
//  buttonTesting
//
//  Created by Brett Peterson on 8/6/13.
//
//

#include "ButtonController.h"


ButtonController::ButtonController(){
    
}

void ButtonController::setup(){
    
    // setup all the buttons
    TouchButton button1;
    button1.setup("seal_active.png", "seal_inactive.png", 10000, 100, 100);
    buttons.push_back(button1);
    
    // setup all the buttons
    TouchButton button2;
    button2.setup("seal_active.png", "seal_inactive.png", 5000, 300, 300);
    buttons.push_back(button2);
    
    // setup all the buttons
    TouchButton button3;
    button3.setup("seal_active.png", "seal_inactive.png", 2000, 500, 500);
    buttons.push_back(button3);
    
}

void ButtonController::update(){
    
    for (int i = 0; i < buttons.size(); i++){
        buttons.at(i).update();
    }
    
}

void ButtonController::draw(){

    for (int i = 0; i < buttons.size(); i++){
        buttons.at(i).draw();
    }
}

void ButtonController::touch(int _x, int _y){
    
    for (int i = 0; i < buttons.size(); i++){
        TouchButton tempButton = buttons.at(i);
        if (_x >= tempButton.x - padding && _x <= tempButton.x + tempButton.width + padding){
            if (_y >= tempButton.y - padding && _y <= tempButton.y + tempButton.height + padding){
                buttons.at(i).press();
            }
        }
    }
    
}
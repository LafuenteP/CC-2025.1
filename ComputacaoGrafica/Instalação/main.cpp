#include <iostream>
#include <gui.h>

using namespace std;
float px = 2.0;
float pz= 0.5;

void desenha(){
    GUI::displayInit();

    GUI::setLight(0, 0, 2, 0, true, false);
    GUI::drawOrigin(0.5);
    GUI::setColor(0.5,0.5,0.7);
    GUI::drawFloor(5, 5);
    GUI::drawSphere(px,0.5,pz,0.5);
    //px -= 0.001;


    GUI::displayEnd();
}

void teclado(unsigned char tecla, int xMouse, int yMouse){

    switch(tecla) {
        case 'a':
            px -= 0.1;
            break;
        case 'd':
            px += 0.1;
            break;
        case 'w':
            pz += 0.1;
            break;
        case 's':
            pz -= 0.1;
            break;

    }

}

int main(){
    cout << "hello world" << endl;
    GUI gui = GUI(800,600, desenha, teclado);
}
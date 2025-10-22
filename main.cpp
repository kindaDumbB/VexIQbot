/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       shane young                                               */
/*    Created:      10/8/2025, 2:43:57 PM                                     */
/*    Description:  IQ2 project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "autolib.h"
#include "mtctllib.h"
using namespace vex;
//a
// A global instance of vex::brain used for printing to the IQ2 brain screen
vex::brain       Brain;
controller ctl = controller();
// define your gloaaaaaaaaaqaaaaaaaaaaaabal instances of moators and otaaaher devices herea
auto mot = nsUMTCTL::clUPMTCTL();

// functions (for threading)
int ExitTaskButton() {
    while (true) {
        if (ctl.ButtonFDown.pressing()) {
            printf("aborted");
            Brain.playSound(soundType::wrongWay);
            Brain.programStop();
            // quit hogging the CPU 
            
        }
        task::sleep(1000);
    }
    return 0;
}
vex::thread ExitTask = vex::thread(ExitTaskButton);

void ini() {
    in.calibrate();
    while (in.isCalibrating()) {
        Brain.Screen.printAt( 2, 60, "calibrating" );
        this_thread::sleep_for(1000);
    }
}

int drive[2] = {1,7};
int main() {
    ini();//initialize the IMU and calibrate the drive
    
	
    
    while(1) {
        //printf("%d::%d::%d \n", x, y, rotation);
        Brain.Screen.printAt( 2, 30, "alive1" );
        if (ctl.ButtonEDown.pressing() ) {
            lift(-100);
            this_thread::sleep_for(100);
            claw(true);
            this_thread::sleep_for(100);
            gotopos(500,0,90);//aaaaaaaaaaa aaaaaaaaaaaaagabvjsaaaatfaaaaaaaa aaaaaaAAAAaaaaahsqrt((sxdis*xdis)+(ydis*yadis))ds
            this_thread::sleep_for(100);
            claw(false);
            this_thread::sleep_for(100);
            gotopos(500,-1000,270);
            this_thread::sleep_for(100);
        }
    
        // Allow other tasks to run
        this_thread::sleep_for(100);
        
        
    }
}



//10/12/25 looking through code to see why its turning right. i plan to sort the bin of parts tomorrow. i am scrapping autolib.h and starting over
//10/12/25 nothing happened this day
//10/10/25 finished auto. its likes to turn right. i have stuff the next couple days so i'll fix it later for now there is bad cource correction
//10/9/25 making auto
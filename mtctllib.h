/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       UpdatedMTCTL.h                                          */
/*    Author:       shane                                                     */
/*    Created:      9/3/2025, 4:25:14 PM                                      */
/*    Description:  IQ2 project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#pragma once

using namespace vex;
namespace nsUMTCTL {
    bool motorOn[12] = {false,false,false,false,false,false,false,false,false,false,false,false};
    motor motors[12] = {motor(PORT1),motor(PORT2),motor(PORT3),motor(PORT4),motor(PORT5),motor(PORT6),motor(PORT7),motor(PORT8),motor(PORT9),motor(PORT10),motor(PORT11),motor(PORT12)};
    int ports[] = {0};
    class clUPMTCTL {//OPEN CLASS
        public:
        void iniMotor() {
            //ini code if needed
        }

        void BreakGroup(int ports[], int PortAmount) {
            for (int i = 0;PortAmount > i; i++) {
                int32_t port = abs(ports[i]) - 1;
                motors[port].setBrake(brakeType::hold);
            }
        }
        void UNBreakGroup(int ports[], int PortAmount) {
            for (int i = 0;PortAmount > i; i++) {
                int32_t port = abs(ports[i]) - 1;
                //motors[port].spinFor(directionType::fwd,1,rotationUnits::deg,false);
            }
        }
        directionType dir;
        // Rename parameter to avoid shadowing local variable 'port'
        void MoveMotor(int mport, int speed = 1) {

                if (mport < 0) {
                    dir = reverse;
                }
                else {
                    dir = fwd;
                }

                int32_t port = abs(mport) - 1;
                
                motors[port].setVelocity(speed, percent);
                motors[port].spin(dir);
                motorOn[port] = true;
               
        }
        void MoveGroup(int ports[], int PortAmount, int speed = 1) {
            for (int i = 0;PortAmount > i; i++) {

                if (ports[i] < 0) {
                    dir = reverse;
                }
                else {
                    dir = fwd;
                }

                int32_t port = abs(ports[i]) - 1;
                
                motors[port].setVelocity(speed, percent);
                motors[port].spin(dir);
                motorOn[port] = true;
            }
        }
        void StopMotor(int mport1) {
                int32_t port = abs(mport1) - 1;
                if (port >= 0 && port < 12 && motorOn[port]) {
                    motors[port].stop();
                    motorOn[port] = false;
                }

        }
        void StopGroup(int ports[], int PortAmount) {
            for (int i = 0;PortAmount > i; i++) {
                // Use the motor index derived from the ports array, not from loop index 'i'
                int32_t port = abs(ports[i]) - 1;
                if (port >= 0 && port < 12 && motorOn[port]) {
                    motors[port].stop();
                    motorOn[port] = false;
                }
                
            }
        }
        
        void changeMotorCal(int port, int amount, int speed) {

            ports[0] = port;
            MoveGroup(ports,1,speed+amount);
        }
        




//MT CTL DISPLAY

    int getScreenNumber(int in) {
        int screennumber[12] = {2,4,7,10,13,15,2,4,7,10,14,16};
        return screennumber[in];
    }
    int animatehelp = 0;
    bool showMoving = false;
    brain Brain1;
    void ShowMoving() {
        if (animatehelp>2) {
            animatehelp =0;
        }   
        else {
            animatehelp++;
        }
        showMoving = true;
        auto& scrn = Brain1.Screen;
        scrn.setCursor(1, 1); scrn.print("|^ ^  ^  ^  ^ ^|"); scrn.setCursor(2, 1); scrn.print("|"); scrn.setCursor(2, 16); scrn.print("|"); scrn.setCursor(3, 1); scrn.print("|"); scrn.setCursor(3, 16); scrn.print("|"); scrn.setCursor(4, 1); scrn.print("|"); scrn.setCursor(4, 16); scrn.print("|"); scrn.setCursor(5, 1); scrn.print("|v v  v  v  v v|");
         
    }
    void UpdateMoving() {
        if (showMoving) {
        auto& scrn = Brain1.Screen;
        for (int i = 0; i < 12; ++i) {
            //printf(motorOn[i] ? ":|" : ":O");
                motor mt((int32_t)i);
                if (i<6 && mt.installed()) {
                    scrn.setCursor(2,getScreenNumber(i));
                    if (animatehelp == 1) { scrn.print(motorOn[i] ? "\\" : "O"); }
                    if (animatehelp == 2) { scrn.print(motorOn[i] ? "-" : "O"); }
                    if (animatehelp == 3) { scrn.print(motorOn[i] ? "/" : "O"); }
                    if (animatehelp == 4) { scrn.print(motorOn[i] ? "-" : "O"); }
                    
                    
                }
                else if (mt.installed()) {
                    scrn.setCursor(4,getScreenNumber(i));
                    if (animatehelp == 1) { scrn.print(motorOn[i] ? "\\" : "O"); }
                    if (animatehelp == 2) { scrn.print(motorOn[i] ? "-" : "O"); }
                    if (animatehelp == 3) { scrn.print(motorOn[i] ? "/" : "O"); }
                    if (animatehelp == 4) { scrn.print(motorOn[i] ? "-" : "O"); }
                }
                
            }
        }
    }
    };//CLOSE CLASS
}//CLOSE NAMESPACE

//autolib.h (newer)
#include "vex.h"
#include "mtctllib.h"
#include "notmine.h"
using namespace vex;
int drivet[2] = {-1, 7};

motor mt[13] {PORT1,PORT1,PORT2,PORT3,PORT4,PORT5,PORT6,PORT7,PORT8,PORT9,PORT10,PORT11,PORT12};
motor leftm = motor(PORT1, true);
motor rightm = motor(PORT7, false);
drivetrain dt = drivetrain(leftm, rightm, 320, 320, 130, distanceUnits::mm, 1.0);
inertial in;
brain br;
auto lcd = br.Screen;
auto mo = nsUMTCTL::clUPMTCTL();
int x = 0;
int y = 0;

int GetHeading() {
    return (int)in.heading();
}

int claw(bool open) {
    if (open) {
        mo.MoveMotor(9, 100);
        this_thread::sleep_for(400);
    }
    else {
        mo.MoveMotor(9, -100);
        this_thread::sleep_for(400);
    }
    mo.StopMotor(9);
    mo.BreakGroup((int[]){9},1);
    return 0;
}
void lift(int amt) {
    while (abs(amt) > 1) {
        mo.MoveMotor(8, 100);
        if (amt > 0) amt--;
        else amt++;
        this_thread::sleep_for(10);
    }
    mo.StopMotor(8);
}


void rotateto(int heading) {
    br.playSound(soundType::powerDown);
    printf("rotating to %d \n", heading);
    if (GetHeading() == (int)heading) {
        return;
    }
    else {

        while (GetHeading() != (int)heading) {
            lcd.clearLine(3);
            lcd.setCursor(3,1);
            lcd.print("%d, out of %d", GetHeading(), heading);
            if (GetHeading() - 180 == (int)heading- 180){
                printf("done");
                break;
            }
            int error = heading - GetHeading();
            // i have no clue whats happening here
            if (error > 180) error -= 360;
            if (error < -180) error += 360;
            int power = error / 1; // tune this for anti jank
            if (power > 0) {
                power += 5; // minimum power to move motor
            } else if (power < 0) {
                power -= 5; // minimum power to move motor
            }
            mo.MoveGroup(drivet,2,power);
            this_thread::sleep_for(10);
        }
        lcd.clearLine(3);
        mo.StopGroup(drivet,2);
    }
    
}
void movefwd(int dist) {
    // do something D:
    // positive is forward negative is backward
    // 1 unit is something. idk
    while (abs(dist) > 1) {
        if (dist > 0) {
            dist--;
        }
        else {
            dist++;
        }
        dt.drive(directionType::fwd, 100, velocityUnits::pct);
        this_thread::sleep_for(10);
    }
    dt.stop();
}
int xdis = 0;
int ydis = 0;
int rotationdis = 0;
void gotopos(int xcord, int ycord, int rotation) {
    //ROTATE TO PROPER GO DIRECTION
    if (xcord == x && ycord == y) {
        return;
    }
    xdis = xcord - x;
    ydis = ycord - y;
    printf("ditance to go: %d::%d \n", xdis, ydis); 
    movefwd(sqrt((xdis*xdis)+(ydis*ydis)));
    this_thread::sleep_for(100);
    rotateto(rotation);
    
}


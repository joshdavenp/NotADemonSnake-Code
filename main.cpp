/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

int rightStickYaxis=50;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void liftArm (void)
{
  ArmMotorL.spin(vex::fwd, 25, vex::pct);
  ArmMotorR.spin(vex::fwd, 25, vex::pct);
}

void lowerArm (void)
{
  ArmMotorL.spin(vex::reverse, 25, vex::pct);
  ArmMotorR.spin(vex::reverse, 25, vex::pct);
}

void armStop (void)
{
  ArmMotorL.stop(vex::brakeType::brake);
  ArmMotorR.stop(vex::brakeType::brake);
}

void armControls (void)
{
  if(Controller1.ButtonR1.pressing())
  {
    liftArm();
  }
  else if (Controller1.ButtonR2.pressing()) 
  {
    lowerArm();
  }
  else 
  {
    armStop();
  }
}

void clawOpen (void)
{
  ClawMotor.spin(vex::fwd, 25, vex::pct);
}

void clawClose (void)
{
  ClawMotor.spin(vex::reverse, 25, vex::pct);
}

void clawStop (void)
{
  ClawMotor.stop(vex::brakeType::brake);
}

void clawControls (void)
{
  if (Controller1.ButtonA.pressing())
  {
    clawOpen();
  }
  else if (Controller1.ButtonB.pressing())
  {
    clawClose();
  }
  else
  {
    clawStop();
  }
}

void driveControls (void)
{
  int turn = Controller1.Axis1.position(vex::percent);
  int forward = Controller1.Axis3.position(vex::percent);
  int sideways = Controller1.Axis4.position(vex::percent);
  int slowdown = 50;

  FrontRightMotor.spin(vex::forward, forward - sideways + turn * slowdown, vex::percent);
  FrontLeftMotor.spin(vex:: forward, forward + sideways - turn * slowdown, vex::percent);
  BackRightMotor.spin(vex:: forward, forward + sideways + turn * slowdown, vex::percent);
  BackLeftMotor.spin(vex:: forward, forward - sideways - turn * slowdown, vex::percent);
}

void forkLiftUp(void)
{
  LiftMotor.spin(vex::fwd, 25, vex::pct);
}

void forkLiftDown(void)
{
  LiftMotor.spin(vex::reverse, 25, vex::pct);
}

void forkLiftStop(void)
{
  LiftMotor.stop(vex::brakeType::brake);
}

void forkLiftControls(void)
{
  if (Controller1.ButtonL1.pressing())
  {
    forkLiftUp();
  }
  else if (Controller1.ButtonL2.pressing()) 
  {
    forkLiftDown();
  }
  else 
  {
    forkLiftStop();      
  }
}

void userControl(void) 
{
  // User control code here, inside the loop
  while (1) 
  {
    driveControls();
    armControls();
    clawControls();
    forkLiftControls();
  }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

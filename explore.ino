// Ultrasonic library
#include <NewPing.h>
// Motor Control library
#include <MotorController.h>

//Define the states of the machine
#define STOP_S 0
#define FORWARD_S 1
#define BACKWARD_S 2
#define LEFT_S 3
#define TURN_LEFT_S 4
#define RIGHT_S 5
#define TURN_RIGHT_S 6

// Ultrasonic
#define echoPin 17 // Echo Pin
#define trigPin 18 // Trigger Pin
NewPing sonar(trigPin, echoPin);
int distance;

//MOTOR CONTROLLER
#define dirBPin 13 // direction //R
#define pwmBPin 3 // speed
#define dirAPin  12 // direction //L
#define pwmAPin  11 // speed
MotorController mc(dirAPin, pwmAPin, dirBPin, pwmBPin, 1, 1);


uint8_t fsm_state = STOP_S;
int turn_cnt;

void setup(){
  Serial.begin(115200);
  // software version
  Serial.println(F("Exp 0.1"));

}

void loop(){
  //state machine
  switch (fsm_state)
  {
    case STOP_S:  //Statements to execute
      // stop motors
      mc.stopMoving();
      // check distance ahead
        distance = sonar.ping();
      // if clear - go forward
      if(distance > 1200) {
        fsm_state = FORWARD_S;
      }
      // else stay in stop
      break;
    case FORWARD_S:   //Statements to execute
      // check distance ahead
      distance = sonar.ping();
      // if clear - go forward
      if(distance > 1200) {
         mc.move(-255,-255);
      } else {  // else turn left
      fsm_state = LEFT_S;
      }
      break;
    case LEFT_S:
      // set turning time
      turn_cnt = 100;
      // go to turn left
      fsm_state = TURN_LEFT_S;
      break;
    case TURN_LEFT_S:
      // decrement turn counter
      turn_cnt--;
      // if == zero - then go forward
      if(turn_cnt <= 0) {
        fsm_state = FORWARD_S;
      }
      // else keep turning
      break;
    default:
      break;
  }

  delay(1000);              // wait for a second
}

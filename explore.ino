//Define the states of the machine
#define STOP_S 0
#define FORWARD_S 1
#define BACKWARD_S 2
#define LEFT_S 3
#define TURN_LEFT_S 4
#define RIGHT_S 5
#define TURN_RIGHT_S 6


uint8_t fsm_state = STOP_S;

void setup(){


}

void loop(){
  //state machine
  switch (fsm_state)
  {
    case STOP_S:  //Statements to execute
      // stop motors
      // check distance ahead
      // if clear - go forward
      // else stop
      fsm_state = FORWARD_S;
      break;
    case FORWARD_S:   //Statements to execute
      // check distance ahead
      // if clear - go forward
      // else turn left
      fsm_state = LEFT_S;
      break;
    case LEFT_S:
      // set turning time
      // go to turn left
      fsm_state = TURN_LEFT_S;
      break;
    case TURN_LEFT_S:
      // decrement turn counter
      // if == zero - then go forward
      // else keep turning
      fsm_state = TURN_LEFT_S;
      break;
    default:
      break;
  }

  delay(1000);              // wait for a second
}

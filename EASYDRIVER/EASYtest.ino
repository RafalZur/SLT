#define Step 22
#define Dir 24
#define MS1 26
#define MS2 28
#define Enable 30

char user_input;
int state;

void setup() {
  pinMode(Step, OUTPUT);
  pinMode(Dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(Enable, OUTPUT);
  resetPins();          // resets pins values
  Serial.begin(9600);
  Serial.println("Stepper motor test");
  Serial.println();

  Serial.println("Chose option to test:");
  
  Serial.println("1. Microstep move: 1/1 step (base), move forward");
  Serial.println("2. Microstep move: 1/1 step (base), move backward");
  Serial.println("3. Microstep move: 1/2 step");
  Serial.println("4. Microstep move: 1/4 step"); 
  Serial.println("5. Microstep move: 1/8 step");
  Serial.println("6. Move forward and backward (1/1 step)");
  Serial.println();
}

void loop() {
  while(Serial.available()){
    user_input = Serial.read();
    digitalWrite(Enable, LOW);       // Initialize steper motor EasyDriver to take commands
    if (user_input =='1') {
      StepMode_1_1();
    } 
    else if(user_input =='2') {
      StepReverse_1_1();
    } 
    else if(user_input =='3') {
      StepMode_1_2();
    } 
    else if(user_input =='4') {
      StepMode_1_4();
    } 
    else if(user_input =='5') {
      StepMode_1_8();
    } 
    else if(user_input =='6') {
      ForwardBackwardStep();
    } 
    else {
      Serial.println("Option not implemented, please choose option from 1 to 6");
    }
    resetPins();
  }
}

// Option 1: Move forward with full step (default mode)
void StepMode_1_1(){
  Serial.println("Move forward with full step (default mode)");
  digitalWrite(Dir, LOW);       // "0" logic assigned for pin DIR: rotation direction declaration (forward move)
  for(int x=1; x<200; x++)      // 200 steps forward - one revolution for typical stepper motor
  {
    digitalWrite(Step, HIGH);   // one step forward
    delay(1);
    digitalWrite(Step, LOW);    // stop before next step 
    delay(1);
  }
  Serial.println("Choose new option:");
  Serial.println();
}

// Option 2: Move backward with full step (default mode)
void StepReverse_1_1(){
  Serial.println("Move backward with full step (default mode)");
  digitalWrite(Dir, HIGH);      // "1" logic assigned for pin DIR: rotation direction declaration (backward move)
  for(int x=1; x<200; x++)      // 200 steps backward - one revolution for typical stepper motor
  {
    digitalWrite(Step, HIGH);   // one step backward
    delay(1);
    digitalWrite(Step, LOW);    // stop before next step 
    delay(1);
  }
  Serial.println("Choose new option:");
  Serial.println();
}

// Option 3: Microstep mode: (1/2 step)
void StepMode_1_2(){
  Serial.println("Microstep mode (1/2 step)");
  digitalWrite(Dir, LOW);       // "0" logic assigned for pin DIR: rotation direction declaration (forward move)
  digitalWrite(MS1, HIGH);      // MS1 = "1" declaration of step resolution mode 1/2 step
  digitalWrite(MS2, LOW);       // MS2 = "0" declaration of step resolution mode 1/2 step
  for(int x=1; x<400; x++)      // 400 steps
  {
    digitalWrite(Step, HIGH);   // one step forward
    delay(1);
    digitalWrite(Step, LOW);    // stop before next step
    delay(1);
  }
  Serial.println("Choose new option:");
  Serial.println();
}

// Option 4: Microstep mode: (1/4 step)
void StepMode_1_4(){
  Serial.println("Microstep mode (1/4 step)");
  digitalWrite(Dir, LOW);       // "0" logic assigned for pin DIR: rotation direction declaration (forward move)
  digitalWrite(MS1, LOW);       // MS1 = "0" declaration of step resolution mode 1/4 step
  digitalWrite(MS2, HIGH);      // MS2 = "1" declaration of step resolution mode 1/4 step
  for(int x=1; x<800; x++)      // 800 steps
  {
    digitalWrite(Step, HIGH);   // one step forward
    delay(1);
    digitalWrite(Step, LOW);    // stop before next step
    delay(1);
  }
  Serial.println("Choose new optio:");
  Serial.println();
}

// Option 5: Microstep mode: (1/8 step)
void StepMode_1_8(){
  Serial.println("Microstep mode (1/8 step)");
  digitalWrite(Dir, HIGH);        // "0" logic assigned for pin DIR: rotation direction declaration (forward move)
  digitalWrite(MS1, HIGH);       // MS1 = "1" declaration of step resolution mode 1/8 step
  digitalWrite(MS2, HIGH);       // MS1 = "1" declaration of step resolution mode 1/8 step
  for(int x=0; x<1600; x++)      // 1600 steps
  {
    digitalWrite(Step, HIGH);    // one step forward
    delay(1);
    digitalWrite(Step, LOW);     // stop before next step
    delay(1);
  }
  Serial.println("Choose new option:");
  Serial.println();
}

// Option 6: Move forward and return to initial postion
void ForwardBackwardStep(){
  Serial.println("Move forward and return to initial postion");
  for(int x=0; x<10; x++)
  {
    state=digitalRead(Dir);        // Read of pin DIR value
    if(state == HIGH) {            // change of value for pin DIR
      digitalWrite(Dir, LOW);
    } 
    else if(state == LOW) {
      digitalWrite(Dir, HIGH);
    }
    for(int y=0; y<200; y++) {     // 200 steps
      digitalWrite(Step, HIGH);    // one move acc. pin DIR value
      delay(1);
      digitalWrite(Step, LOW);     // stop before next step
      delay(1);
    }
  }
  Serial.println("Choose new option:");
  Serial.println();
}

// Initial setup pins value declaration, driver disabled to stop move unintentionally
void resetPins(){
  digitalWrite(Step, LOW);
  digitalWrite(Dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(Enable, HIGH);
}

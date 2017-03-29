//////////////////////////////////////////////////////
//
// Ardubot old school
// Designed by naldin
// naldin.net (at) gmail
// 01/16/2014
// v2.00 (PWM)
//
// *News 01/29/2014
// -now only one pin (7 to HIGH) for set follow line
// -added switch left and right in the corner
// -for each turn the bot turn to left and next to right
//
// *News 01/18/2014
// -added beep when robot is turning
// -added line follow function
//     for this to work it is necessary pin4 and 7 are in HIGH
// -start robot with sound
//
// *News 01/17/2014:
// -using original ultrasonic board
//
//////////////////////////////////////////////////////

//Constants
const int pin13 = 13;         //led
const int mot0_0 = 5;         //motor 0 [pin17]
const int mot0_1 = 6;         //motor 0 [pin19]
const int mot1_0 = 9;         //motor 1 [pin21]
const int mot1_1 = 10;        //motor 1 [pin23]
const int pin_ultrason = 4;   //ultrason out
const int pin_sound = 11;     //speaker [J9]
const int infrared_J1 = 3;    //infrared [pin1]
const int infrared_J5 = 12;   //infrared [pin25]
const int set_infrared = 7;   //set follow black line
const int mic = 2;            //microphone
const int leftsw = A0;        //shitch left [pin5]
const int rightsw = A1;       //switch right [pin7]

//Variables
int motpwm0_0 = 255;          //default = 255
int motpwm0_1 = 0;
int motpwm1_0 = 165;          //default = 165
int motpwm1_1 = 0;
int side = 1;                 //change side to turn

void setup() {
  //setting ports
  pinMode (pin13, OUTPUT);
  pinMode (mot0_0, OUTPUT);
  pinMode (mot0_1, OUTPUT);
  pinMode (mot1_0, OUTPUT);
  pinMode (mot1_1, OUTPUT);
  pinMode (pin_sound, OUTPUT);

  pinMode (pin_ultrason, INPUT);
  pinMode (infrared_J1, INPUT);
  pinMode (infrared_J5, INPUT);
  pinMode (mic, INPUT);
  
  //starting
  offbot();
  digitalWrite(pin13, HIGH);
  delay(5000); //delay before start for ultrasonic board steady
  digitalWrite(pin13, LOW);
}

void loop() {
  digitalWrite(pin_sound, LOW); //sound off

  //start only after sound
  if (digitalRead(mic) == HIGH){
    runbot(); //running

    //call function follow black line
    if (digitalRead(set_infrared) == HIGH){ 
      motpwm0_0 = 230; //default = 255
      motpwm1_0 = 149; //default = 165
      f_line();
    }
  }

  //turn through ultrason
  if (digitalRead(pin_ultrason) == LOW){

    //choose which side the bot will turn
    if (side == 1){
      turnbotright();
    }
    else{
      turnbotleft();
    }
  }

  //turn through left switch
  if (digitalRead(leftsw) == HIGH){
    turnbotright();
  }

  //turn through right switch
  if (digitalRead(rightsw) == HIGH){
    turnbotleft();
  }
}

// function turn on motors
void runbot(){
  analogWrite (mot0_0, motpwm0_0);
  analogWrite (mot0_1, 0);
  analogWrite (mot1_0, motpwm1_0);
  analogWrite (mot1_1, 0);
}

// function turn off motors
void offbot(){
  analogWrite (mot0_0, 0);
  analogWrite (mot0_1, 0);
  analogWrite (mot1_0, 0);
  analogWrite (mot1_1, 0);
}

// function turn left 180º
void turnbotleft(){
  offbot();
  delay(1000);
  analogWrite (mot0_0, 0);
  analogWrite (mot0_1, motpwm0_0);
  analogWrite (mot1_0, 0);
  analogWrite (mot1_1, motpwm1_0);
  beepbot(3, 400); //beep while back

  analogWrite (mot0_0, 0);
  analogWrite (mot0_1, 0);
  analogWrite (mot1_0, motpwm1_0);
  analogWrite (mot1_1, 0);
  beepbot(5, 400); //beep while turn
  side = 1;
  runbot(); //run again
}

// function turn right 180º
void turnbotright(){
  offbot();
  delay(1000);
  analogWrite (mot0_0, 0);
  analogWrite (mot0_1, motpwm0_0);
  analogWrite (mot1_0, 0);
  analogWrite (mot1_1, motpwm1_0);
  beepbot(3, 400); //beep while back

  analogWrite (mot0_0, motpwm0_0);
  analogWrite (mot0_1, 0);
  analogWrite (mot1_0, 0);
  analogWrite (mot1_1, 0);
  beepbot(5, 400); //beep while turn
  side = 0;
  runbot(); //run again
}

// function beep
void beepbot(int j, int t){
  int i = 0;
  for (i = 0; i < j; i ++){
    digitalWrite(pin_sound, HIGH);
    delay(t);
    digitalWrite(pin_sound, LOW);
    delay(t);
  }
}

//function follow black line
void f_line(){
  while(1){ //loop forever
    if (digitalRead(infrared_J1) == HIGH){
      analogWrite (mot0_0, 0);
      analogWrite (mot0_1, 0);
      analogWrite (mot1_0, motpwm1_0);
      analogWrite (mot1_1, 0);
      delay(300);
      runbot();
    }

    if (digitalRead(infrared_J5) == HIGH){
      analogWrite (mot0_0, motpwm0_0);
      analogWrite (mot0_1, 0);
      analogWrite (mot1_0, 0);
      analogWrite (mot1_1, 0);
      delay(300);
      runbot();    
    }
  }
}


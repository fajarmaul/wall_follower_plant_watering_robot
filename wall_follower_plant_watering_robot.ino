
// A =  Kiri
// B = Kanan

// A+ 9 -> PWM
// A- 10
// B+ 11 -> PWM
// B- 12

//A =  -  || B = +

//MOTOR 
//Kiri
#define IN_1 9
#define IN_2 10
//Kanan
#define IN_3 11
#define IN_4 12

#define COL_1_S0 48
#define COL_1_S1 51
#define COL_1_S2 52
#define COL_1_S3 50
#define COL_1_OUT 53

//US
#define US_KAN_BAW_TX 22
#define US_KAN_BAW_RX 24
#define US_KIRI_BAW_TX 26
#define US_KIRI_BAW_RX 28

//Buzzwer
#define BUZZ_PIN 21

//VARS
const int trig = 14;
const int echo = 15;
float dist_front_sensor;
float dist_right_low_sensor;
float dist_left_low_sensor;
int frequency = 0;
boolean turning = false;
int wallState;


void setup(){
 Serial.begin(9600);
 pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);
 pinMode(US_KAN_BAW_TX, OUTPUT);
 pinMode(US_KAN_BAW_RX, INPUT);
 pinMode(US_KIRI_BAW_TX, OUTPUT);
 pinMode(US_KIRI_BAW_RX, INPUT);
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
 pinMode(COL_1_S0, OUTPUT);
 pinMode(COL_1_S1, OUTPUT);
 pinMode(COL_1_S2, OUTPUT);
 pinMode(COL_1_S3, OUTPUT);
 pinMode(COL_1_OUT, INPUT);
 pinMode(BUZZ_PIN, OUTPUT);

 digitalWrite(COL_1_S0, HIGH);
 digitalWrite(COL_1_S1, HIGH);

 dist_front_sensor = 0;
 dist_right_low_sensor = 0;
 dist_left_low_sensor = 0;
 wallState = 0; // 1= ngadep tembok kiri, 2 Tembok kanan
}

void colorSense1(){
  //Set Red filtered photodiodes to be read
  digitalWrite(COL_1_S2, LOW);
  digitalWrite(COL_1_S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(COL_1_OUT, LOW);
//  frequency = map(frequency, 25,72,255,0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(COL_1_S2,HIGH);
  digitalWrite(COL_1_S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(COL_1_OUT, LOW);
//  frequency = map(frequency, 30,90,255,0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(COL_1_S2,LOW);
  digitalWrite(COL_1_S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(COL_1_OUT, LOW);
//  frequency = map(frequency, 25,70,255,0);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);

}

void demoOne(){
// this function will run the motors in both directions at a fixed speed
  // turn on motor A
  analogWrite(IN_1, 73); //Lower slower
  digitalWrite(IN_2, LOW);  
  
  // turn on motor B
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, 70); ////Lower slower
}
 void demoTwo(){
  // turn on motor A
  analogWrite(IN_1, 65); //Lower slower
  digitalWrite(IN_2, LOW);  
  
  // turn on motor B
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, 70); ////Lower slower
}
void stopMotor(){
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);  
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

void frontSensor(){
 
 digitalWrite(trig, LOW);
 delayMicroseconds(2);
 digitalWrite(trig, HIGH);
 delayMicroseconds(10);
 digitalWrite(trig, LOW);

 float time = pulseIn(echo, HIGH);
 float dist = ((float)time/2.0) / 29.1;
 dist_front_sensor = dist;
 Serial.print(dist_front_sensor);
 Serial.println(" cm");
 if(dist>500 or dist==0) Serial.println("Out of Range");
 else{
 Serial.print(dist);
 Serial.println(" cm");
 }
}

void rightLowSensor(){
// delay(500);
 digitalWrite(US_KAN_BAW_TX, LOW);
 delayMicroseconds(2);
 digitalWrite(US_KAN_BAW_TX, HIGH);
 delayMicroseconds(10);
 digitalWrite(US_KAN_BAW_TX, LOW); 

 float time = pulseIn(US_KAN_BAW_RX, HIGH);
 float dist = ((float)time/2.0) / 29.1;
 dist_right_low_sensor = dist;
 Serial.println("Right Low Sensor: ");
 Serial.print(dist_right_low_sensor);
 Serial.println(" cm");
 if(dist>500 or dist==0) Serial.println("RL Out of Range");
 else{
 Serial.println("RL Sensor: ");
 Serial.print(dist);
 Serial.println(" cm");
 }
}


void leftLowSensor(){
// delay(500);
 digitalWrite(US_KIRI_BAW_TX, LOW);
 delayMicroseconds(2);
 digitalWrite(US_KIRI_BAW_TX, HIGH);
 delayMicroseconds(10);
 digitalWrite(US_KIRI_BAW_TX, LOW); 

 float time = pulseIn(US_KIRI_BAW_RX, HIGH);
 float dist = ((float)time/2.0) / 29.1;
 dist_left_low_sensor = dist;
 Serial.println("Left Low Sensor: ");
 Serial.print(dist_left_low_sensor);
 Serial.println(" cm");
 if(dist>500 or dist==0) Serial.println("LL Out of Range");
 else{
 Serial.println("RL Sensor: ");
 Serial.print(dist);
 Serial.println(" cm");
 }
}

void reverse(){
  digitalWrite(IN_1, LOW); //Lower slower
  analogWrite(IN_2, 63);  

  analogWrite(IN_3, 60);
  digitalWrite(IN_4, LOW); ////Lower slower
  
  delay(2000);
}

void turnRight(){
  // turn on motor A
  analogWrite(IN_1, 73); //Lower slower
  digitalWrite(IN_2, LOW);  
  
  // turn on motor B
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, LOW); ////Lower slower

  delay(1150);
}

void loop(){
  frontSensor();
  rightLowSensor();   
  leftLowSensor();
  //colorSense1();

  if(dist_front_sensor > 20){
    //Checking Which sensor is closer to wall
    if(dist_right_low_sensor < dist_left_low_sensor){
      wallState = 2; 
      }
    else {
      wallState = 1;
      }
    //Moving logic
    if (! 13 <dist_right_low_sensor<20 ){
      demoTwo();
      }
    else if(! 13 <dist_right_low_sensor<20 )
  }
  else{
    Serial.print("!! UNSAFE !!");
    stopMotor(); 
    delay(1000);
    reverse();
    delay(500);
    turnRight();

  }
  
}

//Debugging  Purposes

//if(turning == false){
//    if(dist_front_sensor > 20 ){
//    Serial.print("!! SAFE !!");  
//    demoOne();
//  }
//  else if(dist_front_sensor > 20 && dist_right_low_sensor < 17){
//    Serial.print(" RIGHT NOT SAFE !! ");
//    demoTwo();
//  }
//  else{
//    Serial.print("!! UNSAFE !!");
//    stopMotor(); 
//    delay(1000);
//    reverse();
//    delay(500);
//    turnRight();
//  }
//
// }

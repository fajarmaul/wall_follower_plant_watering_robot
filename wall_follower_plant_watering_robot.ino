
// A =  Kiri
// B = Kanan

// A+ 9 -> PWM
// A- 10
// B+ 11 -> PWM
// B- 12

//A =  -  || B = +

//MOTOR 
//Kiri
#define IN_1 4 //9
#define IN_2 5 //10
//Kanan
#define IN_3 6 //11
#define IN_4 7 //12

#define COL_1_S0 22
#define COL_1_S1 23
#define COL_1_S2 24
#define COL_1_S3 25
#define COL_1_OUT 26

#define COL_2_S0 28
#define COL_2_S1 29
#define COL_2_S2 30
#define COL_2_S3 31
#define COL_2_OUT 32

//US
#define US_FRONT_TX 14
#define US_FRONT_RX 15

#define US_KAN_BAW_TX 52
#define US_KAN_BAW_RX 53
#define US_KIRI_BAW_TX 50
#define US_KIRI_BAW_RX 51

#define US_KANAN_BACK_TX 48
#define US_KANAN_BACK_RX 49
#define US_KIRI_BACK_TX 46
#define US_KIRI_BACK_RX 47

#define US_KIRI_ATAS_TX 38 //disconnected
#define US_KIRI_ATAS_RX 39 //disconnected 
#define US_KANAN_ATAS_TX 40 //disconnected
#define US_KANAN_ATAS_RX 41 //disconnected

//Buzzwer
#define BUZZ_PIN 6

//Relay
#define PUMP_1 8 //7 
#define PUMP_2 9 //8 


//VARS
const int trig = 14;
const int echo = 15;
float dist_front_sensor;
float dist_right_low_sensor;
float dist_left_low_sensor;
float dist_left_high_sensor;
float dist_right_high_sensor;
float dist_right_back_sensor;
float dist_left_back_sensor;

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
 pinMode(US_KIRI_ATAS_TX, OUTPUT);
 pinMode(US_KIRI_ATAS_RX, INPUT);
 pinMode(US_KANAN_ATAS_TX, OUTPUT);
 pinMode(US_KANAN_ATAS_RX, INPUT);
 pinMode(US_KANAN_BACK_TX, OUTPUT);
 pinMode(US_KANAN_BACK_RX, INPUT);
 pinMode(US_KIRI_BACK_TX, OUTPUT);
 pinMode(US_KIRI_BACK_RX, INPUT);
 //Motor Driver
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
 //Col_Left
 pinMode(COL_1_S0, OUTPUT);
 pinMode(COL_1_S1, OUTPUT);
 pinMode(COL_1_S2, OUTPUT);
 pinMode(COL_1_S3, OUTPUT);
 pinMode(COL_1_OUT, INPUT);

 //Col_right
 pinMode(COL_2_S0, OUTPUT);
 pinMode(COL_2_S1, OUTPUT);
 pinMode(COL_2_S2, OUTPUT);
 pinMode(COL_2_S3, OUTPUT);
 pinMode(COL_2_OUT, INPUT);
 
 pinMode(BUZZ_PIN, OUTPUT);
  
 pinMode(PUMP_1, OUTPUT);
 pinMode(PUMP_2, OUTPUT);

 digitalWrite(COL_1_S0, HIGH);
 digitalWrite(COL_1_S1, LOW);

 digitalWrite(COL_2_S0, HIGH);
 digitalWrite(COL_2_S1, LOW);

 dist_front_sensor = 0;
 dist_right_low_sensor = 0;
 dist_left_low_sensor = 0;
 dist_left_high_sensor = 0;
 dist_right_high_sensor = 0;
 dist_right_back_sensor = 0;
 dist_left_back_sensor = 0;
 wallState = 0; // 1= ngadep tembok kiri, 2 Tembok kanan
}

void relayOn(int digital){
    digitalWrite(digital, LOW);
  }
  
void relayOff(int digital){
    digitalWrite(digital, HIGH);
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

void colorSense2(){
  //Set Red filtered photodiodes to be read
  digitalWrite(COL_2_S2, LOW);
  digitalWrite(COL_2_S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(COL_2_OUT, LOW);
//  frequency = map(frequency, 25,72,255,0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(COL_2_S2,HIGH);
  digitalWrite(COL_2_S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(COL_2_OUT, LOW);
//  frequency = map(frequency, 30,90,255,0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(COL_2_S2,LOW);
  digitalWrite(COL_2_S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(COL_2_OUT, LOW);
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
  //Beda 3 di v1, Motor A +3
  analogWrite(IN_1, 93); //Lower slower
  digitalWrite(IN_2, LOW);  
  
  // turn on motor B
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, 90); ////Lower slower
}
 void demoTwo(){
  //Turning left if sensor value if low enough
  // turn on motor A
  analogWrite(IN_1, 65); //Lower slower
  digitalWrite(IN_2, LOW);  
  
  // turn on motor B
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, 70); ////Lower slower
}

 void demoThree(){
  //Turning Right if sensor value if low enough
  // turn on motor A
  analogWrite(IN_1, 78); //Lower slower
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
 //Debug Purposes
// Serial.print("FS: ");
// Serial.print(dist_front_sensor);
// Serial.println(" cm");
// if(dist>500 or dist==0) Serial.println("FS Out of Range");
// else{
// Serial.print(dist);
// Serial.println(" cm");
// }
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
// Serial.println("Right Low Sensor: ");
// Serial.print(dist_right_low_sensor);
// Serial.println(" cm");
// if(dist>500 or dist==0) Serial.println("RL Out of Range");
// else{
// Serial.println("RL Sensor: ");
// Serial.print(dist);
// Serial.println(" cm");
// }
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
// Serial.println("Left Low Sensor: ");
// Serial.print(dist_left_low_sensor);
// Serial.println(" cm");
// if(dist>500 or dist==0) Serial.println("LL Out of Range");
// else{
// Serial.println("LL Sensor: ");
// Serial.print(dist);
// Serial.println(" cm");
// }
}

void leftHighSensor(){
// delay(500);
 digitalWrite(US_KIRI_ATAS_TX, LOW);
 delayMicroseconds(2);
 digitalWrite(US_KIRI_ATAS_TX, HIGH);
 delayMicroseconds(10);
 digitalWrite(US_KIRI_ATAS_TX, LOW); 

 float time = pulseIn(US_KIRI_ATAS_RX, HIGH);
 float dist = ((float)time/2.0) / 29.1;
 dist_left_high_sensor = dist;
 Serial.println("Left High Sensor: ");
 Serial.print(dist_left_high_sensor);
 Serial.println(" cm");
}

void rightHighSensor(){
// delay(500);
 digitalWrite(US_KANAN_ATAS_TX, LOW);
 delayMicroseconds(2);
 digitalWrite(US_KANAN_ATAS_TX, HIGH);
 delayMicroseconds(10);
 digitalWrite(US_KANAN_ATAS_TX, LOW); 

 float time = pulseIn(US_KANAN_ATAS_RX, HIGH);
 float dist = ((float)time/2.0) / 29.1;
 dist_right_high_sensor = dist;
 Serial.println("right High Sensor: ");
 Serial.print(dist_right_high_sensor);
 Serial.println(" cm");
}

void leftBackSensor(){
// delay(500);
 digitalWrite(US_KIRI_BACK_TX, LOW);
 delayMicroseconds(2);
 digitalWrite(US_KIRI_BACK_TX, HIGH);
 delayMicroseconds(10);
 digitalWrite(US_KIRI_BACK_TX, LOW); 

 float time = pulseIn(US_KIRI_BACK_RX, HIGH);
 float dist = ((float)time/2.0) / 29.1;
 dist_left_back_sensor = dist;
 Serial.println("Left Back Sensor: ");
 Serial.print(dist_left_back_sensor);
 Serial.println(" cm");
}

void rightBackSensor(){
// delay(500);
 digitalWrite(US_KANAN_BACK_TX, LOW);
 delayMicroseconds(2);
 digitalWrite(US_KANAN_BACK_TX, HIGH);
 delayMicroseconds(10);
 digitalWrite(US_KANAN_BACK_TX, LOW); 

 float time = pulseIn(US_KANAN_BACK_RX, HIGH);
 float dist = ((float)time/2.0) / 29.1;
 dist_right_back_sensor = dist;
 Serial.println("RIGHT BACK Sensor: ");
 Serial.print(dist_right_back_sensor);
 Serial.println(" cm");
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

void siram(){
  stopMotor();
  delay(500);
  demoOne();
  delay(400);
  stopMotor();
  //do nyalain pompa
  delay(400);
  }

void greenLight(){
  
  }
void blueLight(){
  
  }
void redLight(){
  
  }

void loop(){
  //relay
//  
//  delay(1000);  
//  relayOn(PUMP_1);
//  relayOn(PUMP_2);
//  delay(1000);
  relayOff(PUMP_1);
  relayOff(PUMP_2);    
//  colorSense1();
//  frontSensor();
//  rightLowSensor();
//  rightBackSensor(); 
//  leftLowSensor();
//  leftBackSensor();
//  rightBackSensor();
  demoOne();  
//  if(dist_front_sensor > 20){
//    //Checking Which sensor is closer to wall
//    if(dist_right_low_sensor < dist_left_low_sensor){
//      wallState = 2;  //Closer to right wall
//      }
//    else {
//      wallState = 1; //Closer to left wall
//      }
//          
//    //cek di jalan
//    if(wallState = 1){
//      //cek pot
//        // -> jalanin fungsi siram, abis siram, panggil fungsi maju 1/2 second, baru loop ulang
//      int diff = dist_left_back_sensor - dist_left_low_sensor;
//      if(diff >= 5.8){        
//        siram(); //harusnya fungsi siram
//        delay(1000);
//        demoOne();
//        delay(1000);        
//        }
//      
//      //Moving logic
//      if (dist_left_low_sensor > 15 ){
//        demoTwo();
//        }
//      else if (dist_left_low_sensor < 13 ){
//        demoThree();
//        }
//      else {
//        demoOne();
//        }
//      }
//    //Wallstate = 2 == Right Wall  
//    else{
//      //do something
//      }           
//  }
//  else{
//    Serial.print("!! UNSAFE !!");
//    stopMotor(); 
//    delay(1000);
//    reverse();
//    delay(500);
//    if (wallState == 1){
//      turnRight();  
//      }
//    else if (wallState == 2){
////      turnLeft();
//      }
//    
//
//  }
  
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

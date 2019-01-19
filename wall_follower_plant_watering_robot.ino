
// A =  Kiri
// B = Kanan

// A+ 9 -> PWM
// A- 10
// B+ 11 -> PWM
// B- 12

//LEFT_LOW_SENSOR = LEFT_FRONT_SENSOR
//RIGHT_LOW_SENSOR = RIGHT_FRONT_SENSOR


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
#define BUZZ_PIN 3 //6

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

int red;
int green;
int blue;

//=======================================================================SETUP====================================================================================================
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

 red = 0;
 green = 0;
 blue = 0;

  relayOff(PUMP_1);
  relayOff(PUMP_2); 
  digitalWrite(BUZZ_PIN, HIGH);
}

//=======================================================================LOOP====================================================================================================


void loop(){
  frontSensor();
  leftLowSensor();
  leftBackSensor();
  rightLowSensor();
  rightBackSensor();
  demoOne();
  relayOff(PUMP_1);  

  if(dist_right_low_sensor < dist_left_low_sensor){
      wallState = 2;  //Closer to right wall
      }
  else{
      wallState = 1; //Closer to left wall
      }

    //Safety check
  if(dist_front_sensor < 20){
    //UNSAFE       
    Serial.println("UNSAFE");
    stopMotor();
    delay(1000);
    //mundur 2 detik
    if(wallState == 1){
      reverse();
      delay(1000);
      turnRight();
      delay(600);      
      }
    else{
      reverse();
      delay(1000);
      turnLeft();
      delay(600);      
      }
    }
   else{
    //SAFE    
    if(wallState == 1){
      Serial.println("SAFE wallstate 1");
      //Wallstate 1, tembok kiri
      float diff1 = abs(dist_left_back_sensor - dist_left_low_sensor);      
      if((diff1 >= 5.8) && (dist_left_back_sensor > dist_left_low_sensor)){
        Serial.println("diff 1 >= 5.8");
        Serial.println(diff1);
        //kalo ada perbedaan jarak yang kurang dari threshold antara depan dan belakang, ada pot, siram        
        siramKiri();                 
      }      
      else{
        Serial.println("wallstate 1 adjusting");
      //jarak masih aman, adjust route
      adjust();           
      }      
    }
   else {
    //wallstate = 2, tembok kanan
    Serial.println("else wallstate tembok kanan");
      float diff1 = abs(dist_right_back_sensor - dist_right_low_sensor);      
      if((diff1 >= 5.8) && (dist_left_back_sensor > dist_left_low_sensor)){ //(dist_left_back_sensor - dist_left_low_sensor) < 5.8 && dist_left_low_sensor < 30
      Serial.println("diff1 >= 5.8");
      //kalo ada perbedaan jarak yang kurang dari threshold antara depan dan belakang, ada pot
      siramKanan();      
      }      
      else{
        Serial.println("wallstate 2 else adjust");
      //jarak masih aman, adjust route
      adjust();           
      }
    }
  }  
  
};
  
//=======================================================================FUNCTIONS====================================================================================================

void adjust(){
  Serial.println("ADJUST\n");
  if(wallState == 1){
    //adjust di kiri
    if(dist_left_low_sensor < 10 && dist_left_back_sensor < 12){
      demoOne(77, 1);
      delay(200);
      }
    //else proceed as usual    
    }
  else{
    if(dist_right_low_sensor < 10 && dist_right_back_sensor < 12){
      demoOne(64, 2);
      delay(200);
      }
      //else proceed as usual    
    }
  }


void colorSenseKiri(){
  Serial.println("COLORSENSEKIRI\n");
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
  red = frequency;
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(COL_1_S2,HIGH);
  digitalWrite(COL_1_S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(COL_1_OUT, LOW);
  //frequency = map(frequency, 30,90,255,0);
  
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  green = frequency;
  delay(100);
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(COL_1_S2,LOW);
  digitalWrite(COL_1_S3,HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(COL_1_OUT, LOW);
  //frequency = map(frequency, 25,70,255,0);
  
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  blue = frequency;
  delay(100);

}
//
void colorSenseKanan(){
  Serial.println("COLORSENSEKANAN\n");
  //Set Red filtered photodiodes to be read
  digitalWrite(COL_2_S2, LOW);
  digitalWrite(COL_2_S3, LOW);
  
  // Reading the output frequency
  frequency = pulseIn(COL_2_OUT, LOW);
  //frequency = map(frequency, 25,72,255,0);
  
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  red = frequency;
  delay(100);
  
  // Setting Green filtered photodiodes to be read
  digitalWrite(COL_2_S2,HIGH);
  digitalWrite(COL_2_S3,HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(COL_2_OUT, LOW);
  //frequency = map(frequency, 30,90,255,0);
  
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  green = frequency;
  delay(100);
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(COL_2_S2,LOW);
  digitalWrite(COL_2_S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(COL_2_OUT, LOW);
  //frequency = map(frequency, 25,70,255,0);
  
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  blue = frequency;
  delay(100);
}

void demoOne(){
  Serial.println("DEMOONE\n");
// this function will run the motors in both directions at a fixed speed
  // turn on motor A
  //Beda 3 di v1, Motor A +3
  analogWrite(IN_1, 76); //Lower slower
  digitalWrite(IN_2, LOW);  
  
  // turn on motor B
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, 60); ////Lower slower
}

void demoOne(int val, int key){
//Key, 1 = kiri, 2 = kanan;
  Serial.println("DEMOONEwParams\n");
// this function will run the motors in both directions at a fixed speed
  // turn on motor A
  //Beda 3 di v1, Motor A +3
  if(key == 1 ){
    analogWrite(IN_1, val); //Lower slower
    digitalWrite(IN_2, LOW);  
    
    // turn on motor B
    digitalWrite(IN_3, LOW);
    analogWrite(IN_4, 60); ////Lower slower  
    }
  else{
    analogWrite(IN_1, 76); //Lower slower
    digitalWrite(IN_2, LOW);  
    
    // turn on motor B
    digitalWrite(IN_3, LOW);
    analogWrite(IN_4, 66); ////Lower slower  
    }  
}

void stopMotor(){
  Serial.println("STOPMOTOR\n");
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);  
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

void frontSensor(){ 
 digitalWrite(US_FRONT_TX, LOW);
 delayMicroseconds(2);
 digitalWrite(US_FRONT_TX, HIGH);
 delayMicroseconds(10);
 digitalWrite(US_FRONT_TX, LOW);

 float time = pulseIn(US_FRONT_RX, HIGH);
 float dist = ((float)time/2.0) / 29.1;
 dist_front_sensor = dist;
// Debug Purposes
// Serial.print("FS: ");
// Serial.print(dist_front_sensor);
// Serial.println(" cm");
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
 //Debugging purposes
// Serial.println("Right Low Sensor: ");
// Serial.print(dist_right_low_sensor);
// Serial.println(" cm");
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
 //Debugging purposes
// Serial.println("Left Low Sensor: ");
// Serial.print(dist_left_low_sensor);
// Serial.println(" cm");
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
 //Debugging purposes
// Serial.println("Left Back Sensor: ");
// Serial.print(dist_left_back_sensor);
// Serial.println(" cm");
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
 //Debugging purposes
// Serial.println("RIGHT BACK Sensor: ");
// Serial.print(dist_right_back_sensor);
// Serial.println(" cm");
}

void reverse(){
  Serial.println("REVERSE\n");
  digitalWrite(IN_1, LOW); //Lower slower
  analogWrite(IN_2, 76);  //prev 63

  analogWrite(IN_3, 60); //prev 60
  digitalWrite(IN_4, LOW); ////Lower slower   
}

void turnRight(){
  Serial.println("TURNRIGHT\n");
  // turn on motor A
  analogWrite(IN_1, 93); //Lower slower
  digitalWrite(IN_2, LOW);  
  
  // turn on motor B
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, LOW); ////Lower slower

  delay(700);
}

void turnLeft(){
  Serial.println("TURNLEFT\n");
   // turn on motor A
  analogWrite(IN_1, LOW); //Lower slower
  digitalWrite(IN_2, LOW);  
  
  // turn on motor B
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, 89); ////Lower slower

  delay(700);
  }
void siramKanan(){
  Serial.println("SIRAMKANAN\n");
  stopMotor();
  buzzOn(100);
  delay(1000);
  demoOne();
  delay(500);  
  stopMotor();
  //deteksi warna
  colorSenseKanan();
  Serial.print("R: ");
  Serial.print(red);
  Serial.print("G: ");
  Serial.print(green);
  Serial.print("B: ");
  Serial.print(blue);
  //do nyalain pompa
  //cek warna
  if(red < blue && red < green){
    buzzRed();
    Serial.println("RED COLOR");
    relayOn(PUMP_1);
    delay(2000);
    relayOff(PUMP_1);  
    }
  else if(blue < red && blue < green){
    buzzBlue();
    Serial.println("BLUE COLOR");
    relayOn(PUMP_1);
    delay(3000);
    relayOff(PUMP_1);  
    }
  else{
    buzzGreen();
    Serial.println("RED COLOR");
    relayOn(PUMP_1);
    delay(4000);
    relayOff(PUMP_1);  
    }
  demoOne();
  delay(700);
  }
void siramKiri(){
  Serial.println("SIRAMKIRI\n");
  stopMotor();
  buzzOn(100);
  delay(1000);
  demoOne();
  delay(500);  
  stopMotor();
  //deteksi warna
  colorSenseKiri();
  Serial.print("R: ");
  Serial.print(red);
  Serial.print("G: ");
  Serial.print(green);
  Serial.print("B: ");
  Serial.print(blue);
  //do nyalain pompa
  //cek warna
  if(red < blue && red < green){
    //red
    buzzRed();
    Serial.println("RED COLOR");
    relayOn(PUMP_1);
    delay(4000);
    relayOff(PUMP_1);  
    }
  else if(blue < red && blue < green){
    //blue
    buzzBlue();
    Serial.println("BLUE COLOR");
    relayOn(PUMP_1);
    delay(5000);
    relayOff(PUMP_1);  
    }
  else{
    //green
    buzzGreen();
    Serial.println("GREEN COLOR");
    relayOn(PUMP_1);
    delay(6000);
    relayOff(PUMP_1);  
    }
  demoOne();
  delay(700);
  }

void buzzOn(int val){
  Serial.println("BUZZON\n");
  digitalWrite(BUZZ_PIN, LOW);
  delay(val);
  digitalWrite(BUZZ_PIN, HIGH);
  }

void buzzRed(){
  Serial.println("BUZZRED\n");
  //1 kali ngebuzz
  digitalWrite(BUZZ_PIN, LOW);
  delay(300);
  digitalWrite(BUZZ_PIN, HIGH);
  }

void buzzBlue(){
  Serial.println("BUZZBLUE\n");
  //2 kali ngebuzz
  digitalWrite(BUZZ_PIN, LOW);
  delay(300);
  digitalWrite(BUZZ_PIN, HIGH);
  delay(600);
  digitalWrite(BUZZ_PIN, LOW);
  delay(300);
  digitalWrite(BUZZ_PIN, HIGH);
  }

void buzzGreen(){
  Serial.println("BUZZGREEN\n");
  //3 kali ngebuzz
  digitalWrite(BUZZ_PIN, LOW);
  delay(300);
  digitalWrite(BUZZ_PIN, HIGH);
  delay(600);
  digitalWrite(BUZZ_PIN, LOW);
  delay(300);
  digitalWrite(BUZZ_PIN, HIGH);
  delay(600);
  digitalWrite(BUZZ_PIN, LOW);
  delay(300);
  digitalWrite(BUZZ_PIN, HIGH);
  }

void relayOn(int digital){
    Serial.println("RELAY ON\n");
    digitalWrite(digital, LOW);
  }
//  
void relayOff(int digital){
    Serial.println("RELAY OFF\n");
    digitalWrite(digital, HIGH);
  }

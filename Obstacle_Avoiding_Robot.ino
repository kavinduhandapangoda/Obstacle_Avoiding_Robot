/*
  Thingerbits Smart Robot kit
  Sample code 1
  Obstacle Avoiding Robot
  Visit www.Thingerbits.lk for more details about kits and training programmes
*/


#include <Servo.h>   // servo library including
Servo servo1;

#define trig 2      //  intialinzing trig pin
#define echo 10     //  intialinzing echo pin
#define Speed 100  

//-------------------------------------- L293 pinout----------------------------------------------------------------------------------------------------------------- 
#define motorA1 3 
#define motorA2 4 
#define motorB1 7
#define motorB2 8
   
#define servopin  11  // servo pin

long distance;
long distance_right;
long distance_left;
 
//----------------------------------------- Servo position variables---------------------------------------------------------------------------------------------------------

int center = 70;
int right = 0;
int left  = 140; 

//----------------------------------------- Program will begin here---------------------------------------------------------------------------------------------------------

void setup() {
     Serial.begin(9600);
  
     servo1.attach(servopin);
     pinMode(trig, OUTPUT);
     pinMode(echo, INPUT);
  
     pinMode(motorA1, OUTPUT);
     pinMode(motorA2, OUTPUT);
     pinMode(motorB1, OUTPUT);
     pinMode(motorB2, OUTPUT);

}

void loop() {
     servo1.write(center);                // checking barriers
     delay(100);
     
     forward();                       // car is running forward
     distance = sensor_read();
      if (distance > 35){                        // checking distances
        forward();                         // if the distance is large than 35 allow car to run forward
      }
        
          
     if (distance < 15){
          backward();                        // if the distance is lower than 15, run backward and stop the car 
          delay(500);
          Stop();                              
                                         //Measure right distance
          servo1.write(right);
          delay(1000);
          distance_right = sensor_read();
          servo1.write(left);
          distance_left = sensor_read();                                        //Measure left distance     
          delay(1000);
       
          servo1.write(center);
    
          if (distance_right > 70 ){                     // checking right distance
             Tright();
             delay(200);                                      //turning car right
          }
          else if(distance_left > 70){
            Tleft();                         // checking left distance
            delay(200);                                    //turning car right
            }
     }
}

 //----------------------------------------turtle moving functions--------------------------------------------------------------------------------------------------                  
long sensor_read(){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long l=pulseIn(echo, HIGH);
    long cm3 = (l/2)/29.1;

    return cm3;
}
void backward(){
   analogWrite (motorA1,0);
   analogWrite (motorA2,Speed);                       
   analogWrite (motorB1,0);
   analogWrite (motorB2,Speed);

   }

  void forward(){
   analogWrite (motorA1,Speed);
   analogWrite (motorA2,0);                       
   analogWrite (motorB1,Speed);
   analogWrite (motorB2,0);

  }

void Tleft(){
   analogWrite (motorA1,Speed);
   analogWrite (motorA2,0);                       
   analogWrite (motorB1,0);
   analogWrite (motorB2,Speed);

   }  

  void Tright(){
   analogWrite (motorA1,0);
   analogWrite (motorA2,Speed);                       
   analogWrite (motorB1,Speed);
   analogWrite (motorB2,0);

  }

  void Stop(){
    analogWrite (motorA1,0);
    analogWrite (motorA2,0);                       
    analogWrite (motorB1,0);
    analogWrite (motorB2,0);
    }

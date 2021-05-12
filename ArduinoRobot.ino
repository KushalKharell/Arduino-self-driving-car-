#include <Servo.h>

//-----------------------------------------Pins for motor----------------------------------------------------

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define CAR_SPEED 100
typedef unsigned char u8;  //Change the name of unsigned char to u8


//--------------------------------------Motor Functions seciton ----------------------------------------------------
void forward(int16_t car_speed)
{

  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void back(int16_t car_speed)
{

  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void left(int16_t car_speed) //could be switched with right turn function 
{

  analogWrite(ENA, car_speed/1.5);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void right(int16_t car_speed)
{
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed/1.5);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}




void stop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------Variables section---------------------------------------------------------------------------

const int trigPin = A5;
const int echoPin = A4;
Servo myservo; //initilizing the servo motor

long duration;
int distance;

long duration_left; //holds the distance fired to left side
int distance_left; 

long duration_right; //holds the distance fired to right side
int distance_right;

int distance_turn; //value to turn right or left. (if 1 = turn right, if 0 = turn left. if 2 = reverse.)



//----------------------------------------------------set up section---------------------------------------------------------------------

void setup() {

//initilizing the ultrasonic sensor
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); 

//for servo
 
myservo.attach(3);//servo goes in pin 3
myservo.write(100); //it's little tiled to had to use 93 deg
delay(1000);

//for motors
  pinMode(IN1,OUTPUT); 
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}




//-----------------------------------------------------------------actual loop section----------------------------------------------------


void loop() {
 

       
          

    digitalWrite(trigPin, LOW); //this will clear the trig 
    delayMicroseconds(2);
    //generating the ultra sound wave
    digitalWrite(trigPin, HIGH); //put the trig pin in high for 10 micro seconds 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW); //low after 10 micro seconds
    duration = pulseIn(echoPin, HIGH); //reading the ultra sound wave travel time
    distance= duration*0.034/2; //calculating the distance 


    //turn the wheels on, go forward
    
    if(distance <= 20)
    {  //if it's closer than 20 cm it turns                               

          //break , stop the motors and access the situation first
          stop();
          myservo.write(0);//turns to the right
          delay(1000); 

    //Checks left side for obstacle
          digitalWrite(trigPin, LOW); //this will clear the trig 
          delayMicroseconds(2);
          //generating the ultra sound wave
          digitalWrite(trigPin, HIGH); //put the trig pin in high for 10 micro seconds 
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW); //low after 10 micro seconds
          duration_right = pulseIn(echoPin, HIGH); //reading the ultra sound wave travel time
          distance_right = duration_right*0.034/2; //calculating the distance 
          
          myservo.write(100);//returns to middle position
          delay(1000);
          myservo.write(180);
          delay(1000);
          
    //Checks left side for obstacle      
          digitalWrite(trigPin, LOW); //this will clear the trig 
          delayMicroseconds(2);
          //generating the ultra sound wave
          digitalWrite(trigPin, HIGH); //put the trig pin in high for 10 micro seconds 
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW); //low after 10 micro seconds
          duration_left = pulseIn(echoPin, HIGH); //reading the ultra sound wave travel time
          distance_left = duration_left*0.034/2; //calculating the distance 
          
          myservo.write(100);//returns to middle position
          delay(1000);

          if(distance_right < 30 && distance_left <30)
          {
            back(CAR_SPEED);
            delay(1750);
            right(107);
            delay(1750);
            loop();
          }

         else if(distance_right > distance_left)
          {
            right(107);
            delay(1750);
            loop();
          }
          else if(distance_left > distance_right)
          {
            left(107);
            delay(1750);
            loop();
          }
          else if(distance_right==distance_left)
          {
            right(107);
            delay(1750);
            loop();
          }
         else{

            back(CAR_SPEED);
            loop();
            }
          
   }
    
   else 
   {
    forward(CAR_SPEED);
    loop();
   }

        
}
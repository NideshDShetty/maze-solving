#include <StackArray.h>

#define leftFarSensor A0 //s1
#define leftNearSensor A1 //s2
#define leftfollowsensor A2//s3  
#define leftCenterSensor  A3 //s4    
#define rightCenterSensor A4 // s5
#define rightfollowsensor A5//s6
#define rightNearSensor   2 //s7
#define rightFarSensor   4 //s8

#define leftMotor1  8
#define leftMotor2  9
#define rightMotor1 7
#define rightMotor2 6

StackArray <int> s;
int prev_vx = 0,prev_vy = 1,prev_x,prev_y,curr_x,curr_y,curr_vx,curr_vy,a;



 //change prev_vx and prev_vy according to the direction




void setup() {
  // put your setup code here, to run once:

   pinMode(leftCenterSensor, INPUT);
  pinMode(leftNearSensor, INPUT);
  pinMode(leftFarSensor, INPUT);
  pinMode(rightCenterSensor, INPUT);
  pinMode(rightNearSensor, INPUT);
  pinMode(rightFarSensor, INPUT);
  pinMode(leftfollowsensor,INPUT);
    pinMode(rightfollowsensor,INPUT);  
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  Serial.begin(9600);
   s.setPrinter (Serial);
 
  
    s.push(30);
     s.push(20);
      s.push(21);
       s.push(31);
        s.push(32);
         s.push(22);
          s.push(12);

     s.push(11);
         s.push(10);
         s.push(00);
   a= s.pop();
   prev_x = a/100;
   prev_y = a%100;
  //Serial.println(s.pop());
}

void loop() {

   while(digitalRead(leftFarSensor) == HIGH /*&& digitalRead(leftNearSensor) == HIGH */ && digitalRead(rightFarSensor) == HIGH )  
      {
        straight();       
      }
 /*  if(digitalRead(leftFarSensor) != HIGH || digitalRead(leftNearSensor) != HIGH  ||  digitalRead(rightFarSensor) != HIGH) 
   {
    if( digitalRead(leftFarSensor) != HIGH || digitalRead(leftNearSensor) != HIGH || digitalRead(leftfollowsensor) != HIGH || digitalRead(leftCenterSensor) != HIGH)
    {
      while(digitalRead(rightCenterSensor)==HIGH)
     {
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);
      digitalWrite(rightMotor1,HIGH);
      digitalWrite(rightMotor2, LOW);
     }
    } 
    if(digitalRead(rightFarSensor) != HIGH || digitalRead(rightNearSensor) != HIGH || digitalRead(rightfollowsensor) != HIGH || digitalRead(rightCenterSensor) != HIGH)
    {
      while(digitalRead(leftCenterSensor)==HIGH)
      {
       digitalWrite(leftMotor1,  HIGH);
       digitalWrite(leftMotor2, LOW);
       digitalWrite(rightMotor1,LOW);
       digitalWrite(rightMotor2,  HIGH);
      } 
    }*/
   
    path_tracing(); 
    Serial.println("path tracing");
   

   while(digitalRead(leftFarSensor) == HIGH /*&& digitalRead(leftNearSensor) == HIGH*/  && digitalRead(rightFarSensor) == HIGH )  
      {
        straight();       
      }
      
   while(s.isEmpty())
   {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1,LOW);
    digitalWrite(rightMotor2, LOW);
    Serial.println("empty");
   }
}






int path_tracing()
{
  if(!s.isEmpty ())
  {Serial.println("stack not empty");
    a = s.pop();
    curr_x = a/100;
    curr_y = a%100;
    curr_vx = curr_x - prev_x;
    curr_vy = curr_y - prev_y;

    if(prev_vx == curr_vx && prev_vy == curr_vy)
    {
      /*Serial.println("no change in direction");
      while(digitalRead(leftFarSensor) == HIGH && digitalRead(leftNearSensor) == HIGH  && digitalRead(rightFarSensor) == HIGH )  
      {
       Serial.println("path tracing straight");
        straight();       
      }*/
      Serial.println("extrainch");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(300);
    }

    if(prev_vx != curr_vx || prev_vy != curr_vy)
    {
       Serial.println("turn mode");
      if(prev_vx > 0 && prev_vy == 0)
      {Serial.println("turn1");
        if(curr_vx == 0 && curr_vy > 0)
        { Serial.println("left1");
          turnLeft();
        }
        if(curr_vx == 0 && curr_vy < 0)
        { Serial.println("right1");
          turnRight();
        }
      }

       if(prev_vx == 0 && prev_vy > 0)
      {Serial.println("turn2");
      Serial.println(curr_vx);
      Serial.println(curr_vy);
        if(curr_vx > 0 && curr_vy == 0)
        {Serial.println("right2");
          turnRight();
        }
        if(curr_vx < 0 && curr_vy == 0)
        {Serial.println("left2");
          turnLeft();
        }
      }

        
       if(prev_vx < 0 && prev_vy == 0)
       {Serial.println("turn3");
        if(curr_vx == 0 && curr_vy > 0)
        {Serial.println("right3");
          turnRight();
        }
        if(curr_vx == 0 && curr_vy < 0)
        {Serial.println("left3");
          turnLeft();
        }
       }

        if(prev_vx == 0 && prev_vy < 0)
      {Serial.println("turn4");
        if(curr_vx > 0 && curr_vy == 0)
        {Serial.println("left4");
          turnLeft();
        }
        if(curr_vx < 0 && curr_vy == 0)
        {Serial.println("right4");
          turnRight();
        }

      }
     
    } 
      prev_x = curr_x;
      prev_y = curr_y;
      prev_vx = curr_vx;
      prev_vy = curr_vy;
     // Serial.println(prev_x);
     // Serial.println(prev_y);
  }
   return 0;  
}



void turnLeft()
{
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(300);

    
  Serial.println("left main");
  while(digitalRead(rightCenterSensor)!=HIGH || digitalRead(leftCenterSensor)!=HIGH)//black||black
  {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
   delay(10);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(10);
  
  }
  while(digitalRead(rightCenterSensor)==HIGH)//white
  {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
   delay(10);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(10);
  }
  while(digitalRead(rightfollowsensor)==HIGH)//white
  {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
   delay(10);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(10);
  }
 /* if(replaystage==0)
  {
    path[pathLength]='L';
    Serial.println("l");
    pathLength++;
    //Serial.print("Path length: ");
    //Serial.println(pathLength);
      if(path[pathLength-2]=='B')
      {
        Serial.println("shortening path");
        shortPath();
      }
  }*/
}

void turnRight()
{ 
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(300);


    
  Serial.println("right major");
  while(digitalRead(rightCenterSensor)!=HIGH || digitalRead(leftCenterSensor)!=HIGH)//black||black

  {
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(5);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(5);
  }
   while(digitalRead(leftCenterSensor)==HIGH)// && digitalRead(rightCenterSensor)==HIGH)//white
   {
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(5);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(5);
  }
   /*while(digitalRead(leftCenterSensor)==HIGH)//white
   {
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }*/
  
  /*if(replaystage==0){
  path[pathLength]='R';
  Serial.println("r");
  pathLength++;
 // Serial.print("Path length: ");
  //Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
      Serial.println("shortening path");
      shortPath();
    }
  }*/
 
}

void straight()
{  Serial.println("straight main");
   if ((digitalRead(leftNearSensor))==HIGH && !(digitalRead(leftfollowsensor))==HIGH &&  !(digitalRead(leftCenterSensor))==HIGH && !(digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//100001Straight
 {
     digitalWrite( rightMotor1,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,HIGH);
      digitalWrite(leftMotor2,LOW);
      delay(20);
       digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,LOW);
      digitalWrite(leftMotor2,LOW);
      delay(5); 
 }
 else if ((digitalRead(leftNearSensor))==HIGH && (digitalRead(leftfollowsensor))==HIGH &&  !(digitalRead(leftCenterSensor))==HIGH && !(digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//110001Straight
 {
       digitalWrite( rightMotor1,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,HIGH);
      digitalWrite(leftMotor2,LOW);
      delay(20);
       digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,LOW);
      digitalWrite(leftMotor2,LOW);
      delay(5);
 }
 else if ((digitalRead(leftNearSensor))==HIGH && (digitalRead(leftfollowsensor))==HIGH &&  !(digitalRead(leftCenterSensor))==HIGH && !(digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && !(digitalRead(rightNearSensor))==HIGH)//100000SL1
 {
      digitalWrite( rightMotor1 ,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW); 
 }
 else if ((digitalRead(leftNearSensor))==HIGH && !(digitalRead(leftfollowsensor))==HIGH &&  !(digitalRead(leftCenterSensor))==HIGH && !(digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//100011Straight
 {
       digitalWrite( rightMotor1,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,HIGH);
      digitalWrite(leftMotor2,LOW);
      delay(20);
       digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,LOW);
      digitalWrite(leftMotor2,LOW);
      delay(5); 
 }
 else if (!(digitalRead(leftNearSensor))==HIGH && !(digitalRead(leftfollowsensor))==HIGH &&  !(digitalRead(leftCenterSensor))==HIGH && !(digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//000011SR1
 {
      digitalWrite( rightMotor1 ,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW); 
 }
 else if (!(digitalRead(leftNearSensor))==HIGH && !(digitalRead(leftfollowsensor))==HIGH &&  !(digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//000111SR2
 {
      digitalWrite( rightMotor1 ,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW); 
 }
 else if ((digitalRead(leftNearSensor))==HIGH && (digitalRead(leftfollowsensor))==HIGH &&  (digitalRead(leftCenterSensor))==HIGH && !(digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && !(digitalRead(rightNearSensor))==HIGH)//111000SL2
 {
      digitalWrite( rightMotor1 ,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW); 
 }
 else if (!(digitalRead(leftNearSensor))==HIGH && !(digitalRead(leftfollowsensor))==HIGH &&  (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//001111SR3
 {
      digitalWrite( rightMotor1 ,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW); 
 }
 else if ((digitalRead(leftNearSensor))==HIGH && (digitalRead(leftfollowsensor))==HIGH &&  (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && !(digitalRead(rightNearSensor))==HIGH)//111100SL3
 {
      digitalWrite( rightMotor1 ,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW); 
 }
 else if (!(digitalRead(leftNearSensor))==HIGH && (digitalRead(leftfollowsensor))==HIGH &&  (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//011111HR
 {
      digitalWrite( rightMotor1 ,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,HIGH); 
 }
 else if ((digitalRead(leftNearSensor))==HIGH && (digitalRead(leftfollowsensor))==HIGH &&  (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && !(digitalRead(rightNearSensor))==HIGH)//111110HL
 {
      digitalWrite( rightMotor1 ,LOW);
      digitalWrite( rightMotor2,HIGH);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW); 
 }
 /*else if ((!(digitalRead(leftNearSensor))==HIGH || !(digitalRead(leftfollowsensor))==HIGH ||  !(digitalRead(leftCenterSensor))==HIGH) &&  (digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SL 
 {
      digitalWrite( rightMotor1 ,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW); 
 }
  else if ((digitalRead(leftNearSensor))==HIGH && (digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH && ( !(digitalRead(rightCenterSensor))==HIGH || !(digitalRead( rightfollowsensor))==HIGH || !(digitalRead(rightNearSensor))==HIGH))//SR
 {
      digitalWrite( rightMotor1 ,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW); 
 }
 */
     
else  
{ 
   return;
      
}
}



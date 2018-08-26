#define leftMotor1  8
#define leftMotor2  9
#define rightMotor1 7
#define rightMotor2 6

#define leftFarSensor A0 //s1
#define leftNearSensor A1 //s2
#define leftfollowsensor A2//s3  
#define leftCenterSensor  A3 //s4    
#define rightCenterSensor A4 // s5
#define rightfollowsensor A5//s6
#define rightNearSensor   2 //s7
#define rightFarSensor   4 //s8

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
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

}

void loop() {
  // put your main code here, to run repeatedly:
   straight(); 
}
void straight()
{  
  Serial.println("straight main");
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

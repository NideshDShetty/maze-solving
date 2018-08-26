#define leftFarSensor A0 //s1
#define leftNearSensor A1 //s2
#define leftfollowsensor A2//s3  
#define leftCenterSensor  A3 //s4    
#define rightCenterSensor A4 // s5
#define rightfollowsensor A5//s6
#define rightNearSensor   2 //s7
#define rightFarSensor   4 //s8


int leftCenterReading;
int leftNearReading;
int leftFarReading;
int rightCenterReading;
int rightNearReading;
int rightFarReading;
int leftfollowreading;
int rightfollowreading;

int replaystage;


#define leapTime 100

#define leftMotor1  8
#define leftMotor2  9
#define rightMotor1 7
#define rightMotor2 6

#define led 13

char path[30] = {};
int pathLength;
int readLength;

void setup(){
  
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
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  digitalWrite(led, HIGH);
  delay(1000);
}


void loop(){
  
 readSensors();                                                                                     
 
 if(leftFarReading==HIGH && rightFarReading==HIGH && 
   (leftCenterReading!=HIGH|| rightCenterReading!=HIGH|| leftfollowreading!=HIGH|| rightfollowreading!=HIGH|| leftNearReading!=HIGH|| rightNearReading!=HIGH) )
   {
    Serial.println("straight000"); 
    straight(); 
   }
  else
  {  
    Serial.println("lefthand000");                                                                                            
   leftHandWall(); 
 }

}

void readSensors(){
  
  leftCenterReading  = digitalRead(leftCenterSensor);
  leftNearReading    = digitalRead(leftNearSensor);
  leftFarReading     = digitalRead(leftFarSensor);
  rightCenterReading = digitalRead(rightCenterSensor);
  rightNearReading   = digitalRead(rightNearSensor);
  rightFarReading    = digitalRead(rightFarSensor);
  rightfollowreading =digitalRead(rightfollowsensor);
  leftfollowreading =digitalRead(leftfollowsensor);
    

// serial printing below for debugging purposes
/*
Serial.println(leftFarReading);
Serial.println(leftNearReading);
Serial.println(leftCenterReading);
Serial.println(rightCenterReading);
Serial.println(rightNearReading);
Serial.println(rightFarReading);
Serial.println(leftfollowreading);
Serial.println(rightfollowreading);
//delay(200);
 */ 

}


void leftHandWall()
{
  if( leftFarReading!=HIGH && rightFarReading!=HIGH)//black&&black
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
     delay(leapTime);
     Serial.println("extra inch1");
     readSensors();
    
    if(leftFarReading!=HIGH || rightFarReading!=HIGH)//black||black
    {
      Serial.println("done1");
      done();
    
      
    }
    if(leftFarReading==HIGH && rightFarReading==HIGH)//white||white
    { 
      Serial.println("left1");
      turnLeft();
    }
    
  }
  
  if(leftFarReading!=HIGH) //black if you can turn left then turn left
    {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    Serial.println("extra inch2");
    readSensors();
      
      if(leftFarReading==HIGH && rightFarReading==HIGH)//white&&white
      { Serial.println("left2");
        turnLeft();
      }
      else
      { Serial.println("done2");
        done();
      }
  }
   
  if(rightFarReading!=HIGH)//black 
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    Serial.println("extra inch3");
    readSensors();
    
    if(leftFarReading!=HIGH)//black
    {
      delay(leapTime);
      readSensors();
      
      if(rightFarReading!=HIGH&& leftFarReading!=HIGH)//black&&black
      { Serial.println("done3");
        done();
      }
      else
      { Serial.println("left3");
        turnLeft();
        return;
      }
    }
    delay(leapTime);
    readSensors();
    if(leftFarReading==HIGH && leftCenterReading==HIGH &&
      rightCenterReading==HIGH && rightFarReading==HIGH)
      { Serial.println("right1");
      turnRight();
      return;
    }
    path[pathLength]='S';
    Serial.println("s");
    pathLength++;
   // Serial.print("Path length: ");
   // Serial.println("pathLength: ");
    if(path[pathLength-2]=='B'){
    Serial.println("shortening path");
    shortPath();
     }
      Serial.println("straight001");
    straight();
  }
  readSensors();
  if(leftFarReading==HIGH && leftCenterReading==HIGH && rightCenterReading==HIGH 
    && rightFarReading==HIGH && leftNearReading==HIGH && rightNearReading==HIGH)
    {
     Serial.println("uturn001");  
    turnAround();
  }

}
void done()
{
  digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
  replaystage=1;
  path[pathLength]='D';
   Serial.println("d");
  pathLength++;
 while(digitalRead(leftFarSensor)!=HIGH)//black
 {
   digitalWrite(led, LOW);
   delay(150);
   digitalWrite(led, HIGH);
   delay(150);
 }
 delay(500);
  replay();
}

void turnLeft()
{
   Serial.println("left main");
  while(digitalRead(rightCenterSensor)!=HIGH||digitalRead(leftCenterSensor)!=HIGH)//black||black
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
 
  if(replaystage==0)
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
  }
}

void turnRight()
{  Serial.println("right major");
  while(digitalRead(rightCenterSensor)!=HIGH)//black
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
  }
   while(digitalRead(rightCenterSensor)==HIGH && digitalRead(rightCenterSensor)==HIGH)//white
   {
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(10);
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
  
  if(replaystage==0){
  path[pathLength]='R';
  Serial.println("r");
  pathLength++;
 // Serial.print("Path length: ");
  //Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
      Serial.println("shortening path");
      shortPath();
    }
  }
 
}

void straight()
{ Serial.println("straight main");
 if ( !(digitalRead(leftfollowsensor))==HIGH &&  (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH&& (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SL1 01111 L
{
    digitalWrite( rightMotor1 ,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW); 
      Serial.println("SL1 01111 L");
}

else if(!(digitalRead(leftfollowsensor))==HIGH && !(digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SL2 00111 L
{
  digitalWrite( rightMotor1 ,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW); 
      Serial.println("SL2 00111 L");
} 

else if((digitalRead(leftfollowsensor))==HIGH && !(digitalRead(leftCenterSensor))==HIGH &&!(digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SL3 10011 L
{
   digitalWrite( rightMotor1,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW);
       Serial.println("SL3 10011 L");
      
}
else if((digitalRead(leftfollowsensor))==HIGH && !(digitalRead(leftCenterSensor))==HIGH &&(digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SL4 10111 L
{
   digitalWrite( rightMotor1,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW);
      Serial.println("SL4 10111 L");
}
else if(!(digitalRead(leftfollowsensor))==HIGH && !(digitalRead(leftCenterSensor))==HIGH && !(digitalRead(rightCenterSensor))==HIGH && ((digitalRead( rightfollowsensor))==HIGH || (digitalRead(rightNearSensor))==HIGH))//SL5 00011 L
{
   digitalWrite( rightMotor1,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW);
      Serial.println("SL5 00011 L");
}
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH &&!(digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//Straight 11011  S
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
       Serial.println("Straight");
      
}
else if((digitalRead(leftfollowsensor))==HIGH && !(digitalRead(leftCenterSensor))==HIGH && !(digitalRead(rightCenterSensor))==HIGH &&!(digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//Straight 10001  S
{
      digitalWrite( rightMotor1,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW);
      delay(20);
       digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,LOW);
      digitalWrite(leftMotor2,LOW);
      delay(5);
       Serial.println("Straight1");
}
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH &&!(digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//sL 11001  
{
      digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,HIGH);
      digitalWrite(leftMotor2,LOW);
       Serial.println("sL 11001");
}
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH  &&!(digitalRead(rightNearSensor))==HIGH)//SR1 11100 
{
  digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW);
      Serial.println("SR1 11100 ");
}

else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SR2 11101
{
  digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,HIGH);
      digitalWrite(leftMotor2,LOW);
      Serial.println("SR2 11101 ");
      }
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && !(digitalRead(rightNearSensor))==HIGH)// 11100SR3
{
  digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW);
      Serial.println("11100SR3 ");
}
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && !(digitalRead(rightNearSensor))==HIGH)//SR4 11110
{
 digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,HIGH);
      digitalWrite(leftMotor2,LOW);
       Serial.println("SR4 11110");
}
else if(((digitalRead(leftfollowsensor))==HIGH || (digitalRead(leftCenterSensor))==HIGH )&& !(digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && !(digitalRead(rightNearSensor))==HIGH)//SR5 11000 
{
  digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW);
       Serial.println("SR5 11000 ");
}

else  
{ 
   return;
      
}
  /*if( digitalRead(leftCenterSensor)!=HIGH||digitalRead(leftfollowsensor)!=HIGH|| digitalRead(leftNearSensor)!=HIGH)//black,left
  {
    while(rightCenterSensor==HIGH)//white
    {
      digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    Serial.println("straight main111");
    delay(1);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1,HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(5);      
    readSensors();
    }
  }
  if(digitalRead(rightCenterSensor)!=HIGH||digitalRead(rightfollowsensor)!=HIGH || digitalRead(rightNearSensor)!=HIGH)//black,right
  {
    
    while(leftCenterSensor==HIGH)//white
    {
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2,LOW);
    delay(1);
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    Serial.println("straight main222");
    delay(5);  
    readSensors();
    }
  }
  
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    Serial.println("straight333");*/
  
}

void turnAround()
{ Serial.println("uturn main");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    readSensors();
     Serial.println("extra inch for u turn");
   while(digitalRead(leftfollowsensor)==HIGH && digitalRead(rightfollowsensor)==HIGH)//white
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
  path[pathLength]='B';
  pathLength++;
   Serial.println("straight after u turn");
  straight();
  Serial.println("b");
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
}

void shortPath(){
 int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){
    pathLength-=3;
    path[pathLength]='B';
    Serial.println("test1");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    Serial.println("test2");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    Serial.println("test3");
    shortDone=1;
  }
  
   
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    Serial.println("test4");
    shortDone=1;
  }
     
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    Serial.println("test5");
    shortDone=1;
  }
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='S';
    Serial.println("test6");
    shortDone=1;
  }
  
  path[pathLength+1]='D';
  path[pathLength+2]='D';
  pathLength++;
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
  printPath();
}




void printPath(){
  Serial.println(" ");
  int x;
  while(x<=pathLength){
  Serial.println(path[x]);
  x++;
  }
 // Serial.println("+++++++++++++++++");
}


void replay()
{
   Serial.println("replay start");
   readSensors();
  if(leftFarReading==HIGH && rightFarReading==HIGH)//white||white
  {
    straight();
  }
  else{
    if(path[readLength]==('D'))
    {
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(100);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
      endMotion();
    }
    if(path[readLength]=='L'){
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
      turnLeft();
    }
    if(path[readLength]=='R'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    turnRight();
    }
    if(path[readLength]=='S'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    straight();
    }
    
    readLength++;
  }
    
  replay();
  
}

void endMotion(){
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(200);
      digitalWrite(led, LOW);
    delay(200);
    digitalWrite(led, HIGH);
    delay(500);
  endMotion();
}


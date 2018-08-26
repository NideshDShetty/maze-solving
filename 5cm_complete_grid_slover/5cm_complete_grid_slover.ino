#include <StackArray.h>
StackArray <int> s;

//////dry run variables

int i=0,j=0;
int a[5][4];
int m=5,n=4;
int extrainchtime=250;
//int q=0;
//////////////////////
////////shortest path variables


int c= 0,x,y;
int ex,ey,ec,minimum=600,stackdata;
int prev_vx = 0,prev_vy = 1,prev_x,prev_y,curr_x,curr_y,curr_vx,curr_vy,z;
int b[5][4];
//int m=9,n=11;


////////////////


int control_pin = 11;

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




void setup() {
  // put your setup code here, to run once:
/////////////shortest path calculation part
 Serial.begin(9600);
    s.setPrinter (Serial);
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
  pinMode(control_pin,INPUT);
   int i,j;  

///////dry run before shortest path calculation
    
   dry_run(); 

   a[0][0]= -1;
   a[4][3] = -5; 
   digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(20000);
    /*int a[5][4] = {{-1, 1, 0, 1},
                   {0, 1, 1, 1},
                   {1, 0, 1, 1},
                   {0, 1, 1, 1},
                   {1, 1, 1, -5}};*/
    /*{//{-1, 0, 1, 1, 1,1,1,1,1,1},
{-1, 1, 1, 1, 1,1,1,1,0,1},
{1 , 1, 0, 1, 1,1,1,1,1,1},
{1 , 1, 1, 1, 1,1,1,0,1,1},
{1, 1, 0, 1, 1,1,0,1,1,1},
{1 , 1, 1, 1, 1,1,1,0,1,1},
{1 , 1, 1, 1, 1,1,1,0,1,1},
{1 , 1, 1, 1, 1,1,1,0,1,1},
{1 , 1, 1, 1, 1,1,1,0,-5,1}};*/

////////////////////////////////shortest path calculation starts...
   for(i=0;i<m;i++)
   {
    for(j=0;j<n;j++)
    {
      Serial.print(a[i][j]);
    }
    Serial.println();
   }
        for(i=0;i<m;i++)
        {
                for(j=0;j<n;j++)
                {
                        if(a[i][j]<=0)
                        b[i][j]=a[i][j];
                        if(a[i][j]==1)
                        b[i][j]=100;
                }
        }
       
        for(i=0;i<m;i++)
        {
                for(j=0;j<n;j++)
                        if(b[i][j]==-1)
                adjacent(i,j);
        }
        for(c=1;c<80;c++)
        {
                for(i=0;i<m;i++)
                {
                for(j=0;j<n;j++)
                        if(b[i][j]==c)
                                adjacent(i,j);
                }
        }
           for(i=0 ; i<m ; i++)
     {
      for(j=0 ; j< n ; j++)
      {
        if(b[i][j] == -5)
        {
          ex=i;
          ey=j;
          ec = ex*100 + ey;
          s.push(ec);
        }
      }
     }

     while(minimum !=-1 )
     {
      shortestpath(ex,ey);
      ex = stackdata/100;
      ey = stackdata%100;
      
     }
      /* while (!s.isEmpty ())
    {
   Serial.println(s.pop());
    }*/

   // s.pop();
    z= s.pop();
      
   prev_x = z/100;
   prev_y = z%100;
     

///////////////////////////////////

  
 
 

}

void loop() {
  
  shortest_path_tracer();
Serial.println("dfhmghrfgh");
}


void dry_run()
{
   while(i<(m-1))
  {Serial.println(i);
    while(j<n)
    {
      if(((digitalRead(leftfollowsensor))!=HIGH || (digitalRead(leftCenterSensor))!=HIGH || (digitalRead(rightCenterSensor))!=HIGH || (digitalRead( rightfollowsensor))!=HIGH || (digitalRead(rightNearSensor))!=HIGH  ||  digitalRead(leftNearSensor) != HIGH) && (digitalRead(leftFarSensor) == HIGH   && digitalRead(rightFarSensor) == HIGH ))
      {
        straight();
      }
      else
      {
        node_detected();
        j++;
        extra_inch();
      }
    }
  /* while( i == m-1)
    {
      digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    }*/
       dryrunturnRight();
       
       while((digitalRead(leftFarSensor) == HIGH /* && digitalRead(leftNearSensor) == HIGH */ && digitalRead(rightFarSensor) == HIGH ))
      {
        straight();
      }
       j--;
       i++;
       Serial.println(i);
       node_detected();
     
      
     extra_inch();
        if(i%2==1)
     {
      dryrunturnRight();
     }

    if(i<(m-1))
    {  
    while(j>0)
    {
      if(((digitalRead(leftfollowsensor))!=HIGH || (digitalRead(leftCenterSensor))!=HIGH || (digitalRead(rightCenterSensor))!=HIGH || (digitalRead( rightfollowsensor))!=HIGH || (digitalRead(rightNearSensor))!=HIGH || digitalRead(leftNearSensor) != HIGH) && (digitalRead(leftFarSensor) == HIGH && digitalRead(rightFarSensor) == HIGH ))
      {
        straight();
      }
      else
      {
        j--;
        node_detected();
        extra_inch();
      }
       
     
     
        
    }
   /* while( i == m-1)
    {
      digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
   
    }*/
    
      dryrunturnLeft();
       while((digitalRead(leftFarSensor) == HIGH /* && digitalRead(leftNearSensor) == HIGH */ && digitalRead(rightFarSensor) == HIGH ))
      {
        straight();
      }
     i++;
    Serial.println(i);
       node_detected();
       j++;
        extra_inch();
     
       if(i%2==0)
      {
        dryrunturnLeft();
      }
     
  }
 }
 
  /*digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
     for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      Serial.print(a[i][j]);
    }
    Serial.println();
  }*/
   if(m%2==1)
      {
        while(j<n)
    {
      if(((digitalRead(leftfollowsensor))!=HIGH || (digitalRead(leftCenterSensor))!=HIGH || (digitalRead(rightCenterSensor))!=HIGH || (digitalRead( rightfollowsensor))!=HIGH || (digitalRead(rightNearSensor))!=HIGH  ||  digitalRead(leftNearSensor) != HIGH) && (digitalRead(leftFarSensor) == HIGH   && digitalRead(rightFarSensor) == HIGH ))
      {
        straight();
      }
      else
      {
        node_detected();
        j++;
        extra_inch();
      }
    }
      }
       if(m%2==0)
      {
        while(j>0)
    {
      if(((digitalRead(leftfollowsensor))!=HIGH || (digitalRead(leftCenterSensor))!=HIGH || (digitalRead(rightCenterSensor))!=HIGH || (digitalRead( rightfollowsensor))!=HIGH || (digitalRead(rightNearSensor))!=HIGH || digitalRead(leftNearSensor) != HIGH) && (digitalRead(leftFarSensor) == HIGH && digitalRead(rightFarSensor) == HIGH ))
      {
        straight();
      }
      else
      {
        j--;
        node_detected();
        extra_inch();
      }
      
     

        
    }
      }
 }
int node_detected()
{
  if(digitalRead(leftFarSensor) != HIGH /*&& digitalRead(leftNearSensor) != HIGH  &&*/ || digitalRead(rightFarSensor) != HIGH )
  {
    if((digitalRead(leftCenterSensor))==HIGH || (digitalRead(rightCenterSensor))==HIGH /*|| (digitalRead( rightfollowsensor))==HIGH*/)
    {
      a[i][j] = 0; //white node
    }
    else
    {
      a[i][j] = 1; //black node
    }
  }
 /* if(digitalRead(leftFarSensor) != HIGH /*&& digitalRead(leftNearSensor) != HIGH  && digitalRead(rightFarSensor) == HIGH )
  {
    if((digitalRead(leftCenterSensor))==HIGH || (digitalRead(rightCenterSensor))==HIGH )
    {
      a[i][j] = 0; //white node
    }
    else
    {
       a[i][j] = 1; //black node
    }
  }
  if(digitalRead(leftFarSensor) == HIGH /* && digitalRead(leftNearSensor) == HIGH  && digitalRead(rightFarSensor) != HIGH )
  {
    if((digitalRead(leftCenterSensor))==HIGH ||(digitalRead(rightCenterSensor))==HIGH)
    {
       a[i][j] = 0; //white node
    }
    else
    {
       a[i][j] = 1; //black node
    }
  }*/
  
  return 0;
  
}

void extra_inch()
{
   digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(extrainchtime);
}

void dryrunturnLeft()
{
  /*  digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(400);*/

    
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
   // q = 1;
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
  /*while(digitalRead(rightfollowsensor)==HIGH)//white
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
  }*/
/*  if(q == 0)
 { 
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
 }
  q = 0;*/
 
 /* while(digitalRead(rightfollowsensor)==HIGH)//white
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
  }*/
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

void dryrunturnRight()
{ 
    /*digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(400);*/


    
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
   // q = 1;
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
  /*while(digitalRead(leftfollowsensor)==HIGH)// && digitalRead(rightCenterSensor)==HIGH)//white
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
  }*/
 /* if(q == 0)
  {
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
  }
  q = 0;
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
/*void straight()
{  Serial.println("straight main");
 if ( !(digitalRead(leftfollowsensor))==HIGH &&  (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH&& (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SL1 01111 L
{
    digitalWrite( rightMotor1 ,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,HIGH); 
}

else if(!(digitalRead(leftfollowsensor))==HIGH && !(digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SL2 00111 L
{
  digitalWrite( rightMotor1 ,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW); 
} 

else if((digitalRead(leftfollowsensor))==HIGH && !(digitalRead(leftCenterSensor))==HIGH &&!(digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SL3 10011 L
{
   digitalWrite( rightMotor1,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW);
}
else if((digitalRead(leftfollowsensor))==HIGH && !(digitalRead(leftCenterSensor))==HIGH &&(digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SL4 10111 L
{
   digitalWrite( rightMotor1,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW);
}
else if(!(digitalRead(leftfollowsensor))==HIGH && !(digitalRead(leftCenterSensor))==HIGH && !(digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SL5 00011 L
{
   digitalWrite( rightMotor1,HIGH);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,LOW);
      digitalWrite(leftMotor2,LOW);
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
}
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH &&!(digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//sr 11001  
{
      digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,HIGH);
      digitalWrite(leftMotor2,LOW);
}
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH  &&!(digitalRead(rightNearSensor))==HIGH)//SR1 11100 
{
  digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW);
}
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && (digitalRead(rightNearSensor))==HIGH)//SR2 11101
{
  digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1,HIGH);
      digitalWrite(leftMotor2,LOW);
      }
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && !(digitalRead(rightNearSensor))==HIGH)// 11100SR3
{
  digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW);
}
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH && (digitalRead(rightCenterSensor))==HIGH && (digitalRead( rightfollowsensor))==HIGH && !(digitalRead(rightNearSensor))==HIGH)//SR4 11110
{
 digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,HIGH);
      digitalWrite( leftMotor1,HIGH);
      digitalWrite(leftMotor2,LOW);
}
else if((digitalRead(leftfollowsensor))==HIGH && (digitalRead(leftCenterSensor))==HIGH && !(digitalRead(rightCenterSensor))==HIGH && !(digitalRead( rightfollowsensor))==HIGH && !(digitalRead(rightNearSensor))==HIGH)//SR5 11000 
{
  digitalWrite( rightMotor1,LOW);
      digitalWrite( rightMotor2,LOW);
      digitalWrite( leftMotor1 ,HIGH);
      digitalWrite(leftMotor2,LOW);
}
                                                                                    

else  
{ 
   return;
      
}
}*/  
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

void shortest_path_tracer()
{
  while(digitalRead(leftFarSensor) == HIGH && /*digitalRead(leftNearSensor) == HIGH  &&*/ digitalRead(rightFarSensor) == HIGH )  
      {
        straight();       
      }
   if(digitalRead(leftFarSensor) != HIGH || /*digitalRead(leftNearSensor) != HIGH  ||*/  digitalRead(rightFarSensor) != HIGH) 
   {
    /*if( digitalRead(leftFarSensor) != HIGH || digitalRead(leftNearSensor) != HIGH || digitalRead(leftfollowsensor) != HIGH || digitalRead(leftCenterSensor) != HIGH)
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
   }

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

int adjacent(int x,int y)
{
        if(x<(m-1) && y<m)
        {
        if(b[x+1][y]>c)
               b[x+1][y]=c+1;
        }
        if(x<m && y<(n-1))
        {
                if(b[x][y+1]>c)
                b[x][y+1]=c+1;
        }
        if(x>0 && y>-1)
        {
                if(b[x-1][y]>c)
                        b[x-1][y]=c+1;
        }
        if(x>-1 && y>0)
        {
                if(b[x][y-1]>c)
                        b[x][y-1]=c+1;
        }
        return 0;
}
int shortestpath(int x, int y)
{ 

  int c=0,d=0;
 if(x<(m-1) && y<n)
 {
  if(b[x+1][y] != 0)
  {
    minimum = b[x+1][y];
    c=x+1;
    d=y;
  }
 }

 if(x>0 && y>-1)
 {
  if((b[x-1][y]< minimum )&& (b[x-1][y] != 0 ))
  {//Serial.println("abcd");
     minimum = b[x-1][y];
     c = x-1;
     d= y; 
  }
 }

 
 if(x<m && y<(n-1))
 {
   if((b[x][y+1]< minimum )&& (b[x][y+1] != 0 ))
  {
     minimum = b[x][y+1];
     c = x;
     d= y+1; 
  }
 }

 if(x>-1 && y>0)
 {
   if((b[x][y-1]< minimum )&& (b[x][y-1] != 0 ))
  {//Serial.println("sdfgh");
     minimum = b[x][y-1];
     c = x;
     d= y-1; 
  }
 }

 stackdata = 100*c+d;
// Serial.println(stackdata);
 s.push(stackdata);

 if(b[x][y]== minimum)
 {

 s.pop();
 s.pop();
 }

 b[x][y] = 500;


 return 0;
 
}


int path_tracing()
{
  if(!s.isEmpty ())
  {Serial.println("stack not empty");
    z = s.pop();
    curr_x = z/100;
    curr_y = z%100;
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
    delay(400);
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
    delay(250);

    
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
    delay(250);


    
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



#include <Servo.h>


//In and Out
int led = 2;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;


//Variables
byte com = 0;
int group = 1;
int Move = 0;
int Grab = 0;
int Pitch = 0;
int left = 0;
int right = 0;
int up = 0;
int down = 0;
int on = 0;
int grabbed=0;

//The initial angles values for each motor
float mot1 = 90;
float mot2 = 90;
float mot3 = 90;
float mot4 = 180;
float mot5 = 90;

void setup()
{
Serial.begin(9600);
pinMode(led, OUTPUT); // sets the ledPin to be an output
servo1.attach(3);     //Attach the servo 1 to pin 3, servo 2 to 5 and so on...
servo2.attach(5);
servo3.attach(6);
servo4.attach(9);
servo5.attach(11);


Serial.write(0xAA);
Serial.write(0x00);//Waiting
delay(100);
Serial.write(0xAA);
Serial.write(0x37);//Compact mode
delay(100);
Serial.write(0xAA);
Serial.write(0x00);//Waiting
delay(100);
Serial.write(0xAA);
Serial.write(0x21);//Import group 1
}


void Salute()
{
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(180);
  servo5.write(90); 
  delay(500);
  servo3.write(180);
  delay(500);
  servo3.write(90);
  delay(500);
  servo3.write(180);
  delay(500);
  servo3.write(90);
  delay(500);
  servo3.write(180);
  delay(500);
  servo3.write(90);
  delay(500);
}









void loop() // run over and over again
{
while(Serial.available())
{
com = Serial.read();  //We receive the voice command and save it in the com byte 


    //We start in the first group
    if(group == 1)
    {     
        if(com == 0x11)//Hello
        {
          on = 1;
          digitalWrite(led,HIGH); //Turn ON the LED
          //Put the servos in to ON position
          servo1.write(mot1);
          servo2.write(mot2);
          servo3.write(mot3);
          servo4.write(mot4);
          servo5.write(mot5);  
          delay(100);
          com = 0x00;   //Change the value of the com byte in to a never used one in 
                        //order to not affect the next "if"     
        }
        
        if(com == 0x12)//Goodbye
        {
          on = 0;
          digitalWrite(led,LOW);  //Turn OFF the LED
          //Put the servos in to OFF position
          servo1.write(90);
          servo2.write(0);
          servo3.write(180);
          servo4.write(180);
          servo5.write(90);   
          delay(100);
          com = 0x00;
        }
        
        if(com == 0x13)//Move
        {      
          group = 2;    //We switch to the next group
          Move = 1;     //Put the arm in to moving mode
          Grab = 0;     //Grab mode is off
          //Now we send the import group 2 comands
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x22);
          delay(100);
          com = 0x00;
        }
        
        if(com == 0x14)//Pitch
        {
          //Here we do the same but with Pitch mode
          group = 2;
          Move = 0;
          Grab = 0;
          Pitch = 1;
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x22);
          delay(100);
          com = 0x00;
        }
        
        if(com == 0x15)//Grab
        {
          //We do the same with grab mode but we stay in the same group
          Move = 0;
          Grab = 1;
          Pitch = 0;
          com = 0x00;
        }
    }//End of group 1















    //Start of group 2 commands
    if(group == 2 )
    {
        if(com == 0x11)//Left
        {
          //We switch to the next group and activateh the left mode
          group = 3;
          left = 1;
          right = 0;
          up = 0;
          down = 0;           
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x23);
          delay(100);
          com = 0x00;
        }
        
        if(com == 0x12)//Right
        {      
          group = 3;
          left = 0;
          right = 1;
          up = 0;
          down = 0; 
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x23);
          delay(100);
          com = 0x00;
        }
        
        if(com == 0x13)//Up
        {
          
          group = 3;
          left = 0;
          right = 0;
          up = 1;
          down = 0; 
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x23);
          delay(100);
          com = 0x00;
        }
        
        if(com == 0x14)//Down
        {
          
          group = 3;
          left = 0;
          right = 0;
          up = 0;
          down = 1; 
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x23);
          delay(100);
          com = 0x00;
        }
        
        if(com == 0x15)//Salute
        {
          
          group = 1;
          Move = 0;
          Grab = 0;
          Pitch = 0;
          Salute();
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x21);
          delay(100);
          com = 0x00;
        }
    }//End of group 2











    if(group == 3 )
    {
        if(com == 0x11)//Stop
        {      
          group = 1;
          Move = 0;
          Grab = 0;
          Pitch = 0;
          left = 0;
          right = 0;
          up = 0;
          down = 0; 
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x21);
          delay(100);
          com = 0x00;
          digitalWrite(led,HIGH);
        }
    
    
    
    
    /////////////These comands are not used in this project//////////
        if(com == 0x12)//One
        {
         
          group = 1;
          Move = 0;
          Grab = 0;
          Pitch = 0;
          left = 0;
          right = 0;
          up = 0;
          down = 0;
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x21);
          delay(100);
          com = 0x00;
        }
        
        if(com == 0x13)//Two
        {
          
          group = 1;
          Move = 0;
          Grab = 0;
          Pitch = 0;
          left = 0;
          right = 0;
          up = 0;
          down = 0;
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x21);
          delay(100);
          com = 0x00;
        }
        
        if(com == 0x14)//Three
        {
          
          group = 1;
          Move = 0;
          Grab = 0;
          Pitch = 0;
          left = 0;
          right = 0;
          up = 0;
          down = 0;
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x21);
          delay(100);
          com = 0x00;
          digitalWrite(led,LOW);
        }
        
        if(com == 0x15)//Four
        {
          
          group = 1;
          Move = 0;
          Grab = 1;
          Pitch = 0;
          left = 0;
          right = 0;
          up = 0;
          down = 0;
          delay(10);
          Serial.write(0xAA);
          Serial.write(0x00);
          delay(100);
          Serial.write(0xAA);
          Serial.write(0x21);
          delay(100);
          com = 0x00;
          digitalWrite(led,HIGH);
        }
    }//End of group 3
}//end of received bytes while



if(on==1)
{
  if(Move == 1)
  {
    if(left==1)
    {
      mot1 = mot1 + 0.001;  //We increase the angle of motor 1
      //Define angle range
      if(mot1>180)
      {
        mot1=180;
      }
      if(mot1<0)
      {
        mot1=0;
      }
      //Weithe the angle
      servo1.write(mot1);      
    }//enf of left
  
  
    if(right==1)
    {
      mot1 = mot1 - 0.001;  //We decrease the angle of motor 1
      //Define angle range
      if(mot1>180)
      {
        mot1=180;
      }
      if(mot1<0)
      {
        mot1=0;
      }
      //Weithe the angle
      servo1.write(mot1);      
    }//enf of right
  
  
    if(up==1)
    {
      mot2 = mot2 + 0.001;  //We increase the angle of motor 2
      //Define angle range
      if(mot2>180)
      {
        mot2=180;
      }
      if(mot2<0)
      {
        mot2=0;
      }
      //Weithe the angle
      servo2.write(mot2);      
    }//enf of up
    
  
    if(down==1)
    {
      mot2 = mot2 - 0.001;  //We decrease the angle of motor 2
      //Define angle range
      if(mot2>180)
      {
        mot2=180;
      }
      if(mot2<0)
      {
        mot2=0;
      }
      //Weithe the angle
      servo2.write(mot2);      
    }//enf of up  
  }//end of move
  
  
  
  
  
  
  if(Pitch == 1)
  {
    if(left==1)
    {
      mot3 = mot3 + 0.001;  //We increase the angle of motor 3
      //Define angle range
      if(mot3>180)
      {
        mot3=180;
      }
      if(mot3<0)
      {
        mot3=0;
      }
      //Weithe the angle
      servo3.write(mot3);      
    }//enf of left
  
  
    if(right==1)
    {
      mot3 = mot3 - 0.001;  //We decrease the angle of motor 3
      //Define angle range
      if(mot3>180)
      {
        mot3=180;
      }
      if(mot3<0)
      {
        mot3=0;
      }
      //Weithe the angle
      servo3.write(mot3);      
    }//enf of right
  
  
    if(up==1)
    {
      mot4 = mot4 + 0.001;  //We increase the angle of motor 4
      //Define angle range
      if(mot4>180)
      {
        mot4=180;
      }
      if(mot4<0)
      {
        mot4=0;
      }
      //Weithe the angle
      servo4.write(mot4);      
    }//enf of up
    
  
    if(down==1)
    {
      mot4 = mot4 - 0.001;  //We decrease the angle of motor 2
      //Define angle range
      if(mot4>180)
      {
        mot4=180;
      }
      if(mot4<0)
      {
        mot4=0;
      }
      //Weithe the angle
      servo4.write(mot4);      
    }//enf of up
  }//end of pitch
  
  
  
  if(Grab == 1 && grabbed)
  {
    servo5.write(180); //open
    Grab = 0;
    grabbed = 0;
  }
  
  
  if(Grab == 1 && !grabbed)
  {
    servo5.write(0); //close 
    Grab = 0;
    grabbed = 0;
  }
}//end of ON
}//end of the loop

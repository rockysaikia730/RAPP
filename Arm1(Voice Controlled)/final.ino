#include <VarSpeedServo.h>


VarSpeedServo servo1;
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;



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
int grabbed = 0;



float mot1 = 0;
float mot2 = 30;
float mot3 = 30;
float mot4 = 50;
float mot5 =180;
float mot6 =175;
float mot7 =145;
float mot8 =0;

void setup() 
{
  Serial.begin(9600);
  servo1.attach(A1);
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);



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

void loop()
{
  while(Serial.available())
     {
     com = Serial.read();



          if(group == 1)
           {
                if(com == 0x11)//Hello
                   {
                      on = 1;
                      servo1.write(0);
                      servo2.write(175);
                      servo3.write(145);
                      servo4.write(0); 
                      delay(100);
                      com = 0x00;        
                   }

                if(com == 0x12) //Goodbye
                    {
                      on = 0;
                      servo1.write(0);
                      servo2.write(175);
                      servo3.write(145);
                      servo4.write(50);
                      delay(100);
                      com = 0x00;
                    }
                    
                 if(com == 0x13)//Move
                  {      
                    group = 2;    //We switch to the next group
                    Move = 1;     //Put the arm in to moving mode
                    Grab = 0;
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
                  group = 2;
                  Move = 0;
                  Grab = 1;
                  Pitch = 0;
                  delay(10);
                  Serial.write(0xAA);
                  Serial.write(0x00);
                  delay(100);
                  Serial.write(0xAA);
                  Serial.write(0x22);
                  delay(100);
                  com = 0x00;
                 }

                  

             }


      if(group == 2)
       { 
           if(com == 0x11)//Left
            {
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
              right = 1;
              left = 0;
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

            if(com == 0x13)//up
             {
              group = 3;
              up = 1;
              left = 0;
              right = 0;
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

            if(com == 0x14)//down
             {
              group = 3;
              down = 1;
              left = 0;
              right = 0;
              up = 0;
              delay(10);
              Serial.write(0xAA);
              Serial.write(0x00);
              delay(100);
              Serial.write(0xAA);
              Serial.write(0x23);
              delay(100);
              com = 0x00; 
             }
       }


    if(group == 3)
     {
        if(com == 0x11)//stop
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
     }
 


if(on==1)
{
  if(Move == 1)
  {
    if(left == 1)
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
      servo1.write(mot1,30);      
    }//enf of left

    if(right == 1)
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
      servo1.write(mot5,30);      
    }//enf of right

    if(up == 1)
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
      servo2.write(mot2,30);      
    }//enf of up

     if(down == 1)
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
      servo2.write(mot6,30);      
    }//enf of up  
   }

   
  if(Pitch == 1)
  {
    if(up == 1)
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
      servo3.write(mot3,30);      
    }//enf of up
    
  
    if(down == 1)
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
      servo3.write(mot7,30);      
    }//enf of up
  }

 if(Grab == 1)
 {
   if(up == 1)
   {
    mot4 = mot4 - 0.001;  //We decrease the angle of motor 4
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
   }

   if(down == 1)
    {
      mot4 = mot4 - 0.001;  //We decrease the angle of motor 3
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
      servo4.write(mot8);
    }
}
}
}
}        


     

/*
Robot_Full
This Pogram For controlling 4-wheels chasis robot using a standard PC Joysticks Analog Buttons
Implemented by Mahmoud Ayman <mahmoud.ayman07@gmail.com> 
ALL COPYRIGHT RESERVED, AXIS TEAM
THIS IS AN OPEN-SOURCE PROJECT, FOLLOW THE COMMENTS

This Code was published in the public domain
The Idea of this project is to capture the state of the buttons (right,left,up,down)
by detecting the value of the potentiometers attached to each button
Each button is attached to two pots, one change it's value when by moving the button up&down
the other cahnges by moving the button left&right
This Program used 2 analog buttons 
Right button ----> to control forward and backward motion
Left button ----> to control left and right rotations
*/

int m11 =2;  //Digital Outputs for motors pin 2 to 5
int m12 = 3;
int m21 = 4;
int m22=5;


int sens=0;  //Analog Input for joystics
int sens2 =1; // right button pin 0 left button pin 1


int val =0;      //variables for analog input values
int val2 = 0;


int state=0;      //variables to save the state of the buttons
int laststate=0;

void stopm()        //function to stop all the motors for hardware debounce
{
  digitalWrite(m11, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m22, LOW);
  delay(50);
}

void setup ()
{
  Serial.begin(9600);
  pinMode(sens, INPUT);
  pinMode(sens2, INPUT);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
}

void loop ()
{
  val = analogRead(sens);          //reading the values from the buttons
  val2 = analogRead(sens2);
  Serial.println(val);
  Serial.println(val2);
  
  //Check the states of the button
  if ((val > 1000) && (val2 >400) && (val2 < 600))
  {
    Serial.println("left");
    state=1;
  }
  else if ((val < 100) && (val2 >400) && (val2 < 600))
  {
    Serial.println("right");
    state=2;
  }
  else if ((val2 > 1000) && (val >450) && (val < 600))
  {
    Serial.println("forward");
    state=3;
  }
  else if ((val2 <100) && (val >450) && (val < 600))
  {
    Serial.println("backward");
    state=4;
  }
  else if ( (val >450) && (val < 600) && (val2 >400) && (val2 < 600))
  {
    Serial.println("stop");
    state=5;
  }
  
  //moving the motors according to the state of the button
  if ( state != laststate)
  {
    if (state == 1)
    {
      stopm();
      digitalWrite(m21, HIGH);
      digitalWrite(m12, HIGH);
      
      
      delay(50);
    }
    if (state == 2)
    {
      stopm();
      digitalWrite(m22, HIGH);
      digitalWrite(m11, HIGH);
      
      
    }
    else if (state == 4)
    {
      stopm();
      digitalWrite(m11, HIGH);
      digitalWrite(m21,HIGH);
      delay(50);
    }
    else if (state == 3)
    {
      stopm();
      digitalWrite(m12, HIGH);
      digitalWrite(m22, HIGH);
      delay(50);
      
    }
    else if (state == 5)
    {
      stopm();
      delay(50);
    }
    laststate=state;
    state=0;
  }
}

//Button pins
int bottomSwitch = 17;
int middleSwitch = 18;
int topSwitch = 19;

//Speaker
int speaker = 10;

//LED Pins
int redColor = 3;
int greenColor = 4;
int blueColor = 5;
int greenTwo = 6;
int redTwo = 9;


const float INITIAL_TIME = 25000;


void playBuzzer(int val, int time)
{
  for (int i = 0; i < time; i++)
  {
    digitalWrite(speaker,HIGH);
    delayMicroseconds(val);
    digitalWrite(speaker,LOW);
      delayMicroseconds(900);
  }
}


int selectLED()
{
  int randomNumber = random(0,3);
  switch(randomNumber)
  {
    case 0:
      return redColor;
    case 1:
      return greenColor;
    case 2:
      return greenTwo;
  }
  return 0;
}

void setup()
{
  pinMode(redColor, OUTPUT);
  pinMode(greenColor, OUTPUT);
  pinMode(blueColor, OUTPUT);
  pinMode(redTwo, OUTPUT);
  pinMode(greenTwo, OUTPUT);

  pinMode(bottomSwitch, INPUT);
  pinMode(middleSwitch, INPUT);
  pinMode(topSwitch, INPUT);

  pinMode(speaker, OUTPUT);
}

void shine()
{
  int Counter = 40;
  
    analogWrite(greenColor, Counter);
    analogWrite(redColor, Counter);
    analogWrite(greenTwo, Counter);
    delay(500);
    analogWrite(greenColor, 0);
    analogWrite(redColor, 0);
    analogWrite(greenTwo, 0);
    delay(500);
}

void fade()
{
  int Counter = 255;
  while (true)
  { //break;
    analogWrite(greenColor, Counter);
    analogWrite(redColor, Counter);
    analogWrite(greenTwo, Counter);
    if(digitalRead(bottomSwitch) == 1 || digitalRead(middleSwitch) == 1 || digitalRead(topSwitch) == 1) //button is pressed
    {
      playBuzzer(30, 50);
      break;
    }    
    delay(100);
    if(digitalRead(bottomSwitch) == 1 || digitalRead(middleSwitch) == 1 || digitalRead(topSwitch) == 1) //button is pressed
    {
      playBuzzer(30, 50);
      break;
    }    
    Counter-= 10;
    if (Counter <= 0)
    {
      analogWrite(greenColor, 0);
      analogWrite(redColor, 0);
      analogWrite(greenTwo, 0);
      delay(1000);
      Counter = 255;
    }
  
    if(digitalRead(bottomSwitch) == 1 || digitalRead(middleSwitch) == 1 || digitalRead(topSwitch) == 1) //button is pressed
    {
      playBuzzer(30, 50);
      break;
    }
    else
      continue;
  }
}

void loop()
{


    //Idle Mode
    fade();
      shine();
      shine();
      shine();
      shine();

    analogWrite(greenColor, 0);
    analogWrite(redColor, 0);
    analogWrite(greenTwo, 0);

    playBuzzer(50, 50);
    analogWrite(greenColor, 50);
    analogWrite(redColor, 50);
    analogWrite(greenTwo, 50);


    analogWrite(greenColor, 0);
    analogWrite(redColor, 0);
    analogWrite(greenTwo, 0);
  //The Gameplay

  float totalTime = INITIAL_TIME;
  float timeLeft = totalTime;
  int litLED = selectLED();
  
  
  while (timeLeft > 0)
  {
    analogWrite(litLED, 50);
    if ((litLED == redColor && digitalRead(bottomSwitch) == 1) || (litLED == greenColor && digitalRead(middleSwitch) == 1) || (litLED == greenTwo && digitalRead(topSwitch) == 1)) //If the correct button is pressed
    {
      analogWrite(litLED, 0); //analogWrite the litLED to LOW
      playBuzzer(300, 300); //Short sound with speaker
      litLED = selectLED();
      totalTime -= 300;
      timeLeft = totalTime;
      continue;
    }

    delay(150);
    timeLeft -= 300;
  }

  //Losing sequence
   playBuzzer(1000, 1000); //Must use PWM
  shine();
  shine();
  shine();
  playBuzzer(100, 100); //Must use PWM
  

  delay (4000);
}





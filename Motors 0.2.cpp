int ColourLineSensor = 13;
int PowerLineSensor=12;
int DirectionOfRightEngine = 4;
int SpeedOfRightEngine=5;
int DirectionOfLeftEngine = 7;
int SpeedOfLeftEngine=6;
void setup()
{
  pinMode(ColourLineSensor,INPUT);
  pinMode(PowerLineSensor,OUTPUT);
  pinMode(DirectionOfRightEngine,OUTPUT);
  pinMode(SpeedOfRightEngine,OUTPUT);
  pinMode(SpeedOfLeftEngine,OUTPUT);
  pinMode(DirectionOfLeftEngine,OUTPUT);
  digitalWrite(PowerLineSensor,HIGH);
  digitalWrite(DirectionOfRightEngine,HIGH);
  digitalWrite(DirectionOfLeftEngine,HIGH);
}
void loop()
{
  if (digitalRead(ColourLineSensor)== LOW)
  {
    analogWrite(SpeedOfRightEngine,127);
    analogWrite(SpeedOfLeftEngine,127);
  } else {
    analogWrite(SpeedOfRightEngine,0);
    analogWrite(SpeedOfLeftEngine,0);
  }
}

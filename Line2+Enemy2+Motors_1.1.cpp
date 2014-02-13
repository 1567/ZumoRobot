/////// РАСПИНОВКА ///////
int DirectionOfEngine[] = {7,4};    //левый - 0, правый - 1 (и везде далее)
int SpeedOfEngine[] = {6,5};
int EnemyDetector[] = {1,2);
int BorderDetector[] = {8,9};
int Start = 10;

/////// КАКИЕ-ТО ЗНАЧЕНИЯ ///////
const int MaxVelocity = 153;
int PositionOfEnemy = 0;            //слева - 0, справа - 1, спереди - 2


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
  pinMode(DirectionOfEngine[0],OUTPUT);
  pinMode(SpeedOfEngine[0],OUTPUT);
  pinMode(DirectionOfEngine[1],OUTPUT);
  pinMode(SpeedOfEngine[1],OUTPUT);
  pinMode(BorderDetector[1],INPUT);
  pinMode(BorderDetector[0],INPUT);
  pinMode(EnemyDetector[0],INPUT);
  pinMode(EnemyDetector[1],INPUT);
  pinMode(Start,INPUT);
  stopRobot();
  initialPosition();
}

void loop(){
  controlBorder();
  findEnemy();
  attack();
} 




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void goForward(){
  digitalWrite(DirectionOfEngine[0], HIGH);
  digitalWrite(DirectionOfEngine[1], HIGH);
  analogWrite(SpeedOfEngine[0], MaxVelocity);
  analogWrite(SpeedOfEngine[1], MaxVelocity);
}

void goBack(){
  digitalWrite(DirectionOfEngine[0], LOW);
  digitalWrite(DirectionOfEngine[1], LOW);
  analogWrite(SpeedOfEngine[0], MaxVelocity);
  analogWrite(SpeedOfEngine[1], MaxVelocity);
}

void turnLeft(){
  digitalWrite(DirectionOfEngine[0], LOW);
  digitalWrite(DirectionOfEngine[1], HIGH);
  analogWrite(SpeedOfEngine[0], MaxVelocity);
  analogWrite(SpeedOfEngine[1], MaxVelocity);
}

void turnRigth(){
  digitalWrite(DirectionOfEngine[0], HIGH);
  digitalWrite(DirectionOfEngine[1], LOW);
  analogWrite(SpeedOfEngine[0], MaxVelocity);
  analogWrite(SpeedOfEngine[1], MaxVelocity);
}

void stopRobot(){
  analogWrite(SpeedOfEngine[0], 0);
  analogWrite(SpeedOfEngine[1], 0);
}

void turn(int Direction){
  if (Direction == 0) turnLeft();
  if (Direction == 1) turnRight();
}

void turnForward(int Direction){                //ехать вперёд с поворотом
  digitalWrite(DirectionOfEngine[0], HIGH);
  digitalWrite(DirectionOfEngine[1], HIGH);
  if (Direction == 0){
    analogWrite(SpeedOfEngine[0], MaxVelocity*2/3);
    analogWrite(SpeedOfEngine[1], MaxVelocity);
  if (Direction == 1){
    analogWrite(SpeedOfEngine[1], MaxVelocity*2/3);
    analogWrite(SpeedOfEngine[0], MaxVelocity);
}

void turnBack(int Direction){
  digitalWrite(DirectionOfEngine[0], LOW);
  digitalWrite(DirectionOfEngine[1], LOW);
  if (Direction == 0){
    analogWrite(SpeedOfEngine[0], MaxVelocity*2/3);
    analogWrite(SpeedOfEngine[1], MaxVelocity);
  if (Direction == 1){
    analogWrite(SpeedOfEngine[1], MaxVelocity*2/3);
    analogWrite(SpeedOfEngine[0], MaxVelocity);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initialPosition(){
  while (digitalRead(Start) != 1) controlEnemy();
}

void controlEnemy(){
  if (digitalRead(enemyDetector[0]) == 1 && digitalRead(enemyDetector[1]) == 0) PositionOfEnemy = 0;
  if (digitalRead(enemyDetector[0]) == 0 && digitalRead(enemyDetector[1]) == 1) PositionOfEnemy = 1;
  if (digitalRead(enemyDetector[0]) == 1 && digitalRead(enemyDetector[1]) == 1) PositionOfEnemy = 2;
}

void findEnemy(){
  if (PositionOfEnemy != 2) turn(PositionOfEnemy);
  while (PositionOfEnemy != 2) controlEnemy();
  stopRobot();
}

void controlBorder(){
  if (digitalRead(borderDetector[0]) == 1 && digitalRead(borderDetector[1]) == 0) while (digitalRead(borderDetector[0]) == 1) turnBack(1);
  if (digitalRead(borderDetector[0]) == 0 && digitalRead(borderDetector[1]) == 1) while (digitalRead(borderDetector[1]) == 1)turnBack(0);
  if (digitalRead(borderDetector[0]) == 1 && digitalRead(borderDetector[1]) == 1) while (digitalRead(borderDetector[0]) == 1 || digitalRead(borderDetector[1]) == 1) goBack();
} 

void attack(){
  while (PositionOfEnemy == 2){
    controlEnemy();
    goForward();
  }
}

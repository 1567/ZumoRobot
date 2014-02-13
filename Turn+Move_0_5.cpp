//Комменты будут русскими

int ColourLineSensor[] = {8,9,10,11};    //ПЛ (Передний правый), ПП, ЗЛ, ЗП
int PowerLineSensors=12;
int DirectionOfEngine[] = {7,4};    //левый - 0, правый - 1
int SpeedOfEngine[] = {6,5};
int MaxVelocity = 153;        //не уверен, что верно помню. Поправь, если что.
int VOfSlow = 0;               //скорость более медленного колеса
int Slow = 0;                //какой из них медленнее
int flag = 0;


void setup()
{
  pinMode(ColourLineSensor[0],INPUT);
  pinMode(ColourLineSensor[1],INPUT);
  pinMode(ColourLineSensor[2],INPUT);
  pinMode(ColourLineSensor[3],INPUT);
  pinMode(PowerLineSensors,OUTPUT);
  pinMode(DirectionOfEngine[0],OUTPUT);
  pinMode(SpeedOfEngine[0],OUTPUT);
  pinMode(SpeedOfEngine[1],OUTPUT);
  pinMode(DirectionOfEngine[1],OUTPUT);
  
  digitalWrite(PowerLineSensors,HIGH);
  
  digitalWrite(DirectionOfEngine[1],HIGH);
  digitalWrite(DirectionOfEngine[0],HIGH);
  analogWrite(SpeedOfEngine[0],MaxVelocity);    
  analogWrite(SpeedOfEngine[1],MaxVelocity);
  
  VOfSlow = MaxVelocity;
}
void loop()
{
  /*
  Итак, идея:
  При касании одним их угловых сенсоров края, мы уезжаем от края, 
  при этом колёса той стороны, с которой считали белый сигнал
  крутятся активнее для обеспечения нужного поворота.
  */
  for(int i=0;i<4;i++){            
    if (digitalRead(ColourLineSensor[i])== HIGH){
      
      if (i == 0 or i == 1){
        digitalWrite(DirectionOfEngine[0],1);          //тут я считаю, что движение "вперёд" (так, что передние датчики - голова) - это LOW
        digitalWrite(DirectionOfEngine[1],1);
      } else {
        digitalWrite(DirectionOfEngine[0],0);
        digitalWrite(DirectionOfEngine[1],0);
      }
      
      VOfSlow = MaxVelocity/3;
      
      Slow = (i+1)%2;                                      //какой из двигателей медленнее;
      analogWrite(SpeedOfEngine[i%2],MaxVelocity);      //колёса со стороны сигналящего датчика активнее
      analogWrite(SpeedOfEngine[(i+1)%2],VOfSlow);
      flag = 1;            //нужно ли ускорять второй мотор
    }
  }
  
  if (flag == 1 && VOfSlow < MaxVelocity){            //ускорение ворого мотора
    VOfSlow++;
  } else {
    flag==0;
  }
  analogWrite(SpeedOfEngine[Slow],VOfSlow); 
}
//Все четко

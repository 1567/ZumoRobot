//Комменты будут русскими
int ColourLineSensor[2][2];    //4 наших сенсора. Первая координата - передний, задний. Вторая - левый, правый.
ColourLineSensor[0][0] = 8;
ColourLineSensor[0][1] = 9;
ColourLineSensor[1][0] = 10;
ColourLineSensor[1][1] = 11;
int PowerLineSensor=12;
int DirectionOfEngine[] = {7,4};    //левый - 0, правый - 1
int SpeedOfEngine[]={6,5};
int MaxVelocity = 153;        //не уверен, что верно помню. Поправь, если что.
int VOfSlow = 0;               //скорость более медленного колеса
boolean Slow=0;                //какой из них медленнее


void setup()
{
  pinMode(ColourLineSensor[0][0],INPUT);
  pinMode(ColourLineSensor[0][1],INPUT);
  pinMode(ColourLineSensor[1][0],INPUT);
  pinMode(ColourLineSensor[1][1],INPUT);
  pinMode(PowerLineSensor,OUTPUT);
  pinMode(DirectionOfEngine[0],OUTPUT);
  pinMode(SpeedOfEngine[0],OUTPUT);
  pinMode(SpeedOfEngine[1],OUTPUT);
  pinMode(DirectionOfEngine[1],OUTPUT);
  
  digitalWrite(PowerLineSensor,HIGH);
  
  digitalWrite(DirectionOfEngine[1],HIGH);
  digitalWrite(DirectionOfEngine[0],HIGH);
  VOfSlow = MaxVelocity;
  analogWrite(SpeedOfEngine[0],MaxVelocity);    
  analogWrite(SpeedOfEngine[1],MaxVelocity);
}
void loop()
{
  /*
  Итак, идея:
  При касании одним их угловых сенсоров края, мы уезжаем от края, 
  при этом колёса той стороны, с которой считали белый сигнал
  крутятся активнее для обеспечения нужного поворота.
  */
  //We don't need to know, where the center is, you mean?
  for(boolean i=0;i<2;i++){            // перед/зад
    for(boolean j=0;j<2;j++){          // лево/право
      if (digitalRead(ColourLineSensor[i][j])== HIGH){
        digitalWrite(DirectionOfEngine[0],i);          //тут я считаю, что движение "вперёд" (так, что передние датчики - голова) - это LOW
        digitalWrite(DirectionOfEngine[1],i);   //Is "HIGH" like "TRUE" like "1"? That is the question.
        VOfSlow = MaxVelocity/2;
        Slow = !j;                                      //какой из двигателей медленнее;
        analogWrite(SpeedOfEngine[j],MaxVelocity);      //колёса со стороны сигналящего датчика активнее
        analogWrite(SpeedOfEngine[!j],VOfSlow);
        flag = 1;            //нужно ли ускорять второй мотор
      }
    }
  }
  
  if (flag == 1 && VOfSlow < MaxVelocity){            //ускорение ворого мотора
    VOfSlow++;                  //For only 1 point?
  } else {
    flag==0;
  }
  analogWrite(SpeedOfEngine[Slow],VOfSlow); 
}

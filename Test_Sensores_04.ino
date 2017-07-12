////////////Variables del sensor de temperatura////////////////
const int SenTemp = A8;    //Pin analògico del sensor de Temperatura
float LecTemp = 0;
float Temp = 0;
float TempC = 0;

////////////Variables del sensor de humedad////////////////
const int SenHum = A10;      //Pin analògico del sensor Humedad
int LecHum = 0;
float ValHum = 0;
float Hum = 0;

int tiempo=0;
int t_ant=0;

const int ventilador = 7;                           //Se declara el ventilador en el pin digital 7

void setup() {
  Serial.begin (9600);
  pinMode(ventilador, OUTPUT);                      //Se configura el ventilador como Salida
}

void loop() {
  tiempo=millis();
  if (((tiempo-t_ant)>=3000) && ((tiempo-t_ant)<=3100)) {
      Temperatura();   
  }
  if (((tiempo-t_ant)>=8000)  && ((tiempo-t_ant)<=8100)){
        Humedad();
        t_ant=millis();
  }

  if (Temp >= 30){                                  //Si la temperatura es mayor a 30
    digitalWrite(ventilador,HIGH);                  //El ventilador se encienda
  }
  if (Temp <= 28){                                  //Si la temperatura es menor a 28
    digitalWrite(ventilador,LOW);                   //El ventilador se apaga
  }
  
}

////////////Temperatura////////////////
void Temperatura(){
  LecTemp = analogRead(SenTemp);      //Se lee los valores del sensor de temperatura
  Temp = (5.0 * LecTemp * 100)/1024.0;      //Se convierten los datos obtenidos a milivolts
  Serial.print ("Temperatura: ");       //Se muestra la temperatura
  Serial.print (Temp);
  Serial.println (" C");
}

////////////Humedad////////////////
void Humedad(){
  LecHum = analogRead (SenHum);                   //Se lee los valores del sensor ed humedad
  ValHum = (LecHum - 355) / 6.68;                 //Se obtiene el porcentaje
  Hum = map(ValHum,0,100,100,0);                  //Se invierte el porcentaje
  Serial.print("Humedad: ");                      //Se muestra la humedad
  Serial.println(Hum);
}

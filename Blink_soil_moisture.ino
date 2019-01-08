#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define SLEEP_LENGTH 100 // время сна платы в секунадх


char auth[] = "1673d8eb348847d0a3d286f665fe76e8"; //Введите свой токен аутентификации, который вы получили в приложении Blynk
char ssid[] = "ZyXEL_KEENETIC_LITE_72EF60";  //Введите имя своей сети Wi-fi
char pass[] = "0660627225";  //Введите пароль от сети
double sensorData = 0.0; 
int output_value ;
BlynkTimer timer; // Объявляем таймер

void myTimerEvent() // эта функция получает данные с платы
{
  while (Blynk.connect() == false) //цикл ожидания подключения к плате
  {
     //Wait until connected
     //Serial.print("x");
   }
  sensorData = analogRead(A0); // получение анлоговых данных с датчика
  output_value = map(sensorData,1024,0,0,100); // перевод аналоговых данных в проценты
  Serial.println(output_value); // вывод в серийный порт
  if(output_value < 10) // условие поливки цветов
  {
    Blynk.notify("Water plants!"); // отправка уведомления, при выполнении условия
  }
  Blynk.virtualWrite(V5, sensorData); // отправка аналоговых данных в Bkynk
  Blynk.virtualWrite(V6, output_value); // отправка уровня влажности почвы в процентах в Blynk
  delay(2000); // задержка перед уходом в глубокий сон
  ESP.deepSleep(SLEEP_LENGTH * 1000000); //уход платы в глубокий сон
}

void setup()
{
  Serial.begin(9600); // Можно увидеть статус подключения в серийном порту
  Blynk.begin(auth, ssid, pass); // подключение к сети и к проекту в Blynk
  timer.setInterval(1000L, myTimerEvent); // вызов функции получения данных с датчика каждую секунду по таймеру
}

void loop()
{
 Blynk.run(); // инициализация Blynk
 timer.run(); // запуск таймера

}

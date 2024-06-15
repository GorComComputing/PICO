#include "Shell.hpp"


int cmd_state(char **args) {
/*  char JSONMessage[] ="{\"SensorType\":\"Temperature\", \"Value\": 10}";
  StaticJsonDocument<300> parsed;   //Пул памяти
  // Десериализация документа JSON
  DeserializationError error = deserializeJson(parsed, JSONMessage);
  // Проверьте, удастся ли выполнить синтаксический анализ.
  if (error) {
    Serial2.println("failed!");
    return 0;
  } else {   //Вывести если ошибок нет
    const char* sensorType = parsed["SensorType"];  //Получить значение типа датчика
    int value = parsed["Value"];                    //Получить значение измерения датчика

    Serial2.print(sensorType);
    Serial2.print(": ");
    Serial2.println(value);
  }*/


  JsonDocument doc;
  String input = "{\"TempOut\":\"\","  
                  "\"TempIn\":\"\","  
                  "\"Hum\":\"\","
                  "\"Light\":\"\","
                  "\"Lat\":\"\","
                  "\"Lon\":\"\","
                  "\"Time\":\"\","
                  "\"Date\":\"\","
                  "\"Moisture\":\"\""
                  "\"Servo\":\"\""
                  "\"Led\":\"\""
                  "\"Red\":\"\""
                  "\"Yellow\":\"\""
                  "\"Green\":\"\""
                  "\"Laser\":\"\""
                  "\"Pump\":\"\""
                  "\"Display\":\"\""
                  "}";
  deserializeJson(doc, input);

  //ds18b20.selectNext();
  //double tempOut = ds18b20.getTempC();
        //tempOut *= 0.0625;                  //convert to 0.0625/LSB
  //doc["TempOut"] = String(tempOut);

  if (xht.receive(dht)) {
    doc["TempIn"] = String(dht[2]);
    doc["Hum"] = String(dht[0]);
  } else {  
    doc["TempIn"] = "error";
    doc["Hum"] = "error";  
  }

  photoresistor_val = analogRead(PHOTORESISTOR);
  doc["Light"] = String(photoresistor_val);
  
  //doc["Lat"] = lat; 
  //doc["Lon"] = lon;
  //doc["Time"] = timeGPS;
  //doc["Date"] = date;

  doc["Servo"] = String(servo_pos);
  
  if(is_LED_TEST) doc["Led"] = "ON";
  else doc["Led"] = "OFF";

  if(is_LED_RED) doc["Red"] = "ON";
  else doc["Red"] = "OFF";

  if(is_LED_YELLOW) doc["Yellow"] = "ON";
  else doc["Yellow"] = "OFF";

  if(is_LED_GREEN) doc["Green"] = "ON";
  else doc["Green"] = "OFF";

  if(is_LASER) doc["Laser"] = "ON";
  else doc["Laser"] = "OFF";
    
  String output;
  serializeJson(doc, output);
  Serial2.println(output);
	return 0;
}


int cmd_car(char **args) {
  // Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (left/right/forward/back) to \"car\"");
	} else {
    String str = args[1];    
    if (str == "left") {
      Serial2.println("Car LEFT");
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Car LEFT"); 
      digitalWrite(CAR_LEFT, LOW);
      digitalWrite(CAR_FORWARD, LOW);
      delay(car_time);
      digitalWrite(CAR_LEFT, HIGH);
      digitalWrite(CAR_FORWARD, HIGH);
	  }
    if (str == "right") {
      Serial2.println("Car RIGHT"); 
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Car RIGHT"); 
      digitalWrite(CAR_RIGHT, LOW);
      digitalWrite(CAR_FORWARD, LOW);
      delay(car_time);
      digitalWrite(CAR_RIGHT, HIGH);
      digitalWrite(CAR_FORWARD, HIGH);    
	  }
    if (str == "forward") {
      Serial2.println("Car FORWARD"); 
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Car FORWARD"); 
      digitalWrite(CAR_FORWARD, LOW);
      delay(car_time);
      digitalWrite(CAR_FORWARD, HIGH);    
	  }
    if (str == "back") {
      Serial2.println("Car BACK"); 
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Car BACK"); 
      digitalWrite(CAR_BACK, LOW);
      delay(car_time);
      digitalWrite(CAR_BACK, HIGH);    
	  }
    if (str == "bckleft") {
      Serial2.println("Car BACK LEFT");
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Car BACK LEFT"); 
      digitalWrite(CAR_LEFT, LOW);
      digitalWrite(CAR_BACK, LOW);
      delay(car_time);
      digitalWrite(CAR_LEFT, HIGH);
      digitalWrite(CAR_BACK, HIGH);
	  }
    if (str == "bckright") {
      Serial2.println("Car BACK RIGHT"); 
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Car BACKRIGHT"); 
      digitalWrite(CAR_RIGHT, LOW);
      digitalWrite(CAR_BACK, LOW);
      delay(car_time);
      digitalWrite(CAR_RIGHT, HIGH);
      digitalWrite(CAR_BACK, HIGH);    
	  }
	}
	return 1;
}


/*int cmd_gps(char **args) {
  String str = args[1]; 
  if (str == "time") {
    gps.read();
    if(!gps.errTim){ 
      lcd.Cursor(2, 0); 
      char time[5];
      sprintf(time, "%02d:%02d", gps.Hours, gps.minutes);
      Serial2.println(time);
    } else {
      Serial2.println("error");
    }
    return 0;     
	}
  if (str == "date") {
    gps.read();
    if(!gps.errDat){        
      char date[5];
      sprintf(date, "%02d.%02d.%02d", gps.day, gps.month, gps.year);
      Serial2.println(date);
    } else {
      Serial2.println("error");
    }
    return 0;     
	}
  if (str == "lat") {
    gps.read();
    if(gps.errPos){                              
      Serial2.println("error"); 
      return 0;                        
    }
    char lat[15];
    sprintf(lat, "%05f", gps.latitude);
    Serial2.println(lat);
    return 0;     
	}
  if (str == "lon") {
    gps.read();
    if(gps.errPos){                              
      Serial2.println("error"); 
      return 0;                        
    }
    char lon[15];
    sprintf(lon, "%05f", gps.longitude);
    Serial2.println(lon);
    return 0;     
	}

  Serial2.println("GPS");

  is_TEMP_OUT = false;
  is_TEMP_IN = false;
  is_HUM = false;
  is_PHOTORESISTOR = false;
  is_SERVO = false;

  gps.read();                                 
  if(gps.errPos){                              
    Serial.println("Координаты недостоверны");                        
  }              
  lcd.Clear();
  lcd.Cursor(0, 0); 
  char latitude[20];
  sprintf(latitude, "Lat: %05f°", gps.latitude);
  lcd.Display(latitude);   
  lcd.Cursor(1, 0); 
  char longitude[20];
  sprintf(longitude, "Lon: %05f°", gps.longitude);
  lcd.Display(longitude);                           

  if(gps.errCrs){                              
    Serial.println("Скорость недостоверна");                         
  }                                            
  Serial.print("Скорость: "); Serial.print(gps.speed ); Serial.print("км/ч. ");
  Serial.print("Курс: "    ); Serial.print(gps.course); Serial.print("°.\r\n");

  if(!gps.errTim){ 
    lcd.Cursor(2, 0); 
    char time[5];
    sprintf(time, "%02d:%02d", gps.Hours, gps.minutes);
    lcd.Display(time);                               
    //Serial.print(gps.Hours  ); Serial.print(":"); //  Час.
    //Serial.print(gps.minutes); Serial.print(":"); //  Минуты.
    //Serial.print(gps.seconds); Serial.print(" "); //  Секунды.
    if(gps.Hours + hour_add == 24) real_time = 0;
    if(gps.Hours + hour_add > 24) real_time = gps.Hours + hour_add - 24;
    if(gps.Hours + hour_add < 24) real_time = gps.Hours + hour_add;
    item = real_time*100 + gps.minutes;
    tm_4display.displayString(item);
  } else {
    item = 8888;
    tm_4display.displayString(item);
  }                                               

  if(!gps.errDat){        
    lcd.Cursor(3, 0); 
    char date[5];
    sprintf(date, "%02d.%02d.%02d", gps.day, gps.month, gps.year);
    lcd.Display(date);                        
    //Serial.print(gps.day  ); Serial.print(".");   //  День.
    //Serial.print(gps.month); Serial.print(".");   //  Месяц.
    //Serial.print(gps.year ); Serial.print("г. "); //  Год.
    //   Выводим название дня недели:                  
    //Serial.print("(");                            
    //Serial.print(wd[ gps.weekday ]);              
    //Serial.print(") ");                           
    //   Выводим UnixTime:                             
    //Serial.print("UnixTime: ");                   
    //Serial.print(gps.Unix);                       
  }                                               
  //   Завершаем строку:                             
  //Serial.print("\r\n");
	return 0;
}
*/
/*
int cmd_tempOut(char **args) {
  ds18b20.selectNext();
  double tempOut = ds18b20.getTempC();
  //tempOut *= 0.0625;                  //convert to 0.0625/LSB
  char msg[20];
  sprintf (msg, "Temp Out: %dC", tempOut); 
  Serial2.print(msg);
    
  lcd.Clear();
  lcd.Cursor(0, 0); 
  lcd.Display(msg);

  item = tempOut; 
  tm_4display.displayString(item);

  is_TEMP_OUT = true;
  is_TEMP_IN = false;
  is_HUM = false;
  is_PHOTORESISTOR = false;
  is_SERVO = false;
  return 0;
}*/


int cmd_tempIn(char **args) {
  if (xht.receive(dht)) {
    String str = args[1]; 
    if (str == "is") {
      Serial2.println(dht[2]);
      return 0;     
	  } 
    char msg[20];
    sprintf (msg, "Temp: %dC", dht[2]); //The integer part of the temperature, dht[3] is the fractional part
    Serial2.print(msg);
    
    lcd.Clear();
    lcd.Cursor(0, 0); 
    lcd.Display(msg);

    item = dht[2]; 
    tm_4display.displayString(item);

    is_TEMP_OUT = false;
    is_TEMP_IN = true;
    is_HUM = false;
    is_PHOTORESISTOR = false;
    is_SERVO = false;
  } else {    
    Serial2.println("XHT11 error");

    lcd.Clear();
    lcd.Cursor(0, 0); 
    lcd.Display("XHT11 error");

    item = 8888;
    tm_4display.displayString(item);
  }
	return 0;
}


int cmd_hum(char **args) {
  if (xht.receive(dht)) {
    String str = args[1];
    if (str == "is") {
      Serial2.println(dht[0]);
      return 0;     
	  } 
    char msg[20];
    sprintf(msg, "Humidity: %d%%", dht[0]); //The integer part, dht[1] is the fractional part
    Serial2.print(msg);
    
    lcd.Clear();
    lcd.Cursor(0, 0); 
    lcd.Display(msg);

    item = dht[0]; 
    tm_4display.displayString(item);

    is_TEMP_OUT = false;
    is_TEMP_IN = false;
    is_HUM = true;
    is_PHOTORESISTOR = false;
    is_SERVO = false;
  } else {    
    Serial2.println("XHT11 error");

    lcd.Clear();
    lcd.Cursor(0, 0); 
    lcd.Display("XHT11 error");

    item = 8888;
    tm_4display.displayString(item);
  }
	return 0;
}


int cmd_photoresistor(char **args) {
  String str = args[1];
  if (str == "is") {
    Serial2.println(photoresistor_val);
    return 0;     
	}
  photoresistor_val = analogRead(PHOTORESISTOR);
  char msg[20];
  sprintf(msg, "Light: %d%%", photoresistor_val); 
  Serial2.print(msg);

  lcd.Clear();
  lcd.Cursor(0, 0); 
  lcd.Display(msg);

  item = photoresistor_val; 
  tm_4display.displayString(item);

  is_TEMP_OUT = false;
  is_TEMP_IN = false;
  is_HUM = false;
  is_PHOTORESISTOR = true;
  is_SERVO = false;
	return 0;
}


int cmd_servo(char **args) {
  // Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (num) to \"servo\"");
	} else {
    String str = args[1];
    if (str == "is") {
      Serial2.println(servo_pos);
      return 0;     
	  }
    //String str = args[1];
    servo_pos = dec_str_to_number(args[1]);
    if(servo_pos < 30) servo_pos = 30;
    if(servo_pos > 180) servo_pos = 180;
    char msg[20];
    sprintf(msg, "Servo: %d", servo_pos); 
    Serial2.print(msg);

    lcd.Clear();
    lcd.Cursor(0, 0); 
    lcd.Display(msg);

    item = servo_pos; 
    tm_4display.displayString(item);

    is_TEMP_OUT = false;
    is_TEMP_IN = false;
    is_HUM = false;
    is_PHOTORESISTOR = false;
    is_SERVO = true;
    myservo.write(servo_pos);
	}
	return 0;
}


int cmd_wait(char **args) {
  // Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (1000) to \"wait\"");
	} else {   
    Serial2.print("Waiting: ");
    Serial2.print(args[1]);
    delay(dec_str_to_number(args[1]));
    Serial2.println(" DONE");
	}
	return 0;
}


// Команда включения светодиода
int cmd_led(char **args) {
	// Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (on/off) to \"led\"");
	} else {
    String str = args[1];    
    if (str == "on") {
      is_LED_TEST = true;  				
      digitalWrite(LED_TEST, HIGH);
      Serial2.println("Led ON");
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Led ON"); 
	  }
    if (str == "off") {
      is_LED_TEST = false;  				
      digitalWrite(LED_TEST, LOW);
      Serial2.println("Led OFF"); 
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Led OFF");     
	  }
    if (str == "is") {
      if(is_LED_TEST) Serial2.println("ON");
      else Serial2.println("OFF");     
	  }
	}
	return 1;
}


int cmd_laser(char **args) {
	// Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (on/off) to \"laser\"");
	} else {
    String str = args[1];    
    if (str == "on") {
      is_LASER = true;  				
      digitalWrite(LASER, HIGH);
      Serial2.println("Laser ON");
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Laser ON"); 
	  }
    if (str == "off") {
      is_LASER = false;  				
      digitalWrite(LASER, LOW);
      Serial2.println("Laser OFF"); 
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Laser OFF");     
	  }
    if (str == "is") {
      if(is_LASER) Serial2.println("ON");
      else Serial2.println("OFF");     
	  }
	}
	return 1;
}


int cmd_led_green(char **args) {
	// Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (on/off) to \"green\"");
	} else {
    String str = args[1];    
    if (str == "on") {
      is_LED_GREEN = true;  				
      digitalWrite(LED_GREEN, HIGH);
      Serial2.println("Green ON");
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Green ON"); 
	  }
    if (str == "off") {
      is_LED_GREEN = false;  				
      digitalWrite(LED_GREEN, LOW);
      Serial2.println("Green OFF"); 
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Green OFF");     
	  }
    if (str == "is") {
      if(is_LED_GREEN) Serial2.println("ON");
      else Serial2.println("OFF");     
	  }
	}
	return 1;
}


int cmd_led_yellow(char **args) {
	// Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (on/off) to \"yellow\"");
	} else {
    String str = args[1];    
    if (str == "on") {
      is_LED_YELLOW = true;  				
      digitalWrite(LED_YELLOW, HIGH);
      Serial2.println("Yellow ON");
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Yellow ON"); 
	  }
    if (str == "off") {
      is_LED_YELLOW = false;  				
      digitalWrite(LED_YELLOW, LOW);
      Serial2.println("Yellow OFF"); 
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Yellow OFF");     
	  }
    if (str == "is") {
      if(is_LED_YELLOW) Serial2.println("ON");
      else Serial2.println("OFF");     
	  }
	}
	return 1;
}


int cmd_led_red(char **args) {
	// Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (on/off) to \"red\"");
	} else {
    String str = args[1];    
    if (str == "on") {
      is_LED_RED = true;  				
      digitalWrite(LED_RED, HIGH);
      Serial2.println("Red ON");
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Red ON"); 
	  }
    if (str == "off") {
      is_LED_RED = false;  				
      digitalWrite(LED_RED, LOW);
      Serial2.println("Red OFF"); 
      lcd.Clear();
      lcd.Cursor(0, 0); 
      lcd.Display("Red OFF");     
	  }
    if (str == "is") {
      if(is_LED_RED) Serial2.println("ON");
      else Serial2.println("OFF");     
	  }
	}
	return 1;
}


// Команда help
int cmd_help(char **args) {
	int i;
  Serial2.println("Basic v.1.0 (c) 2022 Gor.Com");
	Serial2.println("The following command are built in:");
   
	// Выводим массив имен встроенных команд
	for (i = 0; i < num_builtins(); i++) {
		Serial2.println(cmd_str[i]);    
	}
	return 1;
}


// Команда вывода на экран программы
int cmd_list(char **args) {
    // Служебный вывод программы
    for(int i = 0; i < MAX_LINE; i++){
      if(program[i*20] != 0x0D){ 
        Serial2.print(i+1);
        Serial2.print(" ");       
      }

      for(int j = 0; j < MAX_LENGTH; j++){
        if(program[i*20 + j] != 0x0D){        
          Serial2.print(program[i*20 + j]);
        }
      }
      if(program[i*20] != 0x0D){ 
        Serial2.println("");
      }        
    }
	return 0;
}


// Команда выполнения программы
int cmd_run(char **args) {
    for(int i = 0; i < MAX_LINE; i++){
      line[0] = 0;
      for(int j = 0; j < MAX_LENGTH; j++){
        if(program[i*20 + j] != 0x0D){
          line[j] = program[i*20 + j];       // Копируем строку из программы для выполнения      
        }
      }
      // execute str
      if(line[0]){
        args = split_line(line);  // Извлекает аргументы
        execute(args, line);      // Исполняем команду  
      }    
        
    }
	return 0;
}


// Команда PRINT
int cmd_print(char **args) {
  if(args[1] == NULL){
    return 0;
  }
  if(args[1][0] == 34){
    for(int i = 1; i < 20; i++){
      if(args[1][i] == 34 || args[1][i] == 0x0D || args[1][i] == 0x20 || args[1][i] == 0){
        if(args[1][i] == 34 && args[1][i+1] != 0x3B){    
          Serial2.println(""); 
        }
        break;
      } 
      Serial2.print(args[1][i]);  
    }
    
    return 0;
  }

  Serial2.println(process_expr());
	return 0;
}


// Команда очистки программы
int cmd_new(char **args) {
  running = 0;
  start_bas();
	return 0;
}


// Команда ввода переменной
int cmd_input(char **args) {
  Serial2.print("?");
  while(Serial2.available()==0);  //Ожидаем ввода данных
  // Вычисляем адрес по букве
  vars[args[1][0] - 97] = process_expr();//Serial.read();

  // Служебный вывод
  for(int i = 0; i < 26; i++){
    Serial2.print(vars[i]);   
  } 
  Serial2.println("");  
  
	return 0;
}
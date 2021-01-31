void sens_data()
{

/***** Ultrasonic-CurrentLogic *****/
//  ping();
  
/***** Ultrasonic-PreviousLogic *****
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2; */

/***** BMP/DHT Sensor Logic *****
  h_dht = dht.readHumidity();
  t_dht = dht.readTemperature();
  
  if (isnan(h_dht) || isnan(t_dht)) {
    h_dht = -1;
    t_dht = -1;
  }

  //a_bmp = bmp.readAltitude();
  a_bmp = -1;
  
  //t_bmp = bmp.readTemperature();/


/***** Weight Sensor Logic *****/
//  weight = get_weight();

   
/***** Test Variables *****/
  test1++;
  test2++;
  test3++;
  test4++;
  
  //mydata = "$"+String(h_dht)+","+String(t_dht)+"!"+String(t_bmp)+","+String(a_bmp);
  mydata = "$"+String(test1)+","+String(test2)+"!"+String(test3)+"@,"+String(test4);

  
  mydata.toCharArray(payload, 80);
  Serial.println(payload);

  delay(2000);
}

void ping() {
  int avg = 0;
  for (int i=0;i<10;i++) {
    int temp = readSerial();
    
    if (temp >= 220 || temp <= 0) { i = i -1;}
    else { avg = avg + temp; }
}
  distance = avg/10;
  Serial.print(distance);Serial.println(" in. ");
}

int readSerial() {
  byte serialData[5];
  int discalc;
  
  while (Serial2.available()) {
    byte b = Serial2.read();
  }
  
  Serial2.setTimeout(95);
  
  if( Serial2.readBytes(serialData,4) > 0) {
    discalc = ((serialData[1] * 256) + serialData[2]);
    discalc = (discalc * (1/25.4)); //distance is returned from sensor in mm - this will convert to inches.
  }
  return discalc;
}

float get_weight() {
  
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down();              // put the ADC in sleep mode
  delay(5000);
  scale.power_up();

  return scale.get_units(10);
}

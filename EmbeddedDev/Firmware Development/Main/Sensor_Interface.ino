void sens_data()
{

/***** Inclinometer Logic *****
  inclino_data();/

  
/***** Ultrasonic-NewLogic *****/
//  son_ping();
  
/***** Ultrasonic-PreviousLogic *****
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2; */

/***** BMP/DHT Sensor Logic *****/
  h_dht = dht.readHumidity();
  //t_dht = dht.readTemperature();
  
  if (isnan(h_dht)) {
    h_dht = -1;
  }

  a_bmp = bmp.readAltitude();
  t_bmp = bmp.readTemperature();


/***** Weight Sensor Logic *****
  weight = get_weight();*/

   
/***** Test Variables ****
  test1++;
  test2++;
  test3++;
  test4++;*/
  
  
  //mydata = "$"+String(h_dht)+","+String(t_dht)+"!"+String(t_bmp)+","+String(a_bmp);
  mydata = "$"+String(test1)+","+String(test2)+"!"+String(test3)+"@,"+String(test4);

  
  mydata.toCharArray(payload, 80);
  //Serial.println(payload);

  delay(10);
}

void son_ping() {
  
  delay(50); 
  Serial.print("Distance = "); // Measure distance and print to the Serial Monitor:
  //float distance = sonar.ping_cm(); // Send ping, get distance in cm and print result (0 = outside set distance range):

  for (int x = 0; x <10; x++) {
    distance = distance + sonar.ping_in(); // Send ping, get distance in inches and print result (0 = outside set distance range):
  }
  distance /= 10;

  Serial.print(distance); 
  Serial.println(" inch");
}

//float get_weight() {
//  
//  Serial.print("one reading:\t");
//  Serial.print(scale.get_units(), 1);
//  Serial.print("\t| average:\t");
//  Serial.println(scale.get_units(10), 1);
//
//  scale.power_down();              // put the ADC in sleep mode
//  delay(5000);
//  scale.power_up();
//
//  return scale.get_units(10);
//}

void inclino_data() {
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  aX = a.acceleration.x;
  aY = a.acceleration.y;
  aZ = a.acceleration.z;

  gX = g.gyro.x;
  gY = g.gyro.y;
  gZ = g.gyro.z;
}

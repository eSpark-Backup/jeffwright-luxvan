void sens_data()
{

/***** Inclinometer Logic *****
  inclino_data();/

  
/***** Ultrasonic-NewLogic *****/
  son_ping();
  
/***** Ultrasonic-PreviousLogic *****
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2; */

/***** BMP/DHT Sensor Logic *****/
  //h_dht = dht.readHumidity();
  //t_dht = dht.readTemperature();
  
  if (!(isnan(h_dht))) {
    h_dht = dht.readHumidity();
  }
  else {
    h_dht = -1;
  }

  if (stat1) {
    a_bmp = bmp.readAltitude();
    t_bmp = bmp.readTemperature();
  }


/***** Weight Sensor Logic *****
  weight = get_weight();*/

   
/***** Test Variables ****
  test1++;
  test2++;
  test3++;
  test4++;*/
  
  
  //mydata = "$"+String(h_dht)+","+String(t_dht)+"!"+String(t_bmp)+","+String(a_bmp);
  mydata = String(t_bmp)+"a,"+String(distance)+"b,"+String(h_dht)+"c,"+String(a_bmp)+"d,"+
           String(aX)+"xe,"+String(aY)+"ye,"+String(aZ)+"ze";

  
  mydata.toCharArray(payload, 80);
  Serial.println(payload);

  delay(300);
}

void son_ping() {
  
  delay(50); 
  float value = sonar.ping_in(); // Send ping, get distance in cm and print result (0 = outside set distance range):
  if (value > 0.00) {
    dist = value;
  }

  distance = map(dist, 9, 19, 18, 1); 
  

//  for (int x = 0; x <10; x++) {
//    float value = sonar.ping_in(); // Send ping, get distance in inches and print result (0 = outside set distance range):
//    if (value > 0) {
//      distance += value;
//    }
//  }
//  distance /= 10;

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

//void inclino_data() {
//  
//  sensors_event_t a, g, temp;
//  mpu.getEvent(&a, &g, &temp);
//
//  aX = a.acceleration.x;
//  aY = a.acceleration.y;
//  aZ = a.acceleration.z;
//
//  gX = g.gyro.x;
//  gY = g.gyro.y;
//  gZ = g.gyro.z;
//}

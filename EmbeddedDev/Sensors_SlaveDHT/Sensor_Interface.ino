void sens_data()
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);


  distance= duration*0.034/2;

  
//  h_dht = dht.readHumidity();
  t_dht = dht.readTemperature();
//  if (isnan(h_dht) || isnan(t_dht)) {
//    Serial.println(F("Failed to read from DHT sensor!"));
//  }
//

//  t_bmp = bmp.readTemperature();
  
//  a_bmp = bmp.readAltitude();
//  a_bmp = -a_bmp;

  test1++;
  test2++;
  test3++;
  test4++;
  
  //mydata = "$"+String(h_dht)+","+String(t_dht)+"!"+String(t_bmp)+","+String(a_bmp);
  mydata = "$"+String(t_dht)+","+String(distance)+"!";

  
  mydata.toCharArray(payload, 80);
  Serial.println(payload);

  delay(2000);
}

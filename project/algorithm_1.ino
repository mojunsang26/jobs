void setup() {
  writeLCD("등록 대기");
  while(Lora.available()>0)
  {
    Dest = Lora.read();
    writeLCD("등록 완료");
    break;
  }  
}

void loop() {
  CurrGPS = readGPS();
  if(Dist(Dest,CurrGPS) < DISTANCE)
  {
    writeBluetooth( DestPoint );
    writeLCD( RED );
  }

  writeLora( CurrGPS );
  delay(1000);
  
}

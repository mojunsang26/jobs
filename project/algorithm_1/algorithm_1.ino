/*----- 집하 ------*/
/* IoT device를 실행시키고 LCD에 "등록 대기"가 출력되면 택배 기사는 PDA단말기로 바코드를 스캔하고 스캔한 정보는 택배사 서버와 Lora를 통해 등록 대기중인 IoT device로 전송된다. */
void setup() {
  writeLCD("등록 대기");
  while(Lora.available()>0)
  {
    Dest = Lora.read();
    writeLCD("등록 완료");
    break;
  }
}


/*-----------집하->거점 or 거점->거점---------*/
/* GPS수집만 시행 */
  void loop(){
    currGPS = readGPS();
    if(currGPS == false) /* GPS신호 미약 */
    {
      /* 와이파이를 통한 위치정보 수집 */
      ??????

      if(currGPS == false)/* 와이파이신호 미약 */
      {
        /* Bluetooth를 통한 위치정보 수집 */
        ??????
      }
    }
    Lora.write( currGPS );
    delay(1000);

    if(Lora.available() > 0){
      break;   /* 마지막 거점에서 하차할 경우 택배기사의 단말기로 스캔할 때 IoT device로 신호 전송 */
    }
  }


  /*----------마지막 거점-------*/

  

  /*하나의 트럭 단위로 분류된 택배들의 바코드정보 택배사 서버에서 수집*/
   ????
   
  /*거리별 군집화*/
   ????
   
  /*경로 알고리즘에 다른 거리 순으로 군집 정렬*/
   ????
   
  /*가장 먼 군집의 물류id들로 signal 전송(Lora)*/
  while(Lora.available()>0)
  {
    sign = Lora.read();
    if( sign == true ){  /*signal받은 물류 lcd 불 출력*/
      writeLCD( RED );
    }
    break;
  }

  /*RED 출력된 택배들 택배 바코드 찍고 상차*/
  while(Lora.available()>0)
  {
    sign = Lora.read();
    if(sign == true){
      writeLCD( NULL );      
    }
    break;
  }
  /*상차 완료*/
  Lora.write( 상차 완료 신호 , 물류 정렬 프로그램 );



  /*--------마지막거점 -> 최종 목적지 -------*/
  void loop(){
    currGPS = readGPS();
    if(currGPS == false) /* GPS신호 미약 */
    {
      /* 와이파이를 통한 위치정보 수집 */
      ????????

      if(currGPS == false)/* 와이파이신호 미약 */
      {
        /* Bluetooth를 통한 위치정보 수집 */
        ????????
      }
    }


 /*--------최종 목적지 도착----------*/
    if( dist(currGPS, Dest) < 오차범위 )  /* 최종 목적지에 도착하면 하차할 물류의 device에 빨간불 출력 */
    {
      writeLCD( RED );
      break;
    }
    Lora.write( currGPS );

    delay(1000);
  }
    
 
  while(Lora.available()>0)   /* 택배 기사가 하차할(RED 출력된) 물류의 바코드 스캔하면 PDA단말기로 부터 iot device로 Lora를 통해 signal 전송 */
  {
    sign = Lora.read();
    if(sign == true)
    {
      초기화;
    }
  }
  /* IoT device 회수 */


#include <SoftwareSerial.h>
int rx=3, tx=2;
int real_time[2];
String w1, w2, w3, w4, w5, w6, w7, w8, w9;
SoftwareSerial esp(tx,rx);

void reset_esp();
void write_AP();
String get_api_data();

void setup() 
{
  Serial.begin(9600);
  esp.begin(115200);
  reset_esp();
  get_real_time(real_time);
}
void loop() 
{
  get_real_time(real_time);
  Serial.print(real_time[0]);
  Serial.print(":");
  Serial.println(real_time[1]);
  if(real_time[0]==0 &&(real_time[1]>1 && real_time[1]<25))
  {
    int ct1=0,ct2=0,ct3=0,ct4=0,ct5=0,ct6=0,ct7=0,ct8=0,ct9=0, cl;
    w1=get_api_data("X4Z986RR9LP94C1X",'n');
    w2=get_api_data("2R67BO0P0A6ZCH4Q",'n');
    w3=get_api_data("BJAV889JX4DTPJXK",'n');
    w4=get_api_data("BSKW8MN3056HTGJP",'y');
    w5=get_api_data("X0XQWA8AXQBX7IWH",'y');
    w6=get_api_data("LQR141UEX66I8QZE",'y');
    w7=get_api_data("HM2WU1GNR0LAZH9M",'n');
    w8=get_api_data("842IYWUEFVM01FYG",'n');
    w9=get_api_data("R4TWRP0QTEDOOQ90",'n');
    while(w1=="NULL" && ct1<5)
    {
      w1=get_api_data("X4Z986RR9LP94C1X",'n');
    }
    while(w2=="NULL" && ct2<5)
    {
      w2=get_api_data("2R67BO0P0A6ZCH4Q",'n');
      ct2++;
    }
    while(w3=="NULL" && ct3<5)
    {
      w3=get_api_data("BJAV889JX4DTPJXK",'n');
      ct3++;
    }
    while(w4=="NULL" && ct4<5)
    {
      w4=get_api_data("BSKW8MN3056HTGJP",'y');
      ct4++;
    }
    while(w5=="NULL" && ct5<5)
    {
      w5=get_api_data("X0XQWA8AXQBX7IWH",'y');
      ct5++;
    }
    while(w6=="NULL" && ct6<5)
    {
      w6=get_api_data("LQR141UEX66I8QZE",'y');
      ct6++;
    }
    while(w7=="NULL" && ct7<5)
    {
      w7=get_api_data("HM2WU1GNR0LAZH9M",'n');
      ct7++;
    }
    while(w8=="NULL" && ct8<5)
    {
      w8=get_api_data("842IYWUEFVM01FYG",'n');
      ct8++;
    }
    while(w9=="NULL" && ct9<5)
    {
      w9=get_api_data("R4TWRP0QTEDOOQ90",'n');
      ct9++;
    }
  }
  /*Serial.println(w1);
  Serial.println(w2);
  Serial.println(w3);
  Serial.println(w4);
  Serial.println(w5);
  Serial.println(w6);
  Serial.println(w7);
  Serial.println(w8);
  Serial.println(w9);*/
  
}
void reset_esp()
{
  write_AT("AT+RST\r\n", "ready");
  write_AT("AT+CWQAP\r\n", "OK"); 
  write_AT("AT+CWMODE=1\r\n", "OK");
  write_AT("AT+CWJAP=\"NOVA_2.4\",\"iamkaran\"\r\n","OK");
}
void get_real_time(int a[])
{
  write_AT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n","OK");
  esp.print("AT+CIPSEND=90\r\n");
  String api_url="GET /apps/thinghttp/send_request?api_key=0R6L2ENR78AQR5L4\r\n";
  api_url+="Host:api.thingspeak.com";
  api_url+="\r\n\r\n\r\n\r\n";
  String data="";
  esp.print(api_url);
  long int gold=millis();
  while((gold+5000)>millis())
  {
    while(esp.available())
    {
      char ch=esp.read();
      data+=ch;
    }
  }
  int hour,minu;
  for(int i=0;i<data.length();i++)
  {
    if(data[i]=='T' && data[i-1]!='A' && data[i+3]==':')
      {
        hour=data[i+1]-'0';
        hour*=10;
        hour+=data[i+2]-'0';
        a[0]=hour;
        minu=data[i+4]-'0';
        minu*=10;
        minu+=data[i+5]-'0';
        a[1]=minu;
        break;
      }
  }
}
void write_AT(String command, char rec[]) 
{
  bool flag=false;
  for(int i=0;i<10;i++)
  {
    esp.print(command);
    if(esp.find(rec))
    {
      Serial.print("Done With ");
      Serial.println(command);
      flag=true;
      break;
    }
  }
  if(flag==false)
  {
    Serial.print("Error with ");
    Serial.println(command);
  }
}

String get_api_data(String key, char chr)
{
  write_AT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n","OK");
  esp.print("AT+CIPSEND=90\r\n");
  String api_url="GET /apps/thinghttp/send_request?api_key=";
  api_url+=key;
  api_url+="\r\nHost:api.thingspeak.com";
  api_url+="\r\n\r\n\r\n\r\n";
  String data="";
  esp.print(api_url);
  delay(100);
  long int gold=millis();
  while((gold+12000)>millis())
  {
    while(esp.available())
    {
      char ch=esp.read();
      data+=ch;
    }
  }
  //+IPD,61:<span class="DetailsSummary--extendedData--aaFdV">Clear</>
  String weather=extract_weather(data, chr);
  return weather;
}
String extract_weather(String data, char ch)
{
  String weather="";
  for(int i=(data.length()-1);i>-1;i--)
  {
    if(data[i]=='>' && data[i-1]=='"' && data[i-2]=='V')
    {
      for(int j=i+1;j<data.length();j++)
        weather+=data[j];
      break;
    }
  }
  if(weather[0]=='C')
  {
    String clear_w="Clear            ", cloudy_w="Cloudy            ";
    int ct1=0,ct2=0;
    for(int i=0;i<weather.length();i++)
    {
      if(weather[i]==clear_w[i])
        ct1++;
      else if(weather[i]==cloudy_w[i])
        ct2++;
    }
    if(ct1>ct2)
      return "Clear";
    else if(ct1<ct2)
      return "Cloudy";
    else 
      return "NULL";
  }
  else if(weather[0]=='S')
  {
    String clear_w="Sunny            ", cloudy_w="Showers            ";
    int ct1=0,ct2=0;
    for(int i=0;i<weather.length();i++)
    {
      if(weather[i]==clear_w[i])
        ct1++;
      else if(weather[i]==cloudy_w[i])
        ct2++;
    }
    if(ct1>ct2)
      return "Sunny";
    else if(ct1<ct2)
      return "Showers";    
    else
      return "NULL";
  }
  else if(weather[0]=='R' && weather[1]=='a')
    return "Rain";
  else if(weather[0]=='M')
  {
    if(ch=='y')
    {
      String most_s_w="Mostly Sunny             ", most_c_w="Mostly Cloudy             ";
      int ct1=0,ct2=0;
      for(int i=0;i<weather.length();i++)
      {
          if(weather[i]==most_s_w[i])
           ct1++;
         else if(weather[i]==most_c_w[i])
          ct2++;
      }
      if(ct1>ct2)
        return "Mostly Sunny";
      else if(ct1<ct2)
        return "Mostly Cloudy";    
      else
        return "NULL";
    }
    else if(ch=='n')
    {
      String most_y_w="Mostly Cloudy             ", most_r_w="Mostly Clear             ";
      int ct1=0,ct2=0;
      for(int i=0;i<weather.length();i++)
      {
          if(weather[i]==most_y_w[i])
           ct1++;
         else if(weather[i]==most_r_w[i])
          ct2++;
      }
      if(ct1>ct2)
        return "Mostly Cloudy";
      else if(ct1<ct2)
        return "Mostly Clear";    
      else
        return "NULL";
    }
  }
  else if(weather[0]=='F')
    return "Few Showers";
  else if(weather[0]=='P')
    return "Partly Cloudy";
  else if(weather[0]=='L')
    return "Light Rain";
  else if(weather[0]=='H')
    return "Heavy Rain";
  else 
    return "NULL";
}

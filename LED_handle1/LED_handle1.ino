
#include<ESP8266WiFi.h>
#include<ESP8266WiFiMulti.h>
#include<ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;       //建立ESP8266WiFiMulti的对象，对象名为wifiMulti
ESP8266WebServer esp8266_server(80);  //建立ESP8266WebServer的对象，对象名为esp8266_server;这里表明设置ESP8266为服务器

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //启动串口监视

  pinMode(LED_BUILTIN,OUTPUT);    //使能LED管脚

  //在这里输入你的WiFi名字和密码
  wifiMulti.addAP("HONOR V30 PRO","12345678");      //启动连接wifi
  wifiMulti.addAP("taichi-maker","12345678"); 
  Serial.println("Connecting ..."); 

  int i =0;
  while(wifiMulti.run() != WL_CONNECTED){     //判断wifi是否连接成功

    delay(1000);
    Serial.print(i++);
    Serial.print(' ');
  }

  //wifi连接成功后的串口信息
  Serial.println('\n');
  Serial.print("Connected to");
  Serial.println(WiFi.SSID());        //WiFi.SSID()函数表示连接WiFi的名字
  Serial.print("IP Adress is:");
  Serial.println(WiFi.localIP());     //WiFi.localIP()函数表示连接WiFi的IP地址

  //开始启动网络服务程序
  esp8266_server.begin();
  esp8266_server.on("/",HTTP_GET,handleRoot);     //起始页面
  esp8266_server.on("/LED",HTTP_POST,handleLED);  //跳转到这个页面控制电灯
  esp8266_server.onNotFound(handleNotFound);      //跳转失败页面


  Serial.println("HTTP esp8266_server started");//  告知用户ESP8266网络服务功能已经启动
}

void loop() {
  // put your main code here, to run repeatedly:
  esp8266_server.handleClient();      // 处理http服务器访问，它的主要作用之一是检查有没有设备通过网络向NodeMCU发送请求 
}

//server响应中调用的各个函数
void handleRoot(){      //让页面显示Toggle Led按键，点击按钮将会跳转/LED页面
  
  esp8266_server.send(200,"text/html","<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
  
}

void handleLED(){

  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));    //当小灯为低电平时使其变高，当小灯为高电平时使其变低，从而控制小灯的亮灭
  esp8266_server.sendHeader("Location","/");              //跳转回页面的根目录
  esp8266_server.send(303);                               // 发送Http相应代码303 跳转 
  
}

void handleNotFound(){

  esp8266_server.send(404,"text/plain","Connected unsuccessed,please try again.");
}

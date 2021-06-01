#define BLINKER_WIFI

#include <Blinker.h>

char auth[] = "1d342a77a600";
char ssid[] = "HONOR V30 PRO";
char pswd[] = "12345678";

// 新建组件对象
BlinkerButton Button1("btn-abc");

//服务器中返回值为on 和 off来控制台灯亮灭
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    if (state=="on") {
        digitalWrite(D0, LOW);
        // 反馈开关状态
        Button1.print("on");
    } else if(state=="off"){
        digitalWrite(D0, HIGH);
        // 反馈开关状态
        Button1.print("off");
    }
}


void setup() {
    // 初始化串口，并开启调试信息
    Serial.begin(115200);    
    BLINKER_DEBUG.stream(Serial);
    // 初始化有LED的IO
    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
}

void loop() {
    Blinker.run();
}

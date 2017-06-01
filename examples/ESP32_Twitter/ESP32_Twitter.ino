#include <WiFi.h>
#include <Stewitter-ESP32.h>

#define WIFI_SSID "your_AP_ssid"
#define WIFI_PASS "your_AP_password"

Stewitter twitter("your_token");
char msg[] = "Hello, World! I'm Arduino!";

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  Serial.print("Connect to SSID: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connection success");
}

void loop() {
  // msgのツイート
  tweet(msg);
  // 最後のメンションの取得
  getMention();
  delay(1000 * 60);
}

bool getMention() {
  // 最後のメンションがあるか確認
  if (twitter.lastMention()) {
    // 完了を待つ
    int status = twitter.wait();
    // status が 200なら正常に完了
    if (status == 200) {
      // 最後のメンションを表示
      Serial.println(twitter.response());
      return true;
    }
    else {
      Serial.print("failed : code ");
      Serial.println(status);
      return false;
    }
  }
  else {
    Serial.println("connection failed.");
    return false;
  }
}

bool tweet(char *msg) {
  // twitterに接続して、メッセージを送信
  if (twitter.post(msg)) {
    // 完了を待つ
    int status = twitter.wait();
    // status が 200なら正常に完了
    if (status == 200) {
      // レスポンスを表示
      Serial.println(twitter.response());
      return true;
    }
    else {
      Serial.print("failed : code ");
      Serial.println(status);
      return false;
    }
  }
  else {
    Serial.println("connection failed.");
    return false;
  }
}

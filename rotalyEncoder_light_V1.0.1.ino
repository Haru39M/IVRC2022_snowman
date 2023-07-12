#define sPin A0
#define THR 40
int curr_sense_val, dist_sense_val, count, min_sense_val, max_sense_val;
/*
   ホイールに取り付けたセンサ用ホイールの回転量を取得してシリアル出力するプログラム。
   count = 1400でキャットホイール20回転ぐらい(実測値)
*/
//回転速度計算用
#define DT 10//回転速度計算の周期(ms)
int prev_count;
double curr_t, prev_t;

void setup() {
  prev_count = 0;
  curr_t = 0;
  prev_t = 0;

  curr_sense_val = 0;
  dist_sense_val = 0;
  count = 0;
  min_sense_val = 32767;
  max_sense_val = 0;
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  //センサ値の取得
  curr_sense_val = analogRead(sPin);
  //最小値の更新
  if (min_sense_val > curr_sense_val) {
    min_sense_val = curr_sense_val;
  }
  //最大値の更新
  if (max_sense_val < curr_sense_val) {
    max_sense_val = curr_sense_val;
  }
  //最大値と最小値の差の絶対値が閾値を超えれば、白⇔黒の遷移が起こったとみなす。
  dist_sense_val = max_sense_val - min_sense_val;
  if ((abs(dist_sense_val) - THR) > 0) {
    count++;//回転数(1/6回転)をカウント
    min_sense_val = 32767;//初期化
    max_sense_val = 0;//初期化
    dist_sense_val = 0;//初期化
  }

  curr_t = millis();//現在時刻を取得
  
  if ((curr_t - prev_t) > DT) {//このブロックを動かす時は下のブロックは動かさないこと
    Serial.print(count);
    Serial.println();
    prev_count = count;
    prev_t = curr_t;
  }
  
  //  if ((curr_t - prev_t) > DT * 40) {//このブロックを動かす時は上のブロックは動かさないこと
  //    Serial.print(count - prev_count);
  //    Serial.println();
  //    prev_count = count;
  //    prev_t = curr_t;
  //  }
  
  //  Serial.print(curr_sense_val);
  //  Serial.print(',');
  //  Serial.print(dist_sense_val);
  //  Serial.print(',');
  //  Serial.print(count);
  //  Serial.println();
  //  delay(10);
}

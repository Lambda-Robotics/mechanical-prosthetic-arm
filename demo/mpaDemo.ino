#define EN        8     // ขาเปิดใช้งานมอเตอร์สเต็ปเปอร์ (Active Low)
#define X_DIR     5     // ขาควบคุมทิศทางมอเตอร์แกน X
#define Y_DIR     6     // ขาควบคุมทิศทางมอเตอร์แกน Y
#define X_STP     2     // ขาควบคุมสเต็ปมอเตอร์แกน X
#define Y_STP     3     // ขาควบคุมสเต็ปมอเตอร์แกน Y

int r = 0; // ตัวแปรสำหรับเก็บค่าที่อ่านได้จาก potentiometer
bool stepperClose = true;
bool stepperOpen = true;

// ฟังก์ชัน: step
// หน้าที่: ควบคุมทิศทางและจำนวนสเต็ปของมอเตอร์สเต็ปเปอร์
// พารามิเตอร์: 
//   dir - ควบคุมทิศทาง (boolean)
//   dirPin - ขาทิศทางของมอเตอร์สเต็ปเปอร์ที่ต้องการควบคุม
//   stepperPin - ขาสเต็ปของมอเตอร์สเต็ปเปอร์
//   steps - จำนวนสเต็ปที่ต้องการให้มอเตอร์หมุน
void step(boolean dir, byte dirPin, byte stepperPin, int steps) {
  digitalWrite(dirPin, dir); // กำหนดทิศทาง
  delay(50);
  for (int i = 0; i < steps; i++) {  // วนลูปตามจำนวนสเต็ป
    digitalWrite(stepperPin, HIGH);  // ส่งสัญญาณสูงไปที่ขาสเต็ป
    delayMicroseconds(800);          // หน่วงเวลา 800 ไมโครวินาที
    digitalWrite(stepperPin, LOW);   // ส่งสัญญาณต่ำไปที่ขาสเต็ป
    delayMicroseconds(800);          // หน่วงเวลา 800 ไมโครวินาที
  }
}

void stepreverse(boolean dir, byte dirPin, byte stepperPin, int steps) {
  digitalWrite(dirPin, !dir); // กำหนดทิศทาง
  delay(50);
  for (int i = 0; i < steps; i++) {  // วนลูปตามจำนวนสเต็ป
    digitalWrite(stepperPin, HIGH);  // ส่งสัญญาณสูงไปที่ขาสเต็ป
    delayMicroseconds(800);          // หน่วงเวลา 800 ไมโครวินาที
    digitalWrite(stepperPin, LOW);   // ส่งสัญญาณต่ำไปที่ขาสเต็ป
    delayMicroseconds(800);          // หน่วงเวลา 800 ไมโครวินาที
  }
}

void setup() {
  // กำหนดให้ขาที่ใช้กับมอเตอร์เป็นเอาท์พุต
  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);
  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);
  pinMode(EN, OUTPUT);

  // เปิดใช้งานมอเตอร์สเต็ปเปอร์
  digitalWrite(EN, LOW);

  // เริ่มต้นการทำงานของ Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // อ่านค่าจากตัวต้านทานปรับค่า (Potentiometer) ที่ขา A03
  r = analogRead(A8);  // อ่านค่าจากขา A3 (0 - 1023)

  // แสดงค่าที่อ่านได้ทาง Serial Monitor
  Serial.println(r);

  // ตรวจสอบเงื่อนไข
  if (r > 500) {
    stepperClose = true;
    if (stepperOpen) {
      step(true, X_DIR, X_STP, 100);
      stepperOpen = false;
    }
    // step(true, X_DIR, X_STP, 200);
  } else {
    stepperOpen = true;
    if (stepperClose) {
      stepreverse(true, X_DIR, X_STP, 100);
      stepperClose = false;
    }
    // step(false, X_DIR, X_STP, 200);
  }
  delay(1000);  // หน่วงเวลา 1 วินาที
}
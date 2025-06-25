# 🔧 การสร้างโปรเจกต์ PlatformIO ด้วย Command Line บน Windows 11

## 🧩 ขั้นตอนที่ 1: ติดตั้ง PlatformIO Core (CLI)

### 1.1 ติดตั้ง Python
- ดาวน์โหลดจาก: https://www.python.org/downloads/
- **สำคัญ**: ติ๊ก ✅ `Add Python to PATH`

### 1.2 ติดตั้ง PlatformIO ผ่าน pip
```sh
pip install -U platformio
```
หากเจอปัญหาไฟล์เสียหาย:
```sh
pip install --no-cache-dir --force-reinstall platformio
```

### 1.3 ตรวจสอบว่า PlatformIO ใช้งานได้
```sh
pio --version
```

---

## 📁 ขั้นตอนที่ 2: สร้างโปรเจกต์ใหม่

### 2.1 ใช้คำสั่งสร้างโปรเจกต์
```sh
pio project init --board <board_id>
```
ตัวอย่าง:
```sh
pio project init --board uno
```

### 2.2 โครงสร้างไฟล์ที่ได้
```
my_project/
├── include/         # ไฟล์ header
├── lib/             # ไลบรารีเพิ่มเติม
├── src/             # โค้ดหลักของโปรเจกต์
│   └── main.cpp     # ไฟล์หลัก
├── platformio.ini   # ไฟล์ตั้งค่าบอร์ด
└── .pio/            # ไฟล์ที่ถูกคอมไพล์ (สร้างอัตโนมัติ)
```

---

## 🖊️ ขั้นตอนที่ 3: เขียนโค้ดใน `src/main.cpp`

ตัวอย่างโค้ดสำหรับ Arduino Uno:
```cpp
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.println("Hello, PlatformIO!");
    delay(1000);
}
```

---

## ⚙️ ขั้นตอนที่ 4: คอมไพล์และอัปโหลด

### 4.1 คอมไพล์โค้ด
```sh
pio run
```

### 4.2 อัปโหลดไปยังบอร์ด
```sh
pio run --target upload
```

### 4.3 เปิด Serial Monitor
```sh
pio device monitor
```

---

## 💡 ขั้นตอนที่ 5 (เพิ่มเติม): เปิดโปรเจกต์ใน VS Code

หากติดตั้ง VS Code และ PlatformIO Extension แล้ว:
```sh
code .
```

---

## ✅ สรุป

| ขั้นตอน | คำสั่งสำคัญ |
|--------|--------------|
| ติดตั้ง PlatformIO | `pip install -U platformio` |
| สร้างโปรเจกต์ใหม่ | `pio project init --board <board_id>` |
| คอมไพล์ | `pio run` |
| อัปโหลด | `pio run --target upload` |
| Serial Monitor | `pio device monitor` |

PlatformIO ทำให้การพัฒนาไมโครคอนโทรลเลอร์ง่ายและสะดวกยิ่งขึ้น 💻🔌
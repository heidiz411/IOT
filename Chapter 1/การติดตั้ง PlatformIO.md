# วิธีติดตั้งและอัปเดต PlatformIO บน Windows 11

## 📦 การติดตั้ง PlatformIO Core (CLI)

### 1. ติดตั้ง Python
- ดาวน์โหลดจาก: https://www.python.org/downloads/
- **สำคัญ**: ติ๊ก `Add Python to PATH` ขณะติดตั้ง

### 2. ตรวจสอบ Python และ PIP
```sh
python --version
pip --version
```

### 3. ติดตั้ง PlatformIO
```sh
pip install -U platformio
```

หากพบปัญหาไฟล์เสียหาย ให้ใช้คำสั่ง:
```sh
pip install --no-cache-dir --force-reinstall platformio
```

### 4. ทดสอบ PlatformIO
```sh
pio --version
```

---

## 🛠 หากคำสั่ง `pip` หรือ `pio` ใช้งานไม่ได้

### ✅ เพิ่ม Python/PIP ลงใน PATH
เพิ่มค่าต่อไปนี้เข้าใน Environment Variables:
```
C:\Users\<YourName>\AppData\Local\Programs\Python\Python3xx\
C:\Users\<YourName>\AppData\Local\Programs\Python\Python3xx\Scripts\
```

---

## 🔄 การอัปเดต PlatformIO

### วิธีอัปเดตผ่าน pip
```sh
pip install -U platformio
```

หรือถ้าต้องการติดตั้งใหม่หมด:
```sh
pip uninstall platformio
pip install --no-cache-dir platformio
```

### วิธีอัปเดตผ่าน VS Code
1. เปิด VS Code
2. ไปที่ Extensions → PlatformIO IDE
3. หากมีปุ่ม Update ให้กดอัปเดต

---

## ⚠️ ปัญหาที่อาจเจอและวิธีแก้

### ❌ SyntaxError: source code string cannot contain null bytes
- ลบโฟลเดอร์ `platformio` และ `pio.exe` ที่อาจเสียหาย
- ใช้ `pip install --no-cache-dir platformio` เพื่อล้างและติดตั้งใหม่

### ❌ pip is not recognized
- เพิ่ม PATH ให้ Python และ Scripts ตามที่ระบุไว้ข้างต้น
- หรือติดตั้ง Python ใหม่พร้อมติ๊ก "Add to PATH"

---

## ✅ ตรวจสอบว่า PlatformIO ทำงาน
```sh
pio --version
```

หากเห็นข้อความเช่น `PlatformIO Core, version 6.x.x` แสดงว่าใช้งานได้เรียบร้อยแล้ว 🎉

---

## 📁 หมายเหตุ
หากยังมีปัญหาเพิ่มเติม สามารถใช้ [PlatformIO Installer](https://docs.platformio.org/en/latest/core/installation.html#installer-script) ได้เช่นกัน
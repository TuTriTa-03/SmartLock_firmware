# NOIR HOME — Web Dashboard Starter

Giao diện dashboard web tĩnh cho dự án SmartLock-AI-Intercom / NOIR HOME.

## Cấu trúc

```text
web/
├── index.html
├── css/
│   ├── style.css
│   └── animations.css
├── js/
│   ├── app.js
│   ├── door.js
│   ├── keypad.js
│   ├── visitor.js
│   ├── intercom.js
│   ├── eventLog.js
│   └── communication.js
└── assets/
    ├── images/
    ├── icons/
    └── sounds/
```

## Chạy thử

1. Giải nén thư mục.
2. Mở `web/index.html` bằng trình duyệt; hoặc mở thư mục `web/` trong VS Code và chạy bằng extension Live Server.
3. Thử keypad với PIN demo `123456`, nút mô phỏng chuông cửa, Intercom demo và cấu hình kết nối.

## Lưu ý quan trọng

- Đây là **bản giao diện mô phỏng**, chưa kết nối Yolo UNO, ESP32, STM32, MQTT, camera, micro, loa hoặc khóa cửa vật lý.
- PIN `123456` được viết cứng để demo giao diện, không an toàn để sử dụng trong sản phẩm thật.
- Nút mở/khóa chỉ thay đổi trạng thái trên giao diện; không điều khiển phần cứng.
- Nhật ký chỉ tồn tại trong bộ nhớ của phiên trang hiện tại và sẽ mất khi tải lại trang.
- `communication.js` hiện là adapter giả lập, chưa thực hiện request mạng. Khi tích hợp firmware cần thiết kế API/protocol, xác thực, xử lý timeout, lỗi và trạng thái an toàn.
- Không nhập PIN thật, mật khẩu Wi-Fi hoặc thông tin bí mật vào bản demo.

## Các module JavaScript

- `app.js`: khởi tạo giao diện, đồng hồ, điều hướng, modal cấu hình.
- `door.js`: trạng thái cửa giả lập và tự khóa demo sau 5 giây.
- `keypad.js`: keypad, xác thực PIN demo, giới hạn nhập sai ở giao diện.
- `visitor.js`: mô phỏng chuông cửa.
- `intercom.js`: mô phỏng trạng thái phiên liên lạc, không truy cập micro.
- `eventLog.js`: nhật ký sự kiện trong phiên.
- `communication.js`: lớp adapter giao tiếp dạng stub để thay thế khi tích hợp thiết bị.

## Giai đoạn tích hợp sau này

Thống nhất giao thức trước (message type, payload, response, timeout, error code). Không để module giao diện tự ý gửi lệnh trực tiếp đến phần cứng. Tùy kiến trúc cuối cùng, trình duyệt có thể gọi HTTP API trên Yolo UNO hoặc đi qua backend/broker hỗ trợ WebSocket cho MQTT.

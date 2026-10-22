/* Demo PIN keypad. Never use this hard-coded PIN for a real lock. */
(function () {
  const DEMO_PIN = "123456";
  const MAX_LENGTH = 8;
  let pin = "";
  let failedAttempts = 0;
  let lockedUntil = 0;
  const LOCKOUT_MS = 15000;
  function feedback(message, type = "") {
    const el = document.getElementById("pin-feedback");
    if (!el) return;
    el.textContent = message; el.className = `inline-feedback ${type}`.trim();
  }
  function render() {
    const display = document.getElementById("pin-display");
    if (!display) return;
    display.replaceChildren();
    if (!pin.length) {
      const placeholder = document.createElement("span"); placeholder.className = "pin-placeholder"; placeholder.textContent = "Nhập PIN"; display.append(placeholder);
    } else {
      for (let i = 0; i < pin.length; i++) {
        const dot = document.createElement("span"); dot.className = "pin-bullet"; dot.textContent = "•"; display.append(dot);
      }
    }
  }
  function addDigit(digit) {
    if (Date.now() < lockedUntil) { feedback("Bàn phím demo đang tạm khóa sau nhiều lần nhập sai.", "error"); return; }
    if (pin.length >= MAX_LENGTH) return;
    pin += digit; render(); feedback("PIN chỉ được xử lý trong trình duyệt demo.");
  }
  function clear() { pin = ""; render(); feedback("Đã xóa PIN."); }
  function submit() {
    if (Date.now() < lockedUntil) { feedback("Tạm khóa bàn phím demo. Vui lòng đợi.", "error"); return; }
    if (!pin) { feedback("Bạn chưa nhập PIN.", "error"); return; }
    if (pin === DEMO_PIN) {
      failedAttempts = 0; feedback("Xác thực demo thành công. Đây không phải lệnh mở khóa thật.", "success");
      window.NoirEventLog?.add({ title: "Xác thực PIN thành công (demo)", detail: "Mã demo được chấp nhận tại giao diện", type: "auth", severity: "success" });
      window.NoirDoor?.setUnlocked(true, "Xác thực PIN demo thành công");
      window.NoirApp?.toast("PIN hợp lệ trong chế độ demo.");
    } else {
      failedAttempts++;
      feedback(`PIN không đúng. Lần nhập sai ${failedAttempts}/5.`, "error");
      window.NoirEventLog?.add({ title: "Xác thực PIN thất bại (demo)", detail: `Lần nhập sai ${failedAttempts}/5`, type: "auth", severity: "danger" });
      if (failedAttempts >= 5) { lockedUntil = Date.now() + LOCKOUT_MS; failedAttempts = 0; feedback("Đã tạm khóa keypad demo 15 giây.", "error"); }
    }
    pin = ""; render();
  }
  document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("keypad")?.addEventListener("click", (event) => {
      const button = event.target.closest("button"); if (!button) return;
      if (button.dataset.key) addDigit(button.dataset.key);
      if (button.dataset.action === "clear") clear();
      if (button.dataset.action === "submit") submit();
    });
    document.getElementById("pin-clear")?.addEventListener("click", clear);
    document.getElementById("pin-submit")?.addEventListener("click", submit);
    render();
  });
  window.NoirKeypad = { clear, submit };
})();

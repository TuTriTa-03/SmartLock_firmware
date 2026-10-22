/* Application bootstrap and shared UI behavior. */
(function () {
  let toastTimer = null;
  function toast(message) {
    const el = document.getElementById("toast"); if (!el) return;
    el.textContent = message; el.classList.add("show");
    if (toastTimer) clearTimeout(toastTimer);
    toastTimer = setTimeout(() => el.classList.remove("show"), 2800);
  }
  function updateClock() {
    const now = new Date();
    const time = document.getElementById("current-time");
    const date = document.getElementById("current-date");
    const cameraTime = document.getElementById("camera-time");
    if (time) time.textContent = now.toLocaleTimeString("vi-VN", { hour: "2-digit", minute: "2-digit", second: "2-digit" });
    if (date) date.textContent = now.toLocaleDateString("vi-VN", { weekday: "long", day: "2-digit", month: "long", year: "numeric" });
    if (cameraTime) cameraTime.textContent = now.toLocaleTimeString("vi-VN", { hour: "2-digit", minute: "2-digit", second: "2-digit" });
  }
  function setupNavigation() {
    document.querySelectorAll(".nav-item").forEach((link) => link.addEventListener("click", () => {
      document.querySelectorAll(".nav-item").forEach((item) => item.classList.remove("active"));
      link.classList.add("active");
    }));
  }
  function setupConnectionModal() {
    const modal = document.getElementById("connection-modal");
    const endpoint = document.getElementById("endpoint-input");
    const transport = document.getElementById("transport-select");
    const status = document.getElementById("connection-status");
    const caption = document.getElementById("connection-caption");
    const dot = document.getElementById("connection-dot");
    const feedback = document.getElementById("connection-feedback");
    document.getElementById("connection-settings")?.addEventListener("click", () => {
      const config = window.NoirCommunication.getConfig();
      endpoint.value = config.endpoint; transport.value = config.transport;
      if (typeof modal.showModal === "function") modal.showModal(); else toast("Trình duyệt này không hỗ trợ hộp thoại cấu hình.");
    });
    document.getElementById("save-connection")?.addEventListener("click", () => {
      if (endpoint.value && !endpoint.checkValidity()) { endpoint.reportValidity(); return; }
      window.NoirCommunication.setConfig({ endpoint: endpoint.value, transport: transport.value });
      status.textContent = "Chưa kết nối";
      document.querySelector(".connection-state")?.classList.remove("connected");
      dot.style.background = "var(--amber)";
      caption.textContent = transport.value === "simulated" ? "Đang chạy ở chế độ giao diện độc lập" : "Đã lưu cấu hình; chưa kiểm tra kết nối thiết bị";
      feedback.textContent = "Đã lưu cục bộ trong phiên này. Chưa gửi yêu cầu mạng.";
      if (modal.open) modal.close("saved");
      toast("Đã lưu cấu hình demo; thiết bị chưa được kết nối.");
      window.NoirEventLog?.add({ title: "Cập nhật cấu hình giao tiếp", detail: `Transport: ${transport.value}; chưa kết nối thiết bị`, type: "system", severity: "normal" });
    });
  }
  function setupClearEvents() {
    document.getElementById("clear-events")?.addEventListener("click", () => {
      window.NoirEventLog?.clear();
      toast("Đã xóa nhật ký trong phiên hiện tại.");
    });
  }
  document.addEventListener("DOMContentLoaded", () => {
    updateClock(); setInterval(updateClock, 1000);
    setupNavigation(); setupConnectionModal(); setupClearEvents();
    window.NoirEventLog?.add({ title: "Dashboard khởi động", detail: "Chế độ demo độc lập; chưa kết nối phần cứng", type: "system", severity: "normal" });
  });
  window.NoirApp = { toast };
})();

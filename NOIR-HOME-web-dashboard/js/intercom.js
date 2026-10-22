/* Intercom UI state only. Does not request microphone permission or record audio. */
(function () {
  let active = false;
  function render() {
    const status = document.getElementById("intercom-status");
    const description = document.getElementById("intercom-description");
    const start = document.getElementById("talk-toggle");
    const end = document.getElementById("talk-end");
    if (!status) return;
    status.textContent = active ? "Phiên intercom demo đang chạy" : "Liên lạc đang chờ";
    description.textContent = active ? "Đang mô phỏng trạng thái phiên liên lạc. Chưa có âm thanh thật." : "Micro và loa chưa được kết nối với thiết bị.";
    start.disabled = active; end.disabled = !active;
    start.textContent = active ? "Phiên demo đang chạy" : "Bắt đầu phiên demo";
  }
  function start() {
    if (active) return; active = true; render();
    window.NoirEventLog?.add({ title: "Bắt đầu intercom (demo)", detail: "Chỉ thay đổi trạng thái giao diện", type: "intercom", severity: "success" });
    window.NoirApp?.toast("Phiên intercom demo đã bắt đầu.");
  }
  function end() {
    if (!active) return; active = false; render();
    window.NoirEventLog?.add({ title: "Kết thúc intercom (demo)", detail: "Phiên mô phỏng đã kết thúc", type: "intercom", severity: "normal" });
  }
  document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("talk-toggle")?.addEventListener("click", start);
    document.getElementById("talk-end")?.addEventListener("click", end);
    render();
  });
  window.NoirIntercom = { start, end, isActive: () => active };
})();

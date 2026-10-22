/* Visitor/doorbell interaction simulator; no camera hardware is accessed. */
(function () {
  let visitorNumber = 0;
  function simulate() {
    visitorNumber++;
    const state = document.getElementById("visitor-state");
    const detail = document.getElementById("visitor-detail");
    if (state) state.textContent = `Có khách nhấn chuông #${visitorNumber}`;
    if (detail) detail.textContent = "Sự kiện chuông cửa giả lập — chưa có hình ảnh camera.";
    window.NoirEventLog?.add({ title: "Có người nhấn chuông (demo)", detail: `Sự kiện khách đến #${visitorNumber}`, type: "visitor", severity: "normal" });
    window.NoirApp?.toast("Đã tạo sự kiện chuông cửa mô phỏng.");
  }
  document.addEventListener("DOMContentLoaded", () => document.getElementById("simulate-visitor")?.addEventListener("click", simulate));
  window.NoirVisitor = { simulate };
})();

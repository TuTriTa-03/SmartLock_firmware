/* Door UI state simulator. This module does not actuate physical hardware. */
(function () {
  let unlocked = false;
  let relockTimer = null;
  const UNLOCK_DEMO_MS = 5000;
  function render() {
    const status = document.getElementById("door-status");
    const caption = document.getElementById("door-caption");
    const button = document.getElementById("main-door-toggle");
    const illustration = document.getElementById("door-illustration");
    const footnote = document.getElementById("door-footnote");
    if (!status) return;
    status.textContent = unlocked ? "Đang mở khóa" : "Đã khóa";
    caption.textContent = unlocked ? "Cửa đang ở trạng thái mở khóa demo" : "Lối vào đang được bảo vệ";
    button.innerHTML = unlocked ? 'Khóa lại demo <span>↗</span>' : 'Mở khóa demo <span>↗</span>';
    illustration.classList.toggle("unlocked", unlocked);
    footnote.textContent = unlocked ? "Tự khóa lại sau khoảng 5 giây" : "Trạng thái mô phỏng an toàn";
  }
  function setUnlocked(value, source = "Thao tác trên dashboard") {
    unlocked = Boolean(value);
    if (relockTimer) clearTimeout(relockTimer);
    render();
    if (unlocked) {
      window.NoirEventLog?.add({ title: "Cửa được mở khóa (demo)", detail: source, type: "access", severity: "success" });
      relockTimer = setTimeout(() => setUnlocked(false, "Tự khóa sau 5 giây (demo)"), UNLOCK_DEMO_MS);
    } else {
      window.NoirEventLog?.add({ title: "Cửa đã khóa (demo)", detail: source, type: "access", severity: "normal" });
    }
  }
  function toggle() { setUnlocked(!unlocked); }
  function isUnlocked() { return unlocked; }
  document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("main-door-toggle")?.addEventListener("click", toggle);
    render();
  });
  window.NoirDoor = { setUnlocked, toggle, isUnlocked };
})();

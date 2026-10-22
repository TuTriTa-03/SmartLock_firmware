/* Session-only event log; intentionally does not persist sensitive access data. */
(function () {
  const events = [];
  const icons = { access: "⌑", auth: "◈", visitor: "◉", intercom: "⌁", system: "⌘", alert: "!" };
  function add({ title, detail = "", type = "system", severity = "normal" }) {
    const item = { id: `${Date.now()}-${Math.random().toString(16).slice(2)}`, title, detail, type, severity, time: new Date() };
    events.unshift(item);
    if (events.length > 30) events.length = 30;
    render();
    return item;
  }
  function render() {
    const list = document.getElementById("event-list");
    const count = document.getElementById("event-count");
    if (!list || !count) return;
    count.textContent = `${events.length} sự kiện`;
    if (!events.length) {
      list.innerHTML = '<div class="empty-events">Chưa có sự kiện. Các thao tác demo sẽ xuất hiện tại đây.</div>';
      return;
    }
    list.replaceChildren();
    events.slice(0, 7).forEach((event) => {
      const row = document.createElement("div"); row.className = "event-item";
      const icon = document.createElement("div"); icon.className = `event-icon ${event.severity}`; icon.textContent = icons[event.type] || "•";
      const copy = document.createElement("div"); copy.className = "event-copy";
      const title = document.createElement("strong"); title.textContent = event.title;
      const detail = document.createElement("p"); detail.textContent = event.detail;
      copy.append(title, detail);
      const time = document.createElement("time"); time.className = "event-time"; time.dateTime = event.time.toISOString(); time.textContent = event.time.toLocaleTimeString("vi-VN", { hour: "2-digit", minute: "2-digit", second: "2-digit" });
      row.append(icon, copy, time); list.append(row);
    });
  }
  function clear() { events.length = 0; render(); }
  window.NoirEventLog = { add, clear, getAll: () => events.slice() };
  document.addEventListener("DOMContentLoaded", render);
})();

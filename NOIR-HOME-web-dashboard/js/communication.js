/* Communication adapter: UI demo only. No network requests are sent in this starter. */
(function () {
  const config = { endpoint: "", transport: "simulated", connected: false };
  function getConfig() { return { ...config }; }
  function setConfig(next) {
    if (!next || typeof next !== "object") return false;
    config.endpoint = typeof next.endpoint === "string" ? next.endpoint.trim() : "";
    config.transport = ["http", "mqtt", "simulated"].includes(next.transport) ? next.transport : "simulated";
    // A saved endpoint is configuration only; it does not mean a device is connected.
    config.connected = false;
    return true;
  }
  async function sendCommand(command, payload = {}) {
    // Replace this stub with a real, authenticated API adapter during integration.
    return { ok: false, simulated: true, command, payload, message: "Chưa tích hợp thiết bị thật." };
  }
  window.NoirCommunication = { getConfig, setConfig, sendCommand };
})();

const BASE = "http://localhost:8001/api";

export async function fetchWelcomeName() {
  const res = await fetch(`${BASE_URL}/tes_get`);
  if (!res.ok) throw new Error("Network response was not ok");
  return res.json();
}

export async function tampilkan_dokter() {
  const res = await fetch(`${BASE}/tampilkan_dokter`);
  if (!res.ok) throw new Error("Gagal fetch data dokter");
  const data = await res.json();
  return data;
}

export async function tambah_dokter(data) {
  const res = await fetch("http://localhost:8001/api/tambah_dokter", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(data),
  });
  return res.json();
}

export async function hapus_dokter(data) {
  const res = await fetch("http://localhost:8001/api/hapus_dokter", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(data),
  });
  return res.json();
}

export async function update_dokter(data) {
  const res = await fetch("http://localhost:8001/api/update_dokter", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(data),
  });
  return res.json();
}

export async function buatJadwal() {
  const res = await fetch(`${BASE}/buat_jadwal`, { method: "POST" });
  return await res.json();
}

export async function tampilkanJadwalBulanan() {
  const res = await fetch(`${BASE}/tampilkan_jadwal_bulanan`, {
    method: "POST",
  });
  console.log("Response from tampilkanJadwalBulanan:", res);
  return await res.json();
}

export async function tampilkanJadwalMingguan(minggu) {
  const res = await fetch(`${BASE}/tampilkan_jadwal_mingguan`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ minggu }),
  });
  return await res.json();
}

export async function tampilkanJadwalHarian(hari) {
  const res = await fetch(`${BASE}/tampilkan_jadwal_harian`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ hari }), //
  });
  return await res.json();
}

export async function tampilkanReportShift() {
  const res = await fetch("http://localhost:8001/api/tampilkan_report_shift", {
    method: "POST",
  });
  return await res.json();
}

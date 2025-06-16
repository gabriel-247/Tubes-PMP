const BASE_URL = "http://localhost:8001/api";

export async function fetchWelcomeName() {
  const res = await fetch(`${BASE_URL}/tes_get`);
  if (!res.ok) throw new Error("Network response was not ok");
  return res.json();
}

export async function tampilkan_dokter() {
  const res = await fetch(`${BASE_URL}/tampilkan_dokter`);
  if (!res.ok) throw new Error("Gagal fetch data dokter");
  const data = await res.json();
  return data; // langsung array
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

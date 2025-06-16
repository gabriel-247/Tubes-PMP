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

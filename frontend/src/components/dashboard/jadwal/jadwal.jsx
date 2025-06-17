import React, { useEffect, useState } from "react";
import "./jadwal.css";
import { buatJadwal, tampilkanJadwalBulanan, tampilkanJadwalMingguan, tampilkanJadwalHarian } from "../../../services/api.jsx";

const Jadwal = () => {
  const [jadwalList, setJadwalList] = useState([]);
  const [mode, setMode] = useState("bulanan");
  const [minggu, setMinggu] = useState(1);
  const [hari, setHari] = useState(1);
  const [loading, setLoading] = useState(false);

  const loadJadwal = async () => {
    setLoading(true);
    try {
      let result = [];

      if (mode === "bulanan") {
        result = await tampilkanJadwalBulanan();
      } else if (mode === "mingguan") {
        if (minggu >= 1 && minggu <= 4) {
          const data = await tampilkanJadwalMingguan(minggu);
          result = Array.isArray(data) ? data : [data];
        }
      } else if (mode === "harian") {
        if (hari >= 1 && hari <= 30) {
          const data = await tampilkanJadwalHarian(hari);
          result = Array.isArray(data) ? data : [data];
        }
      }

      setJadwalList(result);
    } catch (err) {
      console.error("Gagal load jadwal:", err);
      setJadwalList([]);
    }
    setLoading(false);
  };

  const handleBuatJadwal = async () => {
    await buatJadwal();
    loadJadwal();
  };

  useEffect(() => {
    loadJadwal();
  }, [mode, minggu, hari]);

  return (
    <div className="jadwal-container">
      <h2>Jadwal Shift Dokter</h2>

      <div className="controls">
        <button onClick={handleBuatJadwal}>Buat Jadwal Otomatis</button>
        <select value={mode} onChange={(e) => setMode(e.target.value)}>
          <option value="bulanan">Bulanan</option>
          <option value="mingguan">Mingguan</option>
          <option value="harian">Harian</option>
        </select>

        {mode === "mingguan" && <input type="number" min={1} max={4} value={minggu} onChange={(e) => setMinggu(parseInt(e.target.value))} />}

        {mode === "harian" && <input type="number" min={1} max={30} value={hari} onChange={(e) => setHari(parseInt(e.target.value))} />}
      </div>

      {loading ? (
        <p>Memuat data...</p>
      ) : (
        <table>
          <thead>
            <tr>
              <th>Hari</th>
              <th>Pagi</th>
              <th>Siang</th>
              <th>Malam</th>
            </tr>
          </thead>
          <tbody>
            {jadwalList.map((jadwal, index) => (
              <tr key={index}>
                <td>{jadwal.hari}</td>
                <td>{jadwal.pagi}</td>
                <td>{jadwal.siang}</td>
                <td>{jadwal.malam}</td>
              </tr>
            ))}
          </tbody>
        </table>
      )}
    </div>
  );
};

export default Jadwal;

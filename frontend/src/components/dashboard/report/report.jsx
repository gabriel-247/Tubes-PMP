// src/pages/Report.jsx
import React, { useEffect, useState } from "react";
import "./report.css";
import { tampilkan_dokter, tampilkanReportShift } from "../../../services/api";

export default function Report() {
  const [dokterList, setDokterList] = useState([]);
  const [selectedId, setSelectedId] = useState("");
  const [report, setReport] = useState(null);
  const [loading, setLoading] = useState(false);

  const loadDokter = async () => {
    try {
      const data = await tampilkan_dokter();
      setDokterList(data);
      if (data.length > 0) {
        setSelectedId(data[0].id); // pilih default pertama
      }
    } catch (err) {
      console.error("Gagal memuat dokter:", err);
    }
  };

  const loadReport = async () => {
    setLoading(true);
    try {
      const res = await tampilkanReportShift();
      const filtered = res.find((r) => r.id === Number(selectedId));
      setReport(filtered);
    } catch (err) {
      console.error("Gagal memuat report:", err);
      setReport(null);
    }
    setLoading(false);
  };

  useEffect(() => {
    loadDokter();
  }, []);

  useEffect(() => {
    if (selectedId) loadReport();
  }, [selectedId]);

  return (
    <div className="report-container">
      <h2>Report Shift Dokter</h2>

      <div className="report-controls">
        <label>Pilih Dokter:</label>
        <select value={selectedId} onChange={(e) => setSelectedId(e.target.value)}>
          {dokterList.map((d) => (
            <option key={d.id} value={d.id}>
              {d.nama}
            </option>
          ))}
        </select>
      </div>

      {loading ? (
        <p>Memuat data...</p>
      ) : report ? (
        <div className="report-card">
          <h3>{report.nama}</h3>
          <p>ID: {report.id}</p>
          <p>Total Shift: {report.total_shift}</p>
          <p>Pelanggaran Preferensi: {report.pelanggaran_preferensi}</p>
          <p>Pelanggaran Shift: {report.pelanggaran_shift}</p>
        </div>
      ) : (
        <p>Data tidak tersedia.</p>
      )}
    </div>
  );
}

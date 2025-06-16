import React, { useEffect, useState } from "react";
import { tampilkan_dokter } from "../../../services/api.jsx";

const Dokter = () => {
  const [dokterList, setDokterList] = useState([]);

  useEffect(() => {
    async function getData() {
      try {
        const data = await tampilkan_dokter();
        setDokterList(data); // langsung array dokter
      } catch (err) {
        console.error("Gagal ambil data dokter:", err);
      }
    }

    getData();
  }, []);

  return (
    <div>
      <h2>Daftar Dokter</h2>
      <table border="1" cellPadding="10">
        <thead>
          <tr>
            <th>ID</th>
            <th>Nama</th>
            <th>Maks/Shift</th>
            <th>Pagi</th>
            <th>Siang</th>
            <th>Malam</th>
          </tr>
        </thead>
        <tbody>
          {dokterList.map((dokter) => (
            <tr key={dokter.id}>
              <td>{dokter.id}</td>
              <td>{dokter.nama}</td>
              <td>{dokter.maks}</td>
              <td>{dokter.pagi}</td>
              <td>{dokter.siang}</td>
              <td>{dokter.malam}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default Dokter;

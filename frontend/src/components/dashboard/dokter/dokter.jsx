import React, { useEffect, useState } from "react";
import { tampilkan_dokter, tambah_dokter, hapus_dokter } from "../../../services/api";
import "./dokter.css";

const Dokter = () => {
  const [dokterList, setDokterList] = useState([]);
  const [showModal, setShowModal] = useState(false);
  const [form, setForm] = useState({
    nama: "",
    maks: "",
    pagi: 0,
    siang: 0,
    malam: 0,
  });

  const getData = async () => {
    try {
      const data = await tampilkan_dokter();
      setDokterList(data);
    } catch (err) {
      console.error("Gagal ambil data dokter:", err);
    }
  };

  useEffect(() => {
    getData();
  }, []);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setForm((prev) => ({ ...prev, [name]: value }));
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      await tambah_dokter({
        nama: form.nama,
        maks: parseInt(form.maks),
        pagi: parseInt(form.pagi),
        siang: parseInt(form.siang),
        malam: parseInt(form.malam),
      });
      setShowModal(false);
      setForm({ nama: "", maks: "", pagi: 0, siang: 0, malam: 0 });
      getData();
    } catch (err) {
      alert("Gagal menambahkan dokter.");
    }
  };

  const handleDelete = async (id) => {
    if (window.confirm(`Yakin ingin hapus dokter dengan ID ${id}?`)) {
      try {
        await hapus_dokter({ id: parseInt(id) });
        getData();
      } catch (err) {
        alert("Gagal menghapus dokter.");
      }
    }
  };

  return (
    <div className="dokter-container">
      <h2>Daftar Dokter</h2>
      <button className="btn-tambah" onClick={() => setShowModal(true)}>
        + Tambah Dokter
      </button>

      <table className="dokter-table">
        <thead>
          <tr>
            <th>ID</th>
            <th>Nama</th>
            <th>Maks/Shift</th>
            <th>Pagi</th>
            <th>Siang</th>
            <th>Malam</th>
            <th>Aksi</th>
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
              <td>
                <button className="btn-hapus" onClick={() => handleDelete(dokter.id)}>
                  Hapus
                </button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>

      {showModal && (
        <div className="modal-backdrop">
          <div className="modal">
            <h3>Tambah Dokter</h3>
            <form onSubmit={handleSubmit}>
              <input name="nama" placeholder="Nama Dokter" value={form.nama} onChange={handleChange} required />
              <input name="maks" type="number" placeholder="Maks shift/minggu" value={form.maks} onChange={handleChange} required />
              <label>Preferensi Shift:</label>
              <div className="preferensi">
                <label>Pagi</label>
                <select name="pagi" value={form.pagi} onChange={handleChange}>
                  <option value="1">Ya</option>
                  <option value="0">Tidak</option>
                </select>
                <label>Siang</label>
                <select name="siang" value={form.siang} onChange={handleChange}>
                  <option value="1">Ya</option>
                  <option value="0">Tidak</option>
                </select>
                <label>Malam</label>
                <select name="malam" value={form.malam} onChange={handleChange}>
                  <option value="1">Ya</option>
                  <option value="0">Tidak</option>
                </select>
              </div>
              <div className="modal-btns">
                <button type="submit">Tambah</button>
                <button type="button" onClick={() => setShowModal(false)}>
                  Batal
                </button>
              </div>
            </form>
          </div>
        </div>
      )}
    </div>
  );
};

export default Dokter;

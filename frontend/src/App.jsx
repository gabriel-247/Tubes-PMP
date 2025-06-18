import React from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import LandingPage from "./components/landing page/landingpage";
import DashboardLayout from "./components/dashboard/dashboard";
import Dokter from "./components/dashboard/dokter/dokter.jsx";
import Jadwal from "./components/dashboard/jadwal/jadwal.jsx";
import Report from "./components/dashboard/report/report.jsx";

export default function App() {
  return (
    <BrowserRouter>
      <Routes>
        {/* Landing page */}
        <Route path="/" element={<LandingPage />} />
        {/* Dashboard layout */}
        <Route path="/dashboard" element={<DashboardLayout />}>
          <Route path="dokter" element={<Dokter />} />
          <Route path="jadwal" element={<Jadwal />} />
          <Route path="report" element={<Report />} />
          {/* Tambahkan rute lain di sini jika perlu */}
        </Route>
      </Routes>
    </BrowserRouter>
  );
}

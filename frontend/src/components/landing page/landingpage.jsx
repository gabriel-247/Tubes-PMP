// src/components/LandingPage.jsx
import React from "react";
import { useNavigate } from "react-router-dom";
import "./landingpage.css";

export default function LandingPage() {
  const navigate = useNavigate();
  return (
    <div className="landing-container">
      <header className="landing-header">
        <div className="logo">RS Scheduler</div>
        <button className="enter-btn" onClick={() => navigate("/dashboard/dokter")}>
          Go to App
        </button>
      </header>

      <main className="landing-main">
        <section className="hero-section">
          <div className="hero-text">
            <h1>Easy scheduling ahead</h1>
            <p>Kelola jadwal shift dokter rumah sakit Anda dengan efisien, cepat, dan tanpa konflik.</p>
            <div className="hero-actions">
              <button className="google-btn">Sign up with Google</button>
            </div>
          </div>
          <div className="hero-image">
            <img src="/assets/schedule-preview.png" alt="Scheduler Preview" />
          </div>
        </section>
      </main>

      <section className="brand-section">
        <div className="brand-message">
          <h2>Solusi Modern untuk Penjadwalan Shift</h2>
          <p>RS Scheduler dirangcang khusus untuk kebutuhan rumah sakit, klinik, dan fasilitas kesehatan lainnya. Otomatisasi dan fleksibel dalam satu platform</p>
          <button className="signup-btn">Try for Free Now</button>
        </div>
      </section>

      <footer className="landing-footer">
        <p>&copy; 2025 RS Scheduler Inc. All rights reserved.</p>
      </footer>
    </div>
  );
}

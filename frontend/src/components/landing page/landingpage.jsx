// src/components/LandingPage.jsx
import React from "react";
import { useNavigate } from "react-router-dom";
import "./landingpage.css";

export default function LandingPage({ onEnter }) {
  const navigate = useNavigate();
  return (
    <div className="landing-container">
      <header className="landing-header">
        <div className="logo">Scheduler</div>
        <button className="enter-btn" onClick={() => navigate("/dashboard/dokter")}>
          Go to App
        </button>
      </header>

      <main className="landing-main">
        <section className="hero-section">
          <div className="hero-text">
            <h1>Easy scheduling ahead</h1>
            <p>Join professionals who easily book meetings with Scheduler. Simplify scheduling, eliminate back-and-forth emails.</p>
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
          <h2>Calendly makes scheduling simple</h2>
          <p>Calendly’s easy enough for individual users, and powerful enough to meet the needs of enterprise organizations — including 86% of the Fortune 500 companies.</p>
          <button className="signup-btn">Sign up for free</button>
        </div>
      </section>

      <footer className="landing-footer">
        <p>&copy; 2025 Scheduler Inc. All rights reserved.</p>
      </footer>
    </div>
  );
}

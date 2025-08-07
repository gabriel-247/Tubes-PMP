import React from "react";
import Sidebar from "./sidebar/sidebar";
import { Outlet, useNavigate } from "react-router-dom";
import "./dashboard.css";
import "./dokter/dokter.jsx";

const Dashboard = () => {
  const navigate = useNavigate();
  return (
    <div className="dashboard-container">
      <Sidebar />
      <main className="dashboard-content">
        <button className="back-button" onClick={() => navigate("/")}>Back to Landing Page</button>
        <Outlet />
      </main>
    </div>
  );
};

export default Dashboard;

import React from "react";
import Sidebar from "./sidebar/sidebar";
import { Outlet } from "react-router-dom";
import "./dashboard.css";
import "./dokter/dokter.jsx";

const Dashboard = () => {
  return (
    <div className="dashboard-container">
      <Sidebar />
      <main className="dashboard-content">
        <Outlet />
      </main>
    </div>
  );
};

export default Dashboard;

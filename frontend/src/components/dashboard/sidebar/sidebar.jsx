import React, { useState } from "react";
import { NavLink } from "react-router-dom";
import { FaRegCalendarAlt, FaClock, FaUserFriends, FaStream, FaPlug, FaCogs, FaChevronLeft, FaChevronRight } from "react-icons/fa";
import "./sidebar.css";

const Sidebar = () => {
  const [collapsed, setCollapsed] = useState(false);
  const toggleSidebar = () => setCollapsed(!collapsed);

  return (
    <nav className={`sidebar ${collapsed ? "collapsed" : ""}`}>
      <button className="toggle-button" onClick={toggleSidebar} title={collapsed ? "Expand navigation" : "Collapse navigation"}>
        {collapsed ? <FaChevronRight /> : <FaChevronLeft />}
      </button>

      {!collapsed && <div className="sidebar-header">RS Scheduler</div>}

      <ul>
        <li>
          <NavLink to="dokter">
            <FaRegCalendarAlt />
            {!collapsed && "Dokter"}
          </NavLink>
        </li>
        <li>
          <NavLink to="jadwal">
            <FaUserFriends />
            {!collapsed && "Jadwal"}
          </NavLink>
        </li>
        <li>
          <NavLink to="settings">
            <FaCogs />
            {!collapsed && "Settings"}
          </NavLink>
        </li>
      </ul>
    </nav>
  );
};

export default Sidebar;

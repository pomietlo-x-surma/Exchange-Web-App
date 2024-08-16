import React from "react";
import Main from "./Main";

const MainWrapper: React.FC = () => {
  const username = localStorage.getItem("username") || ""; // Pobieramy username z localStorage

  return <Main username={username} />;
};

export default MainWrapper;

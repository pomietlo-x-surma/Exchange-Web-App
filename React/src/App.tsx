import React from "react";
import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import Login from "./components/Login";
import CreateAccount from "./components/Register";
import MainWrapper from "./components/MainWrapper";
import './App.css';

const App: React.FC = () => {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<Login />} />
        <Route path="/Main/:message" element={<MainWrapper />} /> {/* Nie przekazujemy już username bezpośrednio */}
        <Route path="/Register" element={<CreateAccount />} />
      </Routes>
    </Router>
  );
};

export default App;

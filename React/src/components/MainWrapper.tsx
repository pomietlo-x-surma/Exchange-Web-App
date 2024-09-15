import React, { useEffect } from "react";
import { w3cwebsocket as W3CWebSocket } from "websocket";
import Main from "./Main";

const client = new W3CWebSocket("ws://localhost:8080");

const MainWrapper: React.FC = () => {
  const username = localStorage.getItem("username") || "";

  useEffect(() => {
    // Sprawdź, czy połączenie WebSocket jest otwarte
    if (client.readyState === WebSocket.OPEN) {
      client.send(`User ${username} has switched to Main page.`);
    } else {
      // Jeśli połączenie nie jest otwarte, ustaw nasłuch na `onopen`
      client.onopen = () => {
        client.send(`User ${username} has switched to Main page.`);
      };
    }

    // Opcjonalne odświeżenie strony po 0.5s
    setTimeout(() => {
      window.location.reload();
    }, 500);

    // Funkcja czyszcząca po odmontowaniu komponentu
    return () => {
      client.onopen = null;
    };
  }, [username]);

  return <Main username={username} />;
};

export default MainWrapper;

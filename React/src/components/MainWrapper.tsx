import React, { useEffect } from "react";
import { w3cwebsocket as W3CWebSocket } from "websocket";
import Main from "./Main";

const client = new W3CWebSocket("ws://localhost:8080");

const MainWrapper: React.FC = () => {
  const username = localStorage.getItem("username") || "";

  useEffect(() => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(`User ${username} has switched to Main page.`);
    } else {
      client.onopen = () => {
        client.send(`User ${username} has switched to Main page.`);
      };
    }
    setTimeout(() => {
      window.location.reload();
    }, 500);
    return () => {
      client.onopen = null as any;
    };
  }, [username]);

  return <Main username={username} />;
};

export default MainWrapper;

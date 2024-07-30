import React, { useState, useEffect } from "react";
import { w3cwebsocket as W3CWebSocket, IMessageEvent } from "websocket";
import {
  BrowserRouter as Router,
  Route,
  Routes,
  useNavigate,
} from "react-router-dom";
import './App.css';


const client = new W3CWebSocket("ws://localhost:8080");

const App: React.FC = () => {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<Login />} />
        <Route path="/new-page" element={<NewPage />} />
      </Routes>
    </Router>
  );
};

const Login: React.FC = () => {
  const [message1, setMessage1] = useState<string>("");
  const [message2, setMessage2] = useState<string>("");
  const [isConnected, setIsConnected] = useState<boolean>(false);
  const [response, setResponse] = useState<string>("");
  const navigate = useNavigate();

  useEffect(() => {
    client.onopen = () => {
      console.log("Polaczono");
      setIsConnected(true);
    };

    client.onclose = () => {
      console.log("Brak polaczenia");
      setIsConnected(false);
    };

    client.onmessage = (message: IMessageEvent) => {
      if (typeof message.data === "string") {
        console.log("Received Data:", message.data);
        setResponse(message.data);
        if (message.data === "0") {
          console.log("Received non-string message:", message.data);
          setResponse("Zly login lub haslo!");
        } else {
          navigate("/new-page");
        }
      }
    };
  }, [navigate]);

  const handleSend = () => {
    if (isConnected) {
      const combinedMessage = `${message1} ${message2}`;
      client.send(combinedMessage);
      setResponse(`Wysłano: ${combinedMessage}`);
    }
  };

  return (
    <div>
      <h1>Login:</h1>
      <div>
        <h2>
          <input
            type="text"
            value={message1}
            onChange={(e) => setMessage1(e.target.value)}
            placeholder="Wpisz login"
          />
        </h2>
      </div>
      <div>
        <br></br>
        <h1>Haslo:</h1>
        <h2>
          <input
            type="text"
            value={message2}
            onChange={(e) => setMessage2(e.target.value)}
            placeholder="Haslo"
          />{" "}
        </h2>
      </div>
      <h1>
        <button onClick={handleSend}>Zaloguj</button>
        <p>{response}</p>
      </h1>
    </div>
  );
};

const NewPage: React.FC = () => {
  return <div>Witamy na nowej stronie!</div>;
};

export default App;

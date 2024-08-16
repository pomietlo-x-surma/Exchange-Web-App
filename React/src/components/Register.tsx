import React, { useState, useEffect } from "react";
import { w3cwebsocket as W3CWebSocket, IMessageEvent } from "websocket";
import { useNavigate } from "react-router-dom";

const client = new W3CWebSocket("ws://localhost:8080");

const Register: React.FC = () => {
  const [message1, setMessage1] = useState<string>("");
  const [message2, setMessage2] = useState<string>(""); 
  const [message3, setMessage3] = useState<string>(""); 
  const [message4, setMessage4] = useState<string>(""); 
  const [response, setResponse] = useState<string>("");
  const [isConnected, setIsConnected] = useState<boolean>(false);
  const navigate = useNavigate();

  useEffect(() => {
    client.onopen = () => {
      console.log("połączono");
      setIsConnected(true);
    };
    client.onclose = () => {
      console.log("Brak połączenia");
      setIsConnected(false);
    };

    client.onmessage = (message: IMessageEvent) => {
      if (typeof message.data === "string") {
        if (message.data[0] === "0") {
          const log = message.data.substring(1);
          navigate(`/Main/${log}`);
        } else {
          setResponse(message.data);
        }
      }
    };
  }, [navigate]);

  const handleSend = () => {
    if (isConnected) {
      const combinedMessage = `1,${message1} ${message2} ${message3} ${message4}`;
      client.send(combinedMessage);
      setResponse(`Wysłano: ${combinedMessage}`);
    }
  };

  return (
    <div className="container" style={{height: "15vw", fontSize: "2vw"}}>
      <p style={{fontSize: "5vw", position: "relative", top: "2vw"}}>Rejestracja</p>
        <p style={{margin: "0vw", position: "relative", top: "-3vw"}}>E-mail</p>
        <br />
        <input
          value={message1}
          onChange={(e) => setMessage1(e.target.value)}
          placeholder="Wpisz E-mail"
        />
        <br />
        <p style={{margin: "0vw", position: "relative", top: "-3vw"}}>Login</p>
        <br />
        <input
          value={message2}
          onChange={(e) => setMessage2(e.target.value)}
          placeholder="Wpisz Login"
        />
        <br />
        <p style={{margin: "0vw", position: "relative", top: "-3vw"}}>Hasło</p>
        <br />
        <input
          type="password"
          value={message3}
          onChange={(e) => setMessage3(e.target.value)}
          placeholder="Wpisz Hasło"
        />
        <br />
        <p style={{margin: "0vw", position: "relative", top: "-3vw"}}>Powtórz hasło</p>
        <br />
        <input
          type="password"
          value={message4}
          onChange={(e) => setMessage4(e.target.value)}
          placeholder="Wpisz Hasło ponownie"
        />
        <br />
        <button onClick={handleSend} style={{position:"relative", top: "-3.5vw", padding: "0.8vw"}}>Zaloguj</button>
        <p style={{position: "relative", top: "-5vw", fontSize: "1.5vw"}}>{response}</p>
    </div>
  );
};

export default Register;

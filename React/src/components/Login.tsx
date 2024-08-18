import React, { useState, useEffect } from "react";
import { w3cwebsocket as W3CWebSocket, IMessageEvent } from "websocket";
import { Link, useNavigate } from "react-router-dom";

const client = new W3CWebSocket("ws://localhost:8080");

const Login: React.FC = () => {
  const [message1, setMessage1] = useState<string>("");
  const [message2, setMessage2] = useState<string>("");
  const [isConnected, setIsConnected] = useState<boolean>(false);
  const [response, setResponse] = useState<string>("");
  const navigate = useNavigate();

  useEffect(() => {
    client.onopen = () => {
      console.log("Połączono");
      setIsConnected(true);
    };
    

    client.onclose = () => {
      console.log("Brak połączenia");
      setIsConnected(false);
    };

    client.onmessage = (message: IMessageEvent) => {
      if (typeof message.data === "string") {
        console.log("Received Data:", message.data);
        setResponse(message.data);
        if (message.data === "5") {
          console.log("Received non-string message:", message.data);
          setResponse("Zły login lub hasło!");
        } else {
          localStorage.setItem("username", message.data);
          navigate(`/Main/${message.data}`);
          window.location.reload();
        }
      }
    };
  }, [navigate]);

  const handleSend = () => {
    if (isConnected) {
      const combinedMessage = `0,${message1} ${message2}`;
      client.send(combinedMessage);
      setResponse(`Wysłano: ${combinedMessage}`);
    }
  };

  return (
    <div>
      <p style={{fontSize: "4vw", position: "relative", top: "-5vw", left: "-2vw"}}>E-mail:</p>
        <input
            type="text"
            value={message1}
            onChange={(e) => setMessage1(e.target.value)}
            placeholder="Wpisz E-mail"
            style={{padding:"1vw", fontSize: "3vw", width: "30vw", height: "4vw", top: "-8vw", position: "relative", margin:"0vw", left: "6vw"}}
          />
        <p style={{fontSize: "4vw", position: "relative", top: "-8vw", left: "-2vw"}}>Hasło:</p>
          <input
            type="password"
            value={message2}
            onChange={(e) => setMessage2(e.target.value)}
            placeholder="Hasło"
            style={{padding:"1vw", fontSize: "3vw", width: "30vw", height: "4vw", top: "-12vw", position: "relative", left: "8vw"}}
          />
        <button onClick={handleSend} style={{fontSize: "3vw", paddingBottom: "5vw", paddingTop:"1vw", height: "7vw",width: "20vw", 
          margin: "0vw", top: "-3vw",position: "relative",left: "-16vw",   flexDirection: "column", justifyContent: "center", alignItems: "center"}}>
          Zaloguj</button>
        <p style={{fontSize: "2vw"}}>{response}</p>
      <p style={{fontSize: "2vw", margin: "-5vw", position: "relative", left: "-2vw", top:"-0vw"}}>
        <Link to="/Register" className="Register-link">
          Utwórz nowe konto
        </Link>
      </p>
    </div>
  );
};

export default Login;

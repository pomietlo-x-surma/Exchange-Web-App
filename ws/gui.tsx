import React, { useState, useEffect } from "react";
import { w3cwebsocket as W3CWebSocket, IMessageEvent } from "websocket";
import {
  BrowserRouter as Router,
  Route,
  Routes,
  useNavigate,
  Link,
} from "react-router-dom";
import "./App.css";

const client = new W3CWebSocket("ws://localhost:8080");

const App: React.FC = () => {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<Login />} />
        <Route path="/new-page" element={<NewPage />} />
        <Route path="/create-account" element={<CreateAccount />} />
      </Routes>
    </Router>
  );
};
const CreateAccount: React.FC = () => {
  const [message1, setMessage1] = useState<string>(""); //login
  const [message2, setMessage2] = useState<string>(""); //mail
  const [message3, setMessage3] = useState<string>(""); //haslo
  const [message4, setMessage4] = useState<string>(""); //pwt haslo
  const [response, setResponse] = useState<string>("");
  const [isConnected, setIsConnected] = useState<boolean>(false);
  const navigate = useNavigate();
  useEffect(() => {
    client.onopen = () => {
      console.log("polaczono");
      setIsConnected(true);
    };
    client.onclose = () => {
      console.log("Brak połączenia");
      setIsConnected(false);
    };

    client.onmessage = (message: IMessageEvent) => {
      if (typeof message.data == "string") {
        console.log("Received Data:", message.data);
        setResponse(message.data);
        if (message.data == "0") {
          console.log("bledna e-mail lub login");
          setResponse("0");
        } else if (message.data == "1") {
          console.log("taki uzytkownik juz istnieje!");
          setResponse("1");
        } else if (message.data == "2") {
          console.log(
            "haslo musi skladac się z:\n-malej litery\n-duzej litery\n-liczby\n-znaku specjalnego (np. !, @, #)"
          );
          setResponse("2");
        } else if (message.data == "3") {
          console.log("hasla sa rozne!");
          setResponse("3");
        } else {
          navigate("/new-page");
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
    <>
      <h2>Login
        <br/>
        <input
          value={message1}
          onChange={(e) => setMessage1(e.target.value)}
          placeholder="Wpisz login"
        ></input>
      <br/>
      E-mail
      <br/>
      <input
          value={message2}
          onChange={(e) => setMessage2(e.target.value)}
          placeholder="Wpisz E-mail"
        ></input>
      <br/>
      Haslo
      <br/>
      <input
          value={message3}
          onChange={(e) => setMessage3(e.target.value)}
          placeholder="Wpisz E-mail"
        ></input>
<br/>
      Powtorz haslo
      <br/>
      <input
          value={message4}
          onChange={(e) => setMessage4(e.target.value)}
          placeholder="Wpisz E-mail"
        ></input>
        <br/>
    <button onClick={handleSend}>Zaloguj</button>
    <p>{response}</p>
    </h2>
    </>
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
          setResponse("Zly login lub haslo!");
        } else {
          navigate("/new-page");
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
        <h1>Hasło:</h1>
        <h2>
          <input
            type="password"
            value={message2}
            onChange={(e) => setMessage2(e.target.value)}
            placeholder="Hasło"
          />{" "}
        </h2>
      </div>
      <h1>
        <button onClick={handleSend}>Zaloguj</button>
        <p>{response}</p>
      </h1>
      <h2>
        <Link to="/create-account" className="create-account-link">
          Utwórz nowe konto
        </Link>
      </h2>
    </div>
  );
};

const NewPage: React.FC = () => {
  return <div>Witamy na nowej stronie!</div>;
};

export default App;

import React, { useState, useEffect } from "react";
import { w3cwebsocket as W3CWebSocket, IMessageEvent } from "websocket";
import {
  BrowserRouter as Router,
  Route,
  Routes,
  useNavigate,
  useParams,
  Link,
} from "react-router-dom";
import "./App.css";

const client = new W3CWebSocket("ws://localhost:8080");

const App: React.FC = () => {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<Login />} />
        <Route path="/new-page/:message" element={<NewPage />} />
        <Route path="/create-account" element={<CreateAccount />} />
      </Routes>
    </Router>
  );
};

const CreateAccount: React.FC = () => {
  const [message1, setMessage1] = useState<string>(""); // login
  const [message2, setMessage2] = useState<string>(""); // mail
  const [message3, setMessage3] = useState<string>(""); // haslo
  const [message4, setMessage4] = useState<string>(""); // powtorz haslo
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
        if (message.data === "0") {
          navigate(`/new-page/${message.data}`);
        } else {
          console.log("Received Data:", message.data);
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
    <div className="container">
      <h1>Rejestracja</h1>
      <h2>
        E-mail
        <br />
        <input
          value={message1}
          onChange={(e) => setMessage1(e.target.value)}
          placeholder="Wpisz E-mail"
        />
        <br />
        Login
        <br />
        <input
          value={message2}
          onChange={(e) => setMessage2(e.target.value)}
          placeholder="Wpisz Login"
        />
        <br />
        Hasło
        <br />
        <input
          value={message3}
          onChange={(e) => setMessage3(e.target.value)}
          placeholder="Wpisz Hasło"
        />
        <br />
        Powtórz hasło
        <br />
        <input
          value={message4}
          onChange={(e) => setMessage4(e.target.value)}
          placeholder="Wpisz Hasło ponownie"
        />
        <br />
        <button onClick={handleSend}>Zaloguj</button>
        <p>{response}</p>
      </h2>
    </div>
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
          setResponse("Zły login lub hasło!");
        } else {
          navigate(`/new-page/${message.data}`);
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
      <h1>E-mail:</h1>
      <div>
        <h2>
          <input
            type="text"
            value={message1}
            onChange={(e) => setMessage1(e.target.value)}
            placeholder="Wpisz E-mail"
          />
        </h2>
      </div>
      <div>
        <h1>Hasło:</h1>
        <h2>
          <input
            type="password"
            value={message2}
            onChange={(e) => setMessage2(e.target.value)}
            placeholder="Hasło"
          />
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
  const [selectedCurrency, setSelectedCurrency] = useState('Wybierz walutę');
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
        // if (message.data === "5") {
        //   console.log("Received non-string message:", message.data);
        //   setResponse("Zły login lub hasło!");
        // } else {
        //   navigate(`/new-page/${message.data}`);
        // }
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
  const handleSelect = (currency: any) => {
    setSelectedCurrency(currency);
  };
  return (
    <>
      <h3>
        Witaj...
        <br />
        <br />
        Aktualny kurs wybranej waluty: <br />
        <div className="rect-1">
          <span className="text">USD to PLN:</span>
        </div>
        <p>Wykres zmien kursu wybranej waluty</p>
        <h4 className="rect-2"></h4>
      </h3>

      <h4>
        twoje saldo
        <h5>
          <button onClick={handleSend}>Dokonaj tranzakcji</button>
        </h5>
      </h4>
      <div className="dropdown">
        szim
        <div className="button1">
          <button>waluta</button>
          <div className="content">
          <a href="#" onClick={() => handleSelect('USD')}>USD</a>
            <a href="#" onClick={() => handleSelect('PLN')}>PLN</a>
            <a href="#" onClick={() => handleSelect('EUR')}>EUR</a>
          </div>
        </div>
      </div>
      <div className="dropdown">
        szim
        <div className="button1">
          <button>waluta</button>
          <div className="content">
            <a href="#" onClick={() => handleSelect('USD')}>USD</a>
            <a href="#" onClick={() => handleSelect('PLN')}>PLN</a>
            <a href="#" onClick={() => handleSelect('EUR')}>EUR</a>
            </div>
        </div>
      </div>
    </>
  );
};

export default App;

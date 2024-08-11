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
  const [selectedCurrency1, setSelectedCurrency1] = useState("USD");
  const [selectedCurrency2, setSelectedCurrency2] = useState("PLN");
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
      const combinedMessage = `11,${message1} ${message2}`;
      client.send(combinedMessage);
      setResponse(`Wysłano: ${combinedMessage}`);
    }
  };
  const handleSend2 = () => {
    if (isConnected) {
      const combinedMessage = `3,${selectedCurrency1} ${selectedCurrency2}`;
      client.send(combinedMessage);
      console.log(`Waluta ${combinedMessage}`);
    }
  };
  const handleSelect1 = (currency: any) => {
    setSelectedCurrency1(currency);
  };
  const handleSelect2 = (currency: any) => {
    setSelectedCurrency2(currency);
  };
  return (
    <>
      <h3 style={{top: '0vw', margin: '1vw', position: 'relative'}}>
        <p
          style={{
            color: "white",
            left: "1vw",
            position: "relative",
            margin: "0px",
            textAlign: "left",
          }}
        >
          <span style={{ fontSize: "5dvmin", fontWeight: "bold" }}>
            Witaj username!
          </span>
          <br />
          <br />
          <span style={{ fontSize: "3dvmin" }}>Kurs wybranej waluty:</span>
        </p>
        <br />
        <p className="plot">Wykres waluty:</p>
        <p className="saldo">Twoje saldo:</p>
        <div
          className="currencychange"
          style={{ left: "15vw", position: "relative" }}
        >
          <p className="dropdown-button" onClick={handleSend}>
            {selectedCurrency1}
          </p>
          <div className="dropdown-content">
            <a onClick={() => {handleSelect1("dollar");handleSend2()}}>USD</a>
            <a onClick={() => {handleSelect1("zloty");handleSend2()}}>PLN</a>
            <a onClick={() => {handleSelect1("euro");handleSend2()}}>EUR</a>
          </div>
        </div>
        <div className="currencychange">
          <p className="dropdown-button" onClick={handleSend}>
            {selectedCurrency2}
          </p>
          <div className="dropdown-content">
          <a onClick={() => {handleSelect2("dollar");handleSend2()}}>USD</a>
            <a onClick={() => {handleSelect2("zloty");handleSend2()}}>PLN</a>
            <a onClick={() => {handleSelect2("euro");handleSend2()}}>EUR</a>

          </div>
          <p style={{fontSize: '8vw', left: '10vw', top: '-32vw', position: 'absolute', margin: '0vw'  }}>→</p>
      <p style={{fontSize: '6vw', left: '26vw', top: '-30vw', position: 'absolute', margin: '0vw'  }}>=</p>
      <p style={{fontSize: '2.5vw', left: '31vw', top: '-28.5vw', position: 'absolute', margin: '0vw', backgroundColor: 'red',
        border: 'solid white 0.5vw ', borderRadius: '1vw', padding: '1vw'
        }}>{response}</p>
        </div>
      </h3>
    </>
  );
};

export default App;

import React, { useState, useEffect } from "react";
import { w3cwebsocket as W3CWebSocket, IMessageEvent } from "websocket";

interface MainProps {
  username: string;
}

const client = new W3CWebSocket("ws://localhost:8080");

const Main: React.FC<MainProps> = ({ username }) => {
  const [selectedCurrency1, setSelectedCurrency1] = useState("EUR");
  const [selectedCurrency2, setSelectedCurrency2] = useState("PLN");
  const [selectedCurrency3, setSelectedCurrency3] = useState("PLN");
  const [selectedCurrency4, setSelectedCurrency4] = useState("EUR");
  const [selectedstate, setState] = useState("");
  const [message1, setMessage1] = useState<string>("");
  const [message2, setMessage2] = useState<string>("");
  const [isConnected, setIsConnected] = useState<boolean>(false);
  const [response, setResponse] = useState<string>("");
  const [response2, setResponse2] = useState<string>("");
  const [error, setError] = useState<string>("");

  useEffect(() => {
    client.onopen = () => {
      console.log("Połączono");
      setIsConnected(true);

      // Wysłanie informacji o użytkowniku
      if (username) {
        const usernameMessage = `4,${username}`;
        client.send(usernameMessage);
        console.log(`Wysłano wiadomość: ${usernameMessage}`);
      }
    };

    client.onclose = () => {
      console.log("Brak połączenia");
      setIsConnected(false);
    };

    client.onmessage = (message: IMessageEvent) => {
      console.log(message.data);
      if (typeof message.data === "string" && message.data.slice(0, 2) === "ZZ") {
        setResponse2(message.data.substring(2));
      } else if (typeof message.data === "string" && message.data[0] === "Z") {
        const [money, code] = message.data.split(" ");
        const base64str = `data:image/png;base64,${code}`;
        setResponse(money.substring(1));
        if (selectedCurrency1 !== selectedCurrency2) {
          setMessage1(base64str);
        }
      } else if (typeof message.data === "string" && message.data[0] === "Y") {
        setMessage2(message.data.substring(1));
      } else if (typeof message.data === "string" && message.data[0] === "W") {
        setState(message.data.substring(1));
        setError(" ");
      } else if (typeof message.data === "string" && message.data[0] === "E") {
        setError(message.data.substring(1));
      }
    };
  }, [username]);

  useEffect(() => {
    if (isConnected && username) {
      const combinedMessage = `3,${selectedCurrency2} ${selectedCurrency1}`;
      client.send(combinedMessage);
      console.log(`Wysłano wiadomość: ${combinedMessage}`);
    }
  }, [selectedCurrency1, selectedCurrency2, isConnected, username]);

  useEffect(() => {
    if (isConnected) {
      const combinedMessage = `3,${selectedCurrency3} ${selectedCurrency4} ${message2}0`;
      client.send(combinedMessage);
    }
  }, [selectedCurrency3, selectedCurrency4, isConnected]);

  const handleSelect1 = (currency: any) => {
    setSelectedCurrency1(currency);
  };

  const handleSelect2 = (currency: any) => {
    setSelectedCurrency2(currency);
  };
  const handleSelect3 = (currency: any) => {
    setSelectedCurrency3(currency);
  };
  const handleSelect4 = (currency: any) => {
    setSelectedCurrency4(currency);
  };
  const handleSend = () => {
    if (isConnected) {
      const combinedMessage = `6,${username} ${selectedCurrency3} ${selectedCurrency4} ${message2}`;
      client.send(combinedMessage);
      console.log(`Wysłano wiadomość: ${combinedMessage}`);
    }
  };
  return (
    <>
    
      <h3 style={{ top: "-22vw", margin: "-2vw", height: "0vw" }}>
        <p
          style={{
            color: "white",
            left: "1vw",
            position: "relative",
            margin: "0px",
            textAlign: "left",
          }}
        >
          <span
            style={{
              fontSize: "5vw",
              fontWeight: "bold",
              top: "0vw",
              position: "relative",
            }}
          >
            Witaj {username}!
          </span>
          <br />
          <br />
          <span style={{ fontSize: "3vw", position: "relative", top: "-4vw" }}>
            Kurs wybranej waluty:
          </span>
        </p>
        <br />
        <p className="plot">
          Wykres waluty:
          <img
            src={message1}
            alt="Image"
            style={{
              position: "absolute",
              left: "0vw",
              zIndex: 1,
              width: "40vw",
              margin: "0vw",
              height: "17vw",
              top: "3vw",
            }}
          ></img>
        </p>
        <p className="saldo" style={{ top: "23vw" }}>
          Twoje saldo:
          {selectedstate.split("  ").map(
            (line, index) =>
              line.trim() && (
                <span key={index}>
                  <br />
                  {line}
                </span>
              )
          )}
        </p>
        <div
          className="currencychange"
          style={{ left: "15vw", position: "relative" }}
        >
          <p className="dropdown-button">{selectedCurrency1}</p>
          <div className="dropdown-content">
            <a onClick={() => handleSelect1("USD")}>USD</a>
            <a onClick={() => handleSelect1("PLN")}>PLN</a>
            <a onClick={() => handleSelect1("EUR")}>EUR</a>
          </div>
        </div>
        <div className="currencychange">
          <p className="dropdown-button">{selectedCurrency2}</p>
          <div className="dropdown-content">
            <a onClick={() => handleSelect2("USD")}>USD</a>
            <a onClick={() => handleSelect2("PLN")}>PLN</a>
            <a onClick={() => handleSelect2("EUR")}>EUR</a>
          </div>
        </div>
        <p
          style={{
            fontSize: "9vw",
            left: "9vw",
            top: "9vw",
            position: "absolute",
            margin: "0.5vw",
          }}
        >
          →
        </p>
        <p
          style={{
            fontSize: "6vw",
            left: "25.5vw",
            top: "11.5vw",
            position: "absolute",
            margin: "0.5vw",
          }}
        >
          =
        </p>
        <p //result box
          style={{
            fontSize: "2.5vw",
            left: "31vw",
            top: "13vw",
            position: "absolute",
            margin: "0.5vw",
            backgroundColor: "red",
            border: "solid white 0.5vw",
            borderRadius: "1vw",
            padding: "1vw",
            minHeight: "4vw",
            minWidth: "10vw",
          }}
        >
          {response}
        </p>
        <input
          placeholder="Wpisz kwote"
          type="number" 
          step="1"
          onChange={(e) => setMessage2(e.target.value)}
          style={{
            position: "relative",
            height: "3vw",
            width: "11.5vw",
            left: "55vw",
            top: "-29.5vw",
            zIndex: 20,
            margin: "0vw",
          }}
        />
        <div className="currencychange" style={{ left: "44.5vw", top: "-5vw" }}>
          <p className="dropdown-button">{selectedCurrency3}</p>
          <div className="dropdown-content">
            <a onClick={() => handleSelect3("USD")}>USD</a>
            <a onClick={() => handleSelect3("PLN")}>PLN</a>
            <a onClick={() => handleSelect3("EUR")}>EUR</a>
          </div>
        </div>
        <p
          style={{
            position: "relative",
            left: "51vw",
            top: "-40vw",
            fontSize: "9vw",
            margin: "0vw",
          }}
        >
          →
        </p>
        <p
          style={{
            position: "relative",
            height: "5vw",
            width: "14vw",
            left: "85vw",
            top: "-48.7vw",
            zIndex: 10,
            margin: "0vw",
            backgroundColor: "gray",
            color: "black",
            border: "white solid 0.5vw",
            borderRadius: "0.3vw",
            fontSize: "3vw",

          }}
        >{response2}</p>
        <div
          className="currencychange"
          style={{ left: "74.5vw", top: "-24.5vw" }}
        >
          <p className="dropdown-button">{selectedCurrency4}</p>
          <div className="dropdown-content">
            <a onClick={() => handleSelect4("USD")}>USD</a>
            <a onClick={() => handleSelect4("PLN")}>PLN</a>
            <a onClick={() => handleSelect4("EUR")}>EUR</a>
          </div>
        </div>
        <p style={{fontSize: "2vw", left: "50vw", top: "-61vw", position:"relative", margin: "-3vw" }}>{error}</p>
        <button onClick={handleSend} style={{position: "relative", top:"-58vw", left: "63vw", fontSize: "2vw", padding: "0.5vw", border: "solid white 0.2vw", borderRadius: "0.5vw", zIndex: 100, margin: "0vw" }}>dokonaj tranzakcji</button>
      </h3>
    </>
  );
};

export default Main;

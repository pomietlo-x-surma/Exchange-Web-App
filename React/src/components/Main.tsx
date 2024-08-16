import React, { useState, useEffect } from "react";
import { w3cwebsocket as W3CWebSocket, IMessageEvent } from "websocket";

interface MainProps {
  username: string;
}

const client = new W3CWebSocket("ws://localhost:8080");

const Main: React.FC<MainProps> = ({ username }) => {
  const [selectedCurrency1, setSelectedCurrency1] = useState("EUR");
  const [selectedCurrency2, setSelectedCurrency2] = useState("PLN");
  const [selectedstate, setState] = useState("");
  const [message1, setMessage1] = useState<string>("");
  const [isConnected, setIsConnected] = useState<boolean>(false);
  const [response, setResponse] = useState<string>("");

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
      console.log(message.data);
      if (typeof message.data === "string" && message.data[0] == "Z") {
        const [money, code] = message.data.split(" ");
        const base64str = `data:image/png;base64,${code}`;
        setResponse(money.substring(1));
        if (selectedCurrency1 !== selectedCurrency2) {
          setMessage1(base64str);
        }
      } else if (typeof message.data === "string") {
        setState(message.data);
      }
    };
  }, [username, selectedCurrency1, selectedCurrency2]);

  useEffect(() => {
    if (isConnected && username) {
      const combinedMessage = `3,${selectedCurrency2} ${selectedCurrency1}`;
      client.send(combinedMessage);
      console.log(`Wysłano wiadomość: ${combinedMessage}`);
      const usernameMessage = `4,${username}`;
      client.send(usernameMessage);
      console.log(`Wysłano wiadomość: ${usernameMessage}`);
    }
  }, [selectedCurrency1, selectedCurrency2, isConnected, username]);

  const handleSelect1 = (currency: any) => {
    setSelectedCurrency1(currency);
  };

  const handleSelect2 = (currency: any) => {
    setSelectedCurrency2(currency);
  };
  
  return (
    <>
      <h3 style={{ top: "0vw", margin: "0vw", position: "relative" }}>
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
        <p className="saldo">
          Twoje saldo:
          {selectedstate.split("\n").map(
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
        <p
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
      </h3>
    </>
  );
};

export default Main;

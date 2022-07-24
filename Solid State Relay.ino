#include <ESP8266WiFi.h>//Includes ESP8266 Wifi library
//Defines representation of the pins used for each relay
#define Relay_01 16        //D0
#define Relay_02 5         //D1
#define Relay_03 4         //D2
#define Relay_04 0         //D3

//Create a server on port 80
//(default port where browsers send http requests)
WiFiServer server(80);

void setup()
{
  //Initializes Serial for logging purposes only
  Serial.begin(115200);

  Serial.print("inside void setup");
  //Sets the mode of all pins
  pinMode(Relay_01, OUTPUT);
  pinMode(Relay_02, OUTPUT);
  pinMode(Relay_03, OUTPUT);
  pinMode(Relay_04, OUTPUT);

  //Adjust the state of all pins
  digitalWrite(Relay_01, HIGH);
  digitalWrite(Relay_02, HIGH);
  digitalWrite(Relay_03, HIGH);
  digitalWrite(Relay_04, HIGH);

  Serial.print("Connected....!");//reporting current state (debug)
  //Makes the ESP connect to the WiFi network available at the place of use.
  //In our example the ssid of the network is networkWiFi and the password is passwordtest
  WiFi.begin("Pred@tor Gaming", "19111998");

  // As long as the ESP does not connect to the network
  while (WiFi.status() != WL_CONNECTED)
  {
    //We wait 100 milliseconds
    delay(100);
    Serial.print(".");
  }

  //If you arrived here, it's because you connected to the network,
  //then we show it on the serial monitor to have a feedback
  Serial.println("");
  Serial.println("connected!!");

  //Fixed IP settings. You can change it according to your network
  Serial.println(WiFi.localIP());
  //send the configuration
  //iFi.config(ip, gateway, subnet);

  //Initialize the server we created on port 80
  server.begin();

  //We show on the serial monitor the IP that the ESP has
  //to check if it is the same as the one we configured
  Serial.print("server on: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  //Checks if any clients are trying to connect
  WiFiClient client = server.available();
  if (!client)
  {
    //If there is no customer we can return it as there is nothing to do
    return;
  }
  //We read the request
  String req = client.readStringUntil('\r');
  req.replace("GET /", "");
  req.replace(" HTTP/1.1","");
  //Serial.print("Request: ");
  Serial.println(req);

  //This is the html we will return to the client
  //It basically consists of two buttons (ON and OFF) for each relay
  //The part that interests us is the <a href=' with the action linked to each button
  //When we click on one of these buttons this information will reach the ESP for
  //let it check which action it should perform
  //The part inside '<style>' is just for us to change the look of the page
  //which will be displayed, you can change it however you want
  String html =
    "<html>"
    "<head>"
    "<meta name='viewport' content='width=device-width, initial-scale=1, user-scalable=no'/>"
    "<title>Controle Esp8266</title>"
    "<style>"
    "body{"
    "text-align: center;"
    "font-family: sans-serif;"
    "font-size:25px;"
    "padding: 25px;"
    "}"
    "p{"
    "color:#444;"
    "}"
    "button{"
    "outline: none;"
    "border: 2px solid #1fa3ec;"
    "border-radius:18px;"
    "background-color:#FFF;"
    "color: #1fa3ec;"
    "padding: 5px 25px;"
    "}"
    "button:active{"
    "color: #fff;"
    "background-color:#1fa3ec;"
    "}"
    "button:hover{"
    "border-color:#0000ff;"
    "}"
    "</style>"
    "</head>"
    "<body>"
    "<p>01 - "
    "<a href='Relay_01On'><button>ON</button></a>"
    "<a href='Relay_01Off'><button>OFF</button></a></p>"
    "<p>02 - "
    "<a href='Relay_02On'><button>ON</button></a>"
    "<a href='Relay_02Off'><button>OFF</button></a></p>"
    "<p>03 - "
    "<a href='Relay_03On'><button>ON</button></a>"
    "<a href='Relay_03Off'><button>OFF</button></a></p>"
    "<p>04 - "
    "<a href='Relay_04On'><button>ON</button></a>"
    "<a href='Relay_04Off'><button>OFF</button></a></p>"
    "</body>"
    "</html>";
  //Escreve o html no buffer que será enviado para o cliente
  client.print(html);
  //Envia os dados do buffer para o cliente
  client.flush();

  //A partir daqui, verificamos se a requisição possui algum comando de
  //atuação sobre os relés
  if (req.indexOf("Relay_01On") != -1)
  {
    digitalWrite(Relay_01, LOW);
  }
  else if (req.indexOf("Relay_01Off") != -1)
  {
    digitalWrite(Relay_01, HIGH);
  }

  if (req.indexOf("Relay_02On") != -1)
  {
    digitalWrite(Relay_02, LOW);
  }
  else if (req.indexOf("Relay_02Off") != -1)
  {
    digitalWrite(Relay_02, HIGH);
  }

  if (req.indexOf("Relay_03On") != -1)
  {
    digitalWrite(Relay_03, LOW);
  }
  else if (req.indexOf("Relay_03Off") != -1)
  {
    digitalWrite(Relay_03, HIGH);
  }

  if (req.indexOf("Relay_04On") != -1)
  {
    digitalWrite(Relay_04, LOW);
  }
  else if (req.indexOf("Relay_04Off") != -1)
  {
    digitalWrite(Relay_04, HIGH);
  }
  delay(200);//waits for information traffic to complete
  //Close the connection with the client
  client.stop();
  //Serial.println("Client disconnected");
}

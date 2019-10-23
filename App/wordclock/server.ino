char webpage[] PROGMEM = R"=====(

  <!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta http-equiv="X-UA-Compatible" content="ie=edge" />
    <title>w{}rdclock</title>
       <script>
      var xhttp = new XMLHttpRequest();
      function setColor(e) {
        var rgbString = e.style.backgroundColor
          .replace("rgb(", "")
          .replace(")", "");

        var rgbArray = rgbString.split(", ");
        console.log(rgbArray);
        xhttp.open(
          "GET",
          "http://192.168.1.7/setColor?r=" +
            rgbArray[0] +
            "&g=" +
            rgbArray[1] +
            "&b=" +
            rgbArray[2],
          true
        );
        xhttp.send();
      }
    </script>
    <style>

      html,
      body {
        padding: 0;
        margin: 0;
      }
      body {
        background: #000;
      }
      .color-grid {
        width: 100%;
        height: 100vh;
        display: grid;
        grid-template-columns: 1fr 1fr 1fr 1fr 1fr;
        grid-template-rows: 1fr;
        justify-content: center;
        align-items: center;
        text-align: center;
      }
      .color-grid__color {
        height: 100%;
      }
    </style>

  </head>
  <body>
    <div class="color-grid">
      <div
        style="background-color:#026873"
        class="color-grid__color"
        onClick="setColor(this)"
      ></div>
      <div
        onClick="setColor(this)"
        style="background-color: #03a6a6"
        class="color-grid__color"
      ></div>
      <div
        onClick="setColor(this)"
        style="background-color:#bf4545"
        class="color-grid__color"
      ></div>
      <div
        onClick="setColor(this)"
        style="background-color:#d96e48"
        class="color-grid__color"
      ></div>
      <div
        onClick="setColor(this)"
        style="background-color:#f2b28d"
        class="color-grid__color"
      ></div>
    </div>


  </body>
</html>

)=====";

char formPage[] PROGMEM = R"=====(
<html>
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>cl{}ck</title>
    <style>
      html,
      body {
        padding: 0px;
        margin: 0;
        background: #000;
        color: #fff;
        width: 100%;
        height: 100vh;
        display: flex;
        justify-content: center;
        align-items: center;
        font-family: "Fira Code", monospace;
      }
      .container {
        width: 100%;
        height: 100vh;
        border: 1px solid white;
      }
      form {
        display: flex;
        flex-direction: column;
        width: 90%;
        opacity: 0;
        max-width: 500px;
        animation: show 2s;
        animation-delay: 5s;
        animation-fill-mode: forwards;
      }

      form.pending .group {
        opacity: 0;
        max-height: 1px;
      }
      form.pending button {
        background: none;
        font-size: 32px;
      }
      .group {
        margin: 10px 0;
        transition: all 1s;
        max-height: 200px;
        overflow: hidden;
      }
      label {
        display: block;
      }
      input,
      button {
        margin: 16px 0;
        border: 0px solid #222;
        padding: 10px 16px;
        background: #111;
        color: #ddd;
        width: 100%;
        box-sizing: border-box;
      }
      button {
        margin-top: 20px;
        width: 230px;
        align-self: center;
        transition: all 200ms;
      }
      button:active,
      button:focus {
        outline: none;
      }
      button:hover {
        background: #333;
        text-decoration: underline;
      }
      h1 {
        position: fixed;
        left: 0;
        right: 0;
        font-weight: 400;
        text-align: center;
        animation: down 0.5s ease-in;
        animation-delay: 5s;

        animation-fill-mode: forwards;
        transform: scale(2);
      }

      h1 span {
        opacity: 0;
        animation: logo 1s ease-in;
        animation-delay: 2s;
        animation-fill-mode: forwards;
      }
      button span {
        animation: fade 3s infinite;
      }

      button span:nth-child(2) {
        animation-delay: 0.333s;
      }

      button span:nth-child(3) {
        animation-delay: 0.666s;
      }

      @keyframes fade {
        0% {
          opacity: 0;
        }
        50% {
          opacity: 1;
        }
        100% {
          opacity: 0;
        }
      }
      @keyframes show {
        0% {
          opacity: 0;
        }
        100% {
          opacity: 1;
        }
      }
      @keyframes logo {
        0% {
          opacity: 0;
        }
        100% {
          opacity: 0.9;
        }
      }
      @keyframes down {
        0% {
          top: 50%;
          transform: scale(2);
        }
        100% {
          top: 90%;
          transform: scale(1);
        }
      }
    </style>
  </head>
  <body>
    <form>
      <div class="group">
        <label for="ssid">wifi-name</label>
        <input name="ssid" id="ssid" placeholder="z.B. MeinNetzwerk" />
      </div>
      <div class="group">
        <label for="password">passwort</label>
        <input name="password" id="password" type="password" />
      </div>
      <button>save</button>
    </form>
    <h1><span>cl</span>{}<span>ck</span></h1>
    <script>
      const form = document.querySelector("form");
      const btn = document.querySelector("button");
      form.addEventListener("submit", e => {
        e.preventDefault();
        form.classList.add("pending");
        btn.innerHTML = "<span>.</span><span>.</span><span>.</span>";

        var password = document.querySelector("#password").value;
        var ssid = document.querySelector("#ssid").value;
        var xhttp = new XMLHttpRequest();

        var jsonData = {
          ssid: ssid,
          password: password
        };
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            btn.innerHTML =
              '<span style="font-size: 18px">' + xhttp.responseText + "</span>";
          }
        };
        var url = `http://192.168.4.54/login`;
        xhttp.open("POST", url, true);
        xhttp.send(JSON.stringify(jsonData));
      });
    </script>
  </body>
</html>


)=====";
void initServer()
{
  server.on("/", handleRoot);
  server.on("/setColor", handleSetColor);
  server.on("/login", HTTP_POST, handleLogin);
  server.on("/inline", []() {
    server.send(200, "text/html", "<h1>this works as well</h1>");
  });
  server.onNotFound(handleNotFound);
  server.begin();
}
void handleRoot()
{
  server.send_P(200, "text/html", formPage);
}
void handleLogin()
{
  String data = server.arg("plain");
  Serial.println("data:");
  Serial.print(data);

  DynamicJsonBuffer jBuffer;
  JsonObject &jObject = jBuffer.parseObject(data);
  String ssid = jObject["ssid"];
  String password = jObject["password"];
  
  File configFile = SPIFFS.open("/config.json", "w");
  if (configFile)
  {
    jObject.printTo(configFile);
    configFile.close();
    server.send(200, "application/json", "{\"status\":\"ok\"}");
  }
  else
  {
    server.send(200, "application/json", "{\"status\":\"error\"}");
  }
  delay(500);

  wifiConnect();
  
}
void handleSetColor()
{
  Serial.println(server.arg("r"));
  Serial.println(server.arg("g"));
  Serial.println(server.arg("b"));
  color[0] = server.arg("r").toInt();
  color[1] = server.arg("g").toInt();
  color[2] = server.arg("b").toInt();

  server.send(200, "text/html", "<h1>Hallo, ich bins</h1>");
}

void handleNotFound()
{
  if (server.method() == HTTP_OPTIONS)
  {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Max-Age", "10000");
    server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "*");
    server.send(204);
  }
  else
  {
    server.send(404, "text/plain", "");
  }
}

import { createSignal, createResource, onCleanup } from "solid-js";
import ledIcon from "./assets/led_icon.svg";

function App() {
  const [count, setCount] = createSignal(0);
  const [ledStatus, setLedStatus] = createSignal("");

  const fetchLedStatus = async () => {
    const response = await fetch("/api/v1/led");

    const json = await response.json();
    setLedStatus(json["led on"] ? "on" : "off");
  };

  const [led] = createResource(fetchLedStatus);

  const interval = setInterval(fetchLedStatus, 500);

  onCleanup(() => clearInterval(interval));

  const storedCount = localStorage.getItem("count");

  if (storedCount != null) {
    setCount(parseInt(storedCount));
  }

  function updateCount(num: number) {
    setCount(count() + num);
    localStorage.setItem("count", count().toString());
  }

  const turnOnLed = async (on: boolean) => {
    const response = await fetch("/api/v1/led", {
      method: "POST",
      headers: {
        Accept: "application/json",
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ "led on": on }),
    });

    const json = await response.json();
    setLedStatus(json["led on"] ? "on" : "off");
  };

  return (
    <div class="container mx-0 flex min-w-full flex-col items-center px-10 py-10">
      <div class="outlined-4 rounded-full outline outline-offset-2">
        <img class="h-48 w-48 p-10" src={ledIcon} alt="Solid logo" />
      </div>
      <h1 class="my-3 text-5xl">
        LED Status: {led.loading ? "" : ledStatus()}
      </h1>
      <div>
        <button
          onClick={() => updateCount(1)}
          class="m-2 rounded bg-violet-500 px-4 py-2 font-bold text-white hover:bg-violet-700"
        >
          stored count is {count()}
        </button>
        <button
          class="m-2 rounded bg-blue-500 px-4 py-2 font-bold text-white hover:bg-blue-700"
          onClick={() => updateCount(count() * -1)}
        >
          reset count
        </button>
      </div>
      <div>
        <button
          class="m-2 rounded bg-blue-500 px-4 py-2 font-bold text-white hover:bg-blue-700"
          onClick={() => turnOnLed(true)}
        >
          Turn LED on
        </button>
        <button
          class="m-2 rounded bg-blue-500 px-4 py-2 font-bold text-white hover:bg-blue-700"
          onClick={() => turnOnLed(false)}
        >
          Turn LED off
        </button>
      </div>

      <div id="list"></div>
    </div>
  );
}

export default App;

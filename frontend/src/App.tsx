import { createSignal, onCleanup } from "solid-js";
import ledIcon from "./assets/led_icon.svg";

function App() {
  const [color, setColor] = createSignal(0);

  const fetchColor = async () => {
    const response = await fetch("/api/v1/led");

    const json = await response.json();
    setColor(json["color"]);
  };

  const interval = setInterval(fetchColor, 10);
  onCleanup(() => clearInterval(interval));

  const changeColor = async (c: number) => {
    const response = await fetch("/api/v1/led", {
      method: "POST",
      headers: {
        Accept: "application/json",
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ color: c }),
    });

    const json = await response.json();
    setColor(json["color"]);
  };

  function translateColor(c: number) {
    switch (c) {
      case 0:
        return "red";
      case 1:
        return "green";
      case 2:
        return "blue";
      default:
        return "violet";
    }
  }

  return (
    <div class="container mx-0 flex min-w-full flex-col items-center px-10 py-10">
      <div
        class={`outlined-4 rounded-full bg-${translateColor(
          color(),
        )}-500 outline outline-offset-2`}
      >
        <img class="h-48 w-48 p-10" src={ledIcon} alt="Solid logo" />
      </div>

      <h1 class="my-10 text-5xl">Lumenaries</h1>

      <button
        onClick={() => changeColor(0)}
        class="m-2 my-2 w-40 rounded bg-red-500 py-6 text-2xl font-bold text-white"
      >
        Red
      </button>

      <button
        onClick={() => changeColor(1)}
        class="m-2 my-2 w-40 rounded bg-green-500 py-6 text-2xl font-bold text-white"
      >
        Green
      </button>

      <button
        onClick={() => changeColor(2)}
        class="m-2 my-2 w-40 rounded bg-blue-500 py-6 text-2xl font-bold text-white"
      >
        Blue
      </button>
    </div>
  );
}

export default App;

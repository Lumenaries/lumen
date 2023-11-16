import { createSignal } from "solid-js";
import solidLogo from "./assets/solid.svg";

function App() {
  const [count, setCount] = createSignal(0);

  const storedCount = localStorage.getItem("count");

  if (storedCount != null) {
    setCount(parseInt(storedCount));
  }

  function updateCount(num: number) {
    setCount(count() + num);
    localStorage.setItem("count", count().toString());
  }

  return (
    <div class="container mx-0 flex min-w-full flex-col items-center px-10 py-10">
      <div>
        <img class="h-48 w-48" src={solidLogo} alt="Solid logo" />
      </div>
      <h1 class="mb-3 text-5xl">Solid</h1>
      <div>
        <button
          onClick={() => updateCount(1)}
          class="m-2 rounded bg-blue-500 px-4 py-2 font-bold text-white hover:bg-blue-700"
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
    </div>
  );
}

export default App;

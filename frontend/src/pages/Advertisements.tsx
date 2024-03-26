import Header from "../components/Header";

function Advertisements() {
  return (
    <>
      <Header>Advertisements</Header>
      <div class="flex justify-center font-poppins-normal">
        <div class="grid w-full max-w-xl grid-cols-1 gap-3">
          <input
            type="text"
            aria-label="advertisement message"
            placeholder="Enter ad message.."
            class="text-md block w-full rounded-lg border border-gray-300 bg-gray-50 p-2.5 placeholder:italic focus:border-gray-800 focus:outline-none focus:ring-0 focus:ring-gray-800"
          />
          <button class="justify-self-start rounded-full bg-lumen-primary px-2 py-1 font-poppins-medium text-white">
            New Ad
          </button>
        </div>
      </div>
    </>
  );
}

export default Advertisements;

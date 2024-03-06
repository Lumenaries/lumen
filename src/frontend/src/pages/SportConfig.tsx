import { MinusSign, PlusSign } from '../components/UtilityIcons'

// team 1 and team 2 text boxes when timer is not started
function SportConfig() {
  return (
    <div class="flex justify-center p-5">
      <div class="grid grid-cols-2 gap-28">
        <div>
          <div class="flex justify-center">
            <p class="pb-5 text-3xl">Team 1</p>
          </div>
          <button
            href="#"
            class="rounded-full bg-violet-900 p-1 text-4xl text-white"
          >
            <MinusSign />
          </button>
          <span class="mx-10 text-5xl">0</span>
          <button
            href="/team_1_add"
            class="rounded-full bg-violet-900 p-1 text-4xl text-white"
          >
            <PlusSign />
          </button>
        </div>

        <div>
          <div class="flex justify-center">
            <p class="pb-5 text-3xl">Team 2</p>
          </div>
          <button class="rounded-full bg-violet-900 p-1 text-4xl text-white">
            <MinusSign />
          </button>
          <span class="mx-10 text-5xl">0</span>
          <button class="rounded-full bg-violet-900 p-1 text-4xl text-white">
            <PlusSign />
          </button>
        </div>
      </div>
    </div>
  )
}

export default SportConfig

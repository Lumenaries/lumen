import { A } from '@solidjs/router'

// Game Advertisemnet Access settings in dropdown menu, battery
function App(props) {
  return (
    <div>
      <header>
        <nav class="border-gray-200 py-3 pb-4 pt-10">
          <div class="flex justify-center">
            <A href="/" class="font-prompt text-3xl tracking-wider">
              Lumenaries
            </A>
          </div>
        </nav>

        <nav>
          <div>
            <div class="mx-auto flex justify-center p-4">
              <div class="flex items-center">
                <ul class="mt-0 flex flex-row space-x-8 font-medium">
                  <li>
                    <A
                      href="/"
                      class="px-3 py-2"
                      activeClass="font-extrabold rounded-full bg-indigo-600 text-white"
                      inactiveClass="rounded-full outline outline-indigo-600"
                      end="true"
                    >
                      Games
                    </A>
                  </li>
                  <li>
                    <A
                      href="/advertisements"
                      class="px-3 py-2"
                      activeClass="font-extrabold rounded-full bg-indigo-600 text-white"
                      inactiveClass="rounded-full outline outline-indigo-600"
                      end="true"
                    >
                      Advertisements
                    </A>
                  </li>
                  <li>
                    <A
                      href="/sport_config"
                      class="px-3 py-2"
                      activeClass="font-extrabold rounded-full bg-indigo-600 text-white"
                      inactiveClass="rounded-full outline outline-indigo-600"
                      end="true"
                    >
                      Sport Config
                    </A>
                  </li>
                </ul>
              </div>
            </div>
          </div>
        </nav>
      </header>

      <div class="mt-10">{props.children}</div>
    </div>
  )
}

export default App

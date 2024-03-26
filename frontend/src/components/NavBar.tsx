import { A } from "@solidjs/router";

import {
  AdIcon,
  GameBoardIcon,
  SettingsIcon,
} from "../components/UtilityIcons";

function NavBar() {
  return (
    <nav class="fixed bottom-0 left-0 z-50 h-16 w-full border-t border-gray-200 bg-lumen-background lg:h-20">
      <div class="mx-auto grid h-full max-w-lg grid-cols-3">
        <NavElement name="Games" icon={<GameBoardIcon />} nav="/" />
        <NavElement name="Ads" icon={<AdIcon />} nav="/ads" />
        <NavElement name="Settings" icon={<SettingsIcon />} nav="/settings" />
      </div>
    </nav>
  );
}

function NavElement(props) {
  return (
    <A
      href={props.nav}
      class="group inline-flex flex-col items-center justify-center px-5 hover:bg-lumen-secondary"
      activeClass="bg-lumen-secondary active"
      inactiveClass="bg-lumen-background"
      end="true"
    >
      <div class="text-lumen-text group-hover:text-lumen-primary group-[.active]:text-lumen-primary">
        {props.icon}
      </div>
      <span class="font-poppins-medium text-sm font-medium text-lumen-text group-hover:font-poppins-bold group-hover:text-lumen-primary group-[.active]:font-poppins-bold group-[.active]:text-lumen-primary">
        {props.name}
      </span>
    </A>
  );
}

export default NavBar;

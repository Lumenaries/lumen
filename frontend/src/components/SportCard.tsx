import { A } from "@solidjs/router";

function SportCard(props) {
  return (
    <div>
      <A href={"/" + props.name.toLowerCase()} class="group">
        <div
          class="mb-2 flex justify-center"
          class="rounded-xl border border-2 border-lumen-primary stroke-lumen-primary p-1 group-hover:bg-lumen-primary group-hover:stroke-white"
        >
          {props.icon}
        </div>
        <p class="m-auto flex justify-center px-3 font-poppins-medium text-xl group-hover:font-poppins-bold group-hover:tracking-normal group-hover:text-lumen-primary">
          {props.name}
        </p>
      </A>
    </div>
  );
}

export default SportCard;

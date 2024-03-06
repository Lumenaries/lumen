function SportCard(props) {
  return (
    <a
      href="#"
      class="max-h-40 min-w-60 rounded-3xl border border-gray-200 p-3 shadow-sm hover:bg-gray-100"
    >
      <div class="flex">
        <div class="grow-0">{props.icon}</div>
        <span class="m-auto grow items-center px-3 text-center text-2xl">
          {props.name}
        </span>
      </div>
    </a>
  )
}

export default SportCard

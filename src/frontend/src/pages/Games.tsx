import SportCard from '../components/SportCard'
import {
  BaseballIcon,
  BasketballIcon,
  FootballIcon,
  LacrosseIcon,
  SoccerIcon,
  TennisIcon,
  VolleyballIcon,
} from '../components/SportIcons'

function Games() {
  return (
    <div class="flex justify-center">
      <div class="grid grid-cols-1 gap-10 px-5 md:grid-cols-2">
        <SportCard name="Baseball" icon={<BaseballIcon />} />
        <SportCard name="Basketball" icon={<BasketballIcon />} />
        <SportCard name="Football" icon={<FootballIcon />} />
        <SportCard name="Lacrosse" icon={<LacrosseIcon />} />
        <SportCard name="Soccer" icon={<SoccerIcon />} />
        <SportCard name="Tennis" icon={<TennisIcon />} />
        <SportCard name="Volleyball" icon={<VolleyballIcon />} />
      </div>
    </div>
  )
}

export default Games

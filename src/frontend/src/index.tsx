import { render } from 'solid-js/web'
import { Router, Route } from '@solidjs/router'

import './index.css'
import App from './App'
import Games from './pages/Games'
import Advertisements from './pages/Advertisements'
import SportConfig from './pages/SportConfig'

const root = document.getElementById('root')

if (import.meta.env.DEV && !(root instanceof HTMLElement)) {
  throw new Error(
    'Root element not found. Did you forget to add it to your index.html? Or maybe the id attribute got misspelled?'
  )
}

render(
  () => (
    <Router root={App}>
      <Route path="/" component={Games} />
      <Route path="/advertisements" component={Advertisements} />
      <Route path="/sport_config" component={SportConfig} />
    </Router>
  ),
  root!
)

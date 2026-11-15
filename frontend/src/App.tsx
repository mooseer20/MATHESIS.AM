import Topbar from "./components/Topbar";
import Sidebar from "./components/Sidebar";

import ProblemCard  from "./components/Problemcard";

import VizPanel from "./components/Vizpanel";
import Metrics from "./components/Metrics";

import StepsPanel from "./components/StepsPanel";


export default function App (){

  return ( 
    <div className = "app">
    <Topbar />
    <Sidebar />
    <main className="main">
      <ProblemCard />
      <VizPanel />
      <Metrics />
    </main>
    <StepsPanel />
    </div>
  ); 
}


import './App.css';

import Clicker from './components/Clicker';

function App() {
  return (
    <>
      <main className="bg-zinc-900 text-zinc-200 overflow-hidden">
        <div className="min-h-dvh flex flex-col justify-center items-center gap-2">
          <div className="">hi!</div>

          <Clicker />
        </div>
      </main>
    </>
  );
}

export default App;

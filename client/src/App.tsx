import './App.css';

import Clicker from './components/Clicker';

function App() {
  return (
    <>
      <main className="select-none overflow-hidden bg-zinc-900 text-zinc-200">
        <div className="flex min-h-dvh flex-col items-center justify-center gap-2">
          <div className="">hi!</div>

          <Clicker />
        </div>
      </main>
    </>
  );
}

export default App;

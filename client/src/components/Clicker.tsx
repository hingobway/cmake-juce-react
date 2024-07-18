import { useCallback } from 'react';

import { getJuceFunction } from '#@/util/juce/juce.js';

export default function Clicker() {
  const handleClick = useCallback(async () => {
    const runTest = getJuceFunction('runTest');
    const a = await runTest(99.2, 'abc', null, { a: 'b', c: true, d: null });

    console.log('FN', a);
  }, []);

  return (
    <>
      <button
        onClick={handleClick}
        className="bg-sky-600 hover:ring-4 ring-sky-950 rounded-full px-4 py-1 my-1"
      >
        click me
      </button>
    </>
  );
}

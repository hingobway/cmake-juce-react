import { useCallback, useEffect, useState } from 'react';

import { execute } from '#@/util/juce/juce.js';
import { ArrowRight } from 'lucide-react';

const CLEAR_MSG_MS = 8000;

export default function Clicker() {
  const [resp, setResp] = useState('');
  const [errorMsg, setErrorMsg] = useState<string | null>(null);
  useEffect(() => {
    const tm = setTimeout(() => {
      setResp('');
      setErrorMsg(null);
    }, CLEAR_MSG_MS);
    return () => clearTimeout(tm);
  }, [resp, errorMsg]);

  // form prpos

  const [name, setName] = useState('');

  const handleSend = useCallback(async () => {
    const a = await execute('announce', { name });

    if ('error' in a) {
      setErrorMsg(typeof a.error === 'string' ? a.error : 'Unknown error.');
      setResp('');
      return;
    }

    setErrorMsg(null);
    setResp(JSON.stringify(a, undefined, 2));
  }, [name]);

  // RENDER
  return (
    <>
      <form
        onSubmit={(e) => {
          e.preventDefault();
          handleSend();
        }}
      >
        <div className="my-1 flex flex-row gap-2">
          <input
            type="text"
            placeholder="name"
            value={name}
            onChange={({ currentTarget: { value: v } }) => setName(v)}
            //
            className="rounded-full border border-zinc-700 bg-transparent px-6 focus:border-sky-700 focus:outline-none focus:ring-0"
          />
          <button
            type="submit"
            className="rounded-full bg-sky-600 px-3 ring-sky-950 hover:ring-4"
          >
            <ArrowRight className="size-5" />
          </button>
        </div>
      </form>

      <pre className="min-h-20">
        <code className="text-sm">
          {errorMsg && <span className="text-red-500">{errorMsg}</span>}
          {resp}
        </code>
      </pre>
    </>
  );
}

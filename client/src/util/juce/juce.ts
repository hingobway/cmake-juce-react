import * as juce from 'juce';

import { COMMANDS } from './COMMANDS';

export function getJuceFunction(name: string) {
  const fn = juce.getNativeFunction(name);
  return fn as (...p: any[]) => Promise<any>;
}

export async function execute<Cmd extends keyof COMMANDS>(
  commandName: Cmd,
  ...[args]: Parameters<COMMANDS[Cmd]>[0] extends undefined
    ? []
    : [Parameters<COMMANDS[Cmd]>[0]]
) {
  const cmd = getJuceFunction('command');
  const s = await cmd({
    type: commandName,
    data: args,
  });

  let out: any;
  try {
    const a = JSON.parse(s);
    if (a.error) out = a;
    else out = a.data;
  } catch (_) {
    if (typeof s !== 'string') out = { error: 'INVALID' };
    out = { error: { raw: s } };
  }

  return out as ReturnType<COMMANDS[Cmd]> | { error: { raw: string } | string };
}

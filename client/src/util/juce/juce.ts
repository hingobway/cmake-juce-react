import * as juce from 'juce';



export function getJuceFunction(name: string) {
  const fn = juce.getNativeFunction(name);

  // TODO can this be typed better or templated
  return fn as (...p: any[]) => Promise<any>;
}



export async function execute(){
  const cmd = getJuceFunction("command");
  const s = await cmd();

  

}
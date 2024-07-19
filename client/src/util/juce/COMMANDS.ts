export type COMMANDS = {
  announce: (p: { name: string }) => {
    text: string;
    username: string;
    t_computed: number;
  };
};
//  satisfies  Record<string, ((params:Record<string, any>)=>any)>

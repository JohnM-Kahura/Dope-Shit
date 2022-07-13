// the code below should be in Player.ts

interface Player{

    name: string;
    
    jersey: number;
    
    active: boolean;
    
    }
    
export{Player};

class Team{
    players:string[];
    teamName:string;
    constructor( teamName : string) {
      
        this.teamName = teamName;
      }
}


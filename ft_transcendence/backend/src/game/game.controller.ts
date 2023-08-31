import { Controller, Post, Query } from '@nestjs/common';
import { validateSync } from 'class-validator';
import { DatabaseService } from 'src/database/database.service';

export class gameHistoricDto
{
    client1Id: number;
    persScore: number;
    client2Id: number;
    vsScore: number;
}

@Controller('game')
export class GameController {
    constructor(private db: DatabaseService){}

    @Post('saveScore') // http://localhost:3000/api/game/saveScore?data={"client1Id":1,"scoreClient1":1,"client2Id":2,"scoreClient2":2}
    async saveScore(@Query('data') data: any) { 
        // console.log("ICI", JSON.parse(data));
        const alldata = JSON.parse(data);
        const gameHistoric = new gameHistoricDto();
        gameHistoric.client1Id = alldata.user.id;
        gameHistoric.persScore = alldata.user.score;
        gameHistoric.client2Id = alldata.com.id;
        gameHistoric.vsScore = alldata.com.score;
		if (alldata.user.id === alldata.com.id)
			return ;
        const errors = await validateSync(gameHistoric);
        if (errors.length > 0) {
            console.log(errors);
            return errors;
        }
        else {
            // return this.db.saveScore(gameHistoric);
          //  this.ft_test(gameHistoric);
            this.db.historicnewEntry(gameHistoric);
            if (gameHistoric.persScore > gameHistoric.vsScore)
            {
                this.db.win(gameHistoric.client1Id);
                this.db.lose(gameHistoric.client2Id);
            }
            else
            {
                this.db.win(gameHistoric.client2Id);
                this.db.lose(gameHistoric.client1Id);
            }
        }
    }
       // return 'bonjour';

    async ft_test(param: gameHistoricDto)
    {
        return this.db.ComTest(param);
    }
}

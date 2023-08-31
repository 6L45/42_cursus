import { Module } from '@nestjs/common';
import { GameController } from './game.controller';
import { GameGateway } from './game.gateway';
import { DatabaseService } from 'src/database/database.service';
import { Lobby } from './lobby';

@Module({
  controllers: [GameController],
  providers: [GameGateway, DatabaseService, Lobby],
})
export class GameModule {}

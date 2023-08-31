import { Module } from '@nestjs/common';
import { RoomsController } from './rooms.controller';
import { DatabaseService } from 'src/database/database.service';
import { ChatGateway } from 'src/chat/chat.gateway';
import { UserConnectedService } from 'src/chat/user-connected-service.service';
import { ChatController } from 'src/chat/chat.controller';
import { createRoomDto } from 'src/dashboard/dashboardDtos/createsTablesDtos';

@Module({
  controllers: [RoomsController, ChatController],
  providers: [DatabaseService, ChatGateway,
        DatabaseService,
        createRoomDto,
        UserConnectedService,],
})
export class RoomsModule {}

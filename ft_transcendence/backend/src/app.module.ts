import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
// import { ChatModule } from './chat/chat.module';
import { AuthModule } from './auth/auth.module';
import { DashboardModule } from './dashboard/dashboard.module';
import { DatabaseModule } from './database/database.module';
import { PrismaModule } from './prisma/prisma.module';
import { ConfigModule } from '@nestjs/config';
import { GameModule } from './game/game.module';
import { RoomsModule } from './rooms/rooms.module';

@Module({
  imports: [
    // ChatModule,
    GameModule,
    AuthModule,
    DashboardModule,
    DatabaseModule,
    PrismaModule,
    ConfigModule.forRoot({
      isGlobal: true,
    }),
    RoomsModule,
    //            PongModule,
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}

import { Module } from '@nestjs/common';
import { DashboardController } from './controllers/dashboard/dashboard.controller';
import { DashboardService } from './services/dashboard/dashboard.service';
import { DatabaseService } from 'src/database/database.service';

@Module({
  controllers: [DashboardController],
  providers: [DashboardService, DatabaseService],
})
export class DashboardModule {}

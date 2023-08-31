/*
  Warnings:

  - You are about to alter the column `title` on the `client_stats` table. The data in that column could be lost. The data in that column will be cast from `VarChar(50)` to `VarChar(50)`.

*/
-- AlterTable
ALTER TABLE "client_stats" ALTER COLUMN "title" SET NOT NULL,
ALTER COLUMN "title" SET DATA TYPE VARCHAR(50);

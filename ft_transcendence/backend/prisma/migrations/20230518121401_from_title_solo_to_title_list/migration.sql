/*
  Warnings:

  - The `title` column on the `client_stats` table would be dropped and recreated. This will lead to data loss if there is data in the column.

*/
-- AlterTable
ALTER TABLE "client_stats" DROP COLUMN "title",
ADD COLUMN     "title" VARCHAR(50)[];

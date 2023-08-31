/*
  Warnings:

  - You are about to drop the column `secu` on the `rooms` table. All the data in the column will be lost.
  - Added the required column `type` to the `rooms` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE "rooms" DROP COLUMN "secu",
ADD COLUMN     "type" INTEGER NOT NULL;

/*
  Warnings:

  - You are about to drop the column `type` on the `rooms` table. All the data in the column will be lost.
  - Added the required column `secu` to the `rooms` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE "rooms" DROP COLUMN "type",
ADD COLUMN     "secu" INTEGER NOT NULL;

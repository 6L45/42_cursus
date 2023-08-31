/*
  Warnings:

  - You are about to drop the column `type` on the `rooms` table. All the data in the column will be lost.
  - You are about to drop the `_AdminsRooms` table. If the table is not empty, all the data it contains will be lost.
  - Added the required column `secu` to the `rooms` table without a default value. This is not possible if the table is not empty.

*/
-- DropForeignKey
ALTER TABLE "_AdminsRooms" DROP CONSTRAINT "_AdminsRooms_A_fkey";

-- DropForeignKey
ALTER TABLE "_AdminsRooms" DROP CONSTRAINT "_AdminsRooms_B_fkey";

-- AlterTable
ALTER TABLE "rooms" DROP COLUMN "type",
ADD COLUMN     "password" VARCHAR,
ADD COLUMN     "secu" INTEGER NOT NULL;

-- DropTable
DROP TABLE "_AdminsRooms";

/*
  Warnings:

  - A unique constraint covering the columns `[roomId,memberId]` on the table `room_members` will be added. If there are existing duplicate values, this will fail.

*/
-- DropIndex
DROP INDEX "room_members_id_memberId_key";

-- CreateIndex
CREATE UNIQUE INDEX "room_members_roomId_memberId_key" ON "room_members"("roomId", "memberId");

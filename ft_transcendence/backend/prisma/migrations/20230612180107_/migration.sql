/*
  Warnings:

  - A unique constraint covering the columns `[id,memberId]` on the table `room_members` will be added. If there are existing duplicate values, this will fail.

*/
-- CreateIndex
CREATE UNIQUE INDEX "room_members_id_memberId_key" ON "room_members"("id", "memberId");

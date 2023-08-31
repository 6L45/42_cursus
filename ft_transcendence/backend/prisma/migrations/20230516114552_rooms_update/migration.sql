/*
  Warnings:

  - You are about to drop the `_ClientsRooms` table. If the table is not empty, all the data it contains will be lost.
  - Changed the type of `status` on the `clients_to_clients` table. No cast exists, the column would be dropped and recreated, which cannot be done if there is data, since the column is required.
  - Added the required column `type` to the `rooms` table without a default value. This is not possible if the table is not empty.

*/
-- DropForeignKey
ALTER TABLE "_ClientsRooms" DROP CONSTRAINT "_ClientsRooms_A_fkey";

-- DropForeignKey
ALTER TABLE "_ClientsRooms" DROP CONSTRAINT "_ClientsRooms_B_fkey";

-- AlterTable
ALTER TABLE "clients_to_clients" DROP COLUMN "status",
ADD COLUMN     "status" INTEGER NOT NULL;

-- AlterTable
ALTER TABLE "rooms" ADD COLUMN     "type" INTEGER NOT NULL;

-- DropTable
DROP TABLE "_ClientsRooms";

-- CreateTable
CREATE TABLE "room_members" (
    "id" SERIAL NOT NULL,
    "roomId" INTEGER NOT NULL,
    "memberId" INTEGER NOT NULL,
    "status" INTEGER NOT NULL,

    CONSTRAINT "room_members_pkey" PRIMARY KEY ("id")
);

-- CreateIndex
CREATE INDEX "clients_to_clients_status_idx" ON "clients_to_clients"("status");

-- AddForeignKey
ALTER TABLE "room_members" ADD CONSTRAINT "room_members_roomId_fkey" FOREIGN KEY ("roomId") REFERENCES "rooms"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "room_members" ADD CONSTRAINT "room_members_memberId_fkey" FOREIGN KEY ("memberId") REFERENCES "Clients"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

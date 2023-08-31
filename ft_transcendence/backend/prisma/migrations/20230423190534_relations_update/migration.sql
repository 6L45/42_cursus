/*
  Warnings:

  - You are about to drop the column `memberOf` on the `Clients` table. All the data in the column will be lost.
  - You are about to drop the column `admins` on the `rooms` table. All the data in the column will be lost.
  - You are about to drop the column `members` on the `rooms` table. All the data in the column will be lost.

*/
-- AlterTable
ALTER TABLE "Clients" DROP COLUMN "memberOf";

-- AlterTable
ALTER TABLE "rooms" DROP COLUMN "admins",
DROP COLUMN "members";

-- CreateTable
CREATE TABLE "_ClientsRooms" (
    "A" INTEGER NOT NULL,
    "B" INTEGER NOT NULL
);

-- CreateTable
CREATE TABLE "_AdminsRooms" (
    "A" INTEGER NOT NULL,
    "B" INTEGER NOT NULL
);

-- CreateIndex
CREATE UNIQUE INDEX "_ClientsRooms_AB_unique" ON "_ClientsRooms"("A", "B");

-- CreateIndex
CREATE INDEX "_ClientsRooms_B_index" ON "_ClientsRooms"("B");

-- CreateIndex
CREATE UNIQUE INDEX "_AdminsRooms_AB_unique" ON "_AdminsRooms"("A", "B");

-- CreateIndex
CREATE INDEX "_AdminsRooms_B_index" ON "_AdminsRooms"("B");

-- AddForeignKey
ALTER TABLE "_ClientsRooms" ADD CONSTRAINT "_ClientsRooms_A_fkey" FOREIGN KEY ("A") REFERENCES "Clients"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "_ClientsRooms" ADD CONSTRAINT "_ClientsRooms_B_fkey" FOREIGN KEY ("B") REFERENCES "rooms"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "_AdminsRooms" ADD CONSTRAINT "_AdminsRooms_A_fkey" FOREIGN KEY ("A") REFERENCES "Clients"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "_AdminsRooms" ADD CONSTRAINT "_AdminsRooms_B_fkey" FOREIGN KEY ("B") REFERENCES "rooms"("id") ON DELETE CASCADE ON UPDATE CASCADE;

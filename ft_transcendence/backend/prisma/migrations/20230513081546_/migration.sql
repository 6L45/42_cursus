/*
  Warnings:

  - You are about to alter the column `img` on the `Clients` table. The data in that column could be lost. The data in that column will be cast from `Text` to `VarChar(100)`.
  - A unique constraint covering the columns `[img]` on the table `Clients` will be added. If there are existing duplicate values, this will fail.
  - Made the column `img` on table `Clients` required. This step will fail if there are existing NULL values in that column.

*/
-- AlterTable
ALTER TABLE "Clients" ALTER COLUMN "img" SET NOT NULL,
ALTER COLUMN "img" SET DATA TYPE VARCHAR(100);

-- CreateIndex
CREATE UNIQUE INDEX "Clients_img_key" ON "Clients"("img");

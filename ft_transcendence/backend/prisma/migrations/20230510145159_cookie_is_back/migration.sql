/*
  Warnings:

  - A unique constraint covering the columns `[cookie]` on the table `Clients` will be added. If there are existing duplicate values, this will fail.
  - Added the required column `cookie` to the `Clients` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE "Clients" ADD COLUMN     "cookie" VARCHAR(250) NOT NULL;

-- CreateIndex
CREATE UNIQUE INDEX "Clients_cookie_key" ON "Clients"("cookie");

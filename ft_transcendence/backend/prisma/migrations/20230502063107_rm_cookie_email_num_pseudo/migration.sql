/*
  Warnings:

  - You are about to drop the column `cookie` on the `Clients` table. All the data in the column will be lost.
  - You are about to drop the column `email` on the `Clients` table. All the data in the column will be lost.
  - You are about to drop the column `num` on the `Clients` table. All the data in the column will be lost.
  - You are about to drop the column `pseudo` on the `Clients` table. All the data in the column will be lost.

*/
-- DropIndex
DROP INDEX "Clients_cookie_key";

-- DropIndex
DROP INDEX "Clients_email_key";

-- DropIndex
DROP INDEX "Clients_num_key";

-- DropIndex
DROP INDEX "Clients_pseudo_key";

-- AlterTable
ALTER TABLE "Clients" DROP COLUMN "cookie",
DROP COLUMN "email",
DROP COLUMN "num",
DROP COLUMN "pseudo";

/*
  Warnings:

  - Added the required column `id42` to the `Clients` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE "Clients" ADD COLUMN     "id42" INTEGER NOT NULL;
